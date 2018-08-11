/*
 * gate_lights.cpp
 *
 *  Created on: 11 Aug 2018
 *      Author: janus
 */

#include "stm32f1xx_hal.h"
#include "gate_lights.h"

typedef struct
{
	GPIO_TypeDef *port;
	uint32_t pin;
}sGatePins;

static const sGatePins gatePins[] =
{
		{GATE_OUT0_Port, GATE_OUT0_Pin},
		{GATE_OUT1_Port, GATE_OUT1_Pin},
		{GATE_OUT2_Port, GATE_OUT2_Pin},
		{GATE_OUT3_Port, GATE_OUT3_Pin},
		{GATE_OUT4_Port, GATE_OUT4_Pin},
};

void setPin(uint8_t index, GPIO_PinState state)
{
	HAL_GPIO_WritePin(gatePins[index].port, gatePins[index].pin, state);
}

GateLights::GateLights()
{
	mSequence = OFF;
	mFlashFlag = 0;
	mTick = 0;
}

GateLights::~GateLights()
{
}

void setAll()
{
	for (int k = 0; k < 5; ++k)
	{
		setPin(k, GPIO_PIN_SET);
	}
}

void resetAll()
{
	for (int k = 0; k < 5; ++k)
	{
		setPin(k, GPIO_PIN_RESET);
	}
}

void GateLights::run()
{
	switch(mSequence)
	{
	case OFF:
		resetAll();
		break;
	case ON:
		setAll();
		break;
	case FLASH_ON_OFF:
		if(mFlashFlag)
		{
			mFlashFlag = 0;
			setAll();
		}
		else
		{
			mFlashFlag = 1;
			resetAll();
		}
		break;
	case HOUSE_TO_STREET_OPENING:
		setPin(mFlashFlag, GPIO_PIN_RESET);
		mFlashFlag = (mFlashFlag + 1) % 5;
		setPin(mFlashFlag, GPIO_PIN_SET);
		break;
	case HOUSE_TO_STREET_CLOSEING:
		setPin(mFlashFlag, GPIO_PIN_SET);
		mFlashFlag = (mFlashFlag + 1) % 5;
		setPin(mFlashFlag, GPIO_PIN_RESET);
		break;
	case STREET_TO_HOUSE_OPENING:
		setPin(mFlashFlag, GPIO_PIN_RESET);
		mFlashFlag--;
		if(mFlashFlag < 0)
			mFlashFlag = 4;
		setPin(mFlashFlag, GPIO_PIN_SET);
		break;
	case STREET_TO_HOUSE_CLOSEING:
		setPin(mFlashFlag, GPIO_PIN_SET);
		mFlashFlag--;
		if(mFlashFlag < 0)
			mFlashFlag = 4;
		setPin(mFlashFlag, GPIO_PIN_RESET);
		break;
	case SWITCH_OFF:
		break;
	}
}


void GateLights::set(eSequence seq)
{
	mFlashFlag = 0;
	mSequence = seq;
}
