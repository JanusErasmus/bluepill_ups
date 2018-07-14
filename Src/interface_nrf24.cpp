/*
 * interface_nrf24.cpp
 *
 *  Created on: 14 Jul 2018
 *      Author: janus
 */
#include <stdio.h>

#include "Utils/utils.h"
#include "interface_nrf24.h"

InterfaceNRF24 *InterfaceNRF24::__instance = 0;

uint8_t InterfaceNRF24::nrf_rw(uint8_t data)
{
	if(!__instance)
		return 0;

	uint8_t rx;
	HAL_SPI_TransmitReceive(__instance->hspi, &data, &rx, 1, 1000);

	return rx;
}

void InterfaceNRF24::nrf_cs_l(void)
{
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
}

void InterfaceNRF24::nrf_cs_h(void)
{
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}

void InterfaceNRF24::nrf_ce_l(void)
{
	HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_RESET);
}

void InterfaceNRF24::nrf_ce_h(void)
{
	HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_SET);
}

void InterfaceNRF24::init(SPI_HandleTypeDef *spi_handle)
{
	if(!__instance)
		__instance = new InterfaceNRF24(spi_handle);
}

InterfaceNRF24::InterfaceNRF24(SPI_HandleTypeDef *spi_handle)
{
	hspi = spi_handle;

	nrf_if.nRF24_RW = nrf_rw;
	nrf_if.nRF24_CSN_L = nrf_cs_l;
	nrf_if.nRF24_CSN_H = nrf_cs_h;
	nrf_if.nRF24_CE_L = nrf_ce_l;
	nrf_if.nRF24_CE_H = nrf_ce_h;

	nRF24_Init(&nrf_if);

	// Set RF channel
	nRF24_SetRFChannel(40);

	// Set data rate
	nRF24_SetDataRate(nRF24_DR_250kbps);

	// Set CRC scheme
	nRF24_SetCRCScheme(nRF24_CRC_2byte);

	// Set address width, its common for all pipes (RX and TX)
	nRF24_SetAddrWidth(3);

    // Configure TX PIPE
    static const uint8_t nRF24_ADDR[] = { 'E', 'S', 'B' };
    nRF24_SetAddr(nRF24_PIPETX, nRF24_ADDR); // program TX address
    nRF24_SetAddr(nRF24_PIPE0, nRF24_ADDR); // program address for pipe#0, must be same as TX (for Auto-ACK)

    // Configure RX PIPE
	nRF24_SetAddr(nRF24_PIPE1, nRF24_ADDR); // program address for pipe
	nRF24_SetRXPipe(nRF24_PIPE1, nRF24_AA_ON, 10); // Auto-ACK: enabled, payload length: 10 bytes

	// Set TX power for Auto-ACK (maximum, to ensure that transmitter will hear ACK reply)
	nRF24_SetTXPower(nRF24_TXPWR_0dBm);

	// Configure auto retransmit: 10 retransmissions with pause of 2500s in between
	nRF24_SetAutoRetr(nRF24_ARD_4000us, 10);

	// Enable Auto-ACK for pipe#0 (for ACK packets)
	nRF24_EnableAA(nRF24_PIPE0);
	//    // Disable ShockBurst for all pipes
	//    nRF24_DisableAA(0xFF);

	// Set operational mode (PRX == receiver)
	nRF24_SetOperationalMode(nRF24_MODE_RX);

	// Clear any pending IRQ flags
	nRF24_ClearIRQFlags();

	// Wake the transceiver
	nRF24_SetPowerMode(nRF24_PWR_UP);

	// Put the transceiver to the RX mode
	nrf_ce_h();
}

InterfaceNRF24::~InterfaceNRF24()
{
}

#define nRF24_WAIT_TIMEOUT         (uint32_t)20
// Function to transmit data packet
// input:
//   pBuf - pointer to the buffer with data to transmit
//   length - length of the data buffer in bytes
// return: one of nRF24_TX_xx values
nRF24_TXResult InterfaceNRF24::nRF24_TransmitPacket(uint8_t *pBuf, uint8_t length)
{
	volatile uint32_t wait = nRF24_WAIT_TIMEOUT;
	uint8_t status;

	// Deassert the CE pin (in case if it still high)
	nrf_ce_l();

	// Transfer a data from the specified buffer to the TX FIFO
	nRF24_WritePayload(pBuf, length);
	HAL_Delay(100);
	// Start a transmission by asserting CE pin (must be held at least 10us)
	nrf_ce_h();

	// Poll the transceiver status register until one of the following flags will be set:
	//   TX_DS  - means the packet has been transmitted
	//   MAX_RT - means the maximum number of TX retransmits happened
	// note: this solution is far from perfect, better to use IRQ instead of polling the status
	do {
		status = nRF24_GetStatus();
		if (status & (nRF24_FLAG_TX_DS | nRF24_FLAG_MAX_RT)) {
			break;
		}

		HAL_Delay(100);
	} while (--wait);

	// Deassert the CE pin (Standby-II --> Standby-I)

	if (!wait) {
		// Timeout
		return nRF24_TX_TIMEOUT;
	}

	// Check the flags in STATUS register
	printf("Status [0x%02X]\n", status);

	// Clear pending IRQ flags
    nRF24_ClearIRQFlags();

	if (status & nRF24_FLAG_MAX_RT) {
		// Auto retransmit counter exceeds the programmed maximum limit (FIFO is not removed)
		return nRF24_TX_MAXRT;
	}

	if (status & nRF24_FLAG_TX_DS) {
		// Successful transmission
		return nRF24_TX_SUCCESS;
	}

	// Some banana happens, a payload remains in the TX FIFO, flush it
	nRF24_FlushTX();

	return nRF24_TX_ERROR;
}



	// This is simple transmitter (to one logic address):
	//   - TX address: '0xE7 0x1C 0xE3'
	//   - payload: 5 bytes
	//   - RF channel: 115 (2515MHz)
	//   - data rate: 250kbps (minimum possible, to increase reception reliability)
	//   - CRC scheme: 2 byte
void InterfaceNRF24::talk()
{
	// Buffer to store a payload of maximum width
	uint8_t nRF24_payload[32];

	// Some variables
	uint32_t packets_lost = 0; // global counter of lost packets
	uint8_t otx;
	uint8_t otx_plos_cnt; // lost packet count
	uint8_t otx_arc_cnt; // retransmit count


	// The main loop
	int payload_length = 10;
	static int j = 0;

	// Prepare data packet
	for (int i = 0; i < payload_length; i++) {
		nRF24_payload[i] = j++;
		if (j > 0x000000FF) j = 0;
	}

	// Print a payload
	printf("PAYLOAD:> TX %d\n", (int)payload_length);
	diag_dump_buf((char *)nRF24_payload, payload_length);

	// Transmit a packet	// Set operational mode (PTX == transmitter)
	nRF24_SetOperationalMode(nRF24_MODE_TX);


	nRF24_TXResult tx_res = nRF24_TransmitPacket(nRF24_payload, payload_length);
	otx = nRF24_GetRetransmitCounters();
	otx_plos_cnt = (otx & nRF24_MASK_PLOS_CNT) >> 4; // packets lost counter
	otx_arc_cnt  = (otx & nRF24_MASK_ARC_CNT); // auto retransmissions counter
	switch (tx_res) {
	case nRF24_TX_SUCCESS:
		printf(GREEN("OK\n"));
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		break;
	case nRF24_TX_TIMEOUT:
		printf(RED("TIMEOUT\n"));
		packets_lost++;
		break;
	case nRF24_TX_MAXRT:
		printf(CYAN("MAX RETRANSMIT\n"));
		packets_lost += otx_plos_cnt;
		nRF24_ResetPLOS();

		break;
	default:
		printf(RED("ERROR\n"));
		break;
	}
	printf(" - ARC= %d LOST= %d\n", (int)otx_arc_cnt, (int)packets_lost);


	// Set operational mode (PRX == receiver)
	nRF24_SetOperationalMode(nRF24_MODE_RX);
}

void InterfaceNRF24::run()
{
	if(HAL_GPIO_ReadPin(NRF_IRQ_GPIO_Port, NRF_IRQ_Pin))
		return;

    uint8_t payload_length = 10;
	uint8_t nRF24_payload[32];
	if (nRF24_GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
	{
		// Get a payload from the transceiver
		nRF24_RXResult pipe = nRF24_ReadPayload(nRF24_payload, &payload_length);

		// Clear all pending IRQ flags
		nRF24_ClearIRQFlags();

		// Print a payload contents to UART
		printf("RCV PIPE# %d", (int)pipe);
		printf(" PAYLOAD:> %d", payload_length);
		diag_dump_buf(nRF24_payload, payload_length);
	}
}

