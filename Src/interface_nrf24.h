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

class InterfaceNRF24 {

	static InterfaceNRF24 *__instance;
	SPI_HandleTypeDef *hspi;
	nRF24cb nrf_if;

	static uint8_t nrf_rw(uint8_t data);
	static void nrf_cs_l(void);
	static void nrf_cs_h(void);
	static void nrf_ce_l(void);
	static void nrf_ce_h(void);
	nRF24_TXResult nRF24_TransmitPacket(uint8_t *pBuf, uint8_t length) ;

	InterfaceNRF24(SPI_HandleTypeDef *spi_handle);
	virtual ~InterfaceNRF24();

public:
	static void init(SPI_HandleTypeDef *spi_handle);
	static InterfaceNRF24 *get(){ return __instance; }

	void run();
	void talk();
};

#endif /* SRC_INTERFACE_NRF24_H_ */
