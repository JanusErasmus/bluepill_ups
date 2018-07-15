/*
 * interface_nrf24.h
 *
 *  Created on: 14 Jul 2018
 *      Author: janus
 */

#ifndef SRC_INTERFACE_NRF24_H_
#define SRC_INTERFACE_NRF24_H_
#include "stm32f1xx_hal.h"

#include "nrf24.h"

class InterfaceNRF24
{
	static InterfaceNRF24 *__instance;
	nRF24cb nrf_cb;
	static SPI_HandleTypeDef *mSPI;
	uint32_t mPacketsLost;

	static uint8_t nrf_rw(uint8_t data);
	static void nrf_cs_l(void);
	static void nrf_cs_h(void);
	static void nrf_ce_l(void);
	static void nrf_ce_h(void);
	nRF24_TXResult transmitPacket(uint8_t *pBuf, uint8_t length);

public:
	InterfaceNRF24(SPI_HandleTypeDef *spi_handle);
	virtual ~InterfaceNRF24();

	static void init(SPI_HandleTypeDef *spi_handle);
	static InterfaceNRF24 *get(){ return __instance; }

	void run();
	int transmit(uint8_t *addr, uint8_t *payload, uint8_t length);
};

#endif /* SRC_INTERFACE_NRF24_H_ */
