/*
 * gate_lights.cpp
 *
 *  Created on: 11 Aug 2018
 *      Author: janus
 */

#include "driveway_lights.h"

#include "stm32f1xx_hal.h"

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

DrivewayLights::DrivewayLights()
{
	mSequence = OFF;
	mFlashFlag = 0;
	mTick = 0;
}

DrivewayLights::~DrivewayLights()
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

void DrivewayLights::run()
{
	//sample gate light every 300ms
	static int checkGate = 0;
	int tick = HAL_GetTick();
	if(tick < (checkGate + 300))
		return;
	checkGate = tick;

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
	case HOUSE_TO_STREET_OPEN:
		setPin(mFlashFlag, GPIO_PIN_SET);
		mFlashFlag++;
		if(mFlashFlag > 4)
		{
			mFlashFlag = 0;
			mSequence = ON;
		}
		break;
	case HOUSE_TO_STREET_CLOSING:
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
	case STREET_TO_HOUSE_OPEN:
		setPin(mFlashFlag, GPIO_PIN_SET);
		mFlashFlag--;
		if(mFlashFlag < 0)
		{
			mFlashFlag = 0;
			mSequence = ON;
		}
		break;
	case STREET_TO_HOUSE_CLOSING:
		setPin(mFlashFlag, GPIO_PIN_SET);
		mFlashFlag--;
		if(mFlashFlag < 0)
			mFlashFlag = 4;
		setPin(mFlashFlag, GPIO_PIN_RESET);
		break;
	case SWITCH_OFF:
		if(mFlashFlag == 0) //switch all lights on
		{
			setAll();
		}
		if(mFlashFlag == 101) //switch outer lights off to middle after 30s
		{
			setPin(0, GPIO_PIN_RESET);
			setPin(4, GPIO_PIN_RESET);
		}
		if(mFlashFlag == 102) //switch outer lights off to middle
		{
			setPin(1, GPIO_PIN_RESET);
			setPin(3, GPIO_PIN_RESET);
		}
		if(mFlashFlag == 103) //switch outer lights off to middle
		{
			setPin(2, GPIO_PIN_RESET);
			mSequence = OFF;
		}
		mFlashFlag++;
		break;
	}
}


void DrivewayLights::set(eSequence seq)
{
	//when a gate was open or opening, do not change sequence when another starts opening
	if((seq == STREET_TO_HOUSE_OPENING) || (seq == HOUSE_TO_STREET_OPENING))
	{
		if((mSequence == STREET_TO_HOUSE_OPENING) || (mSequence == HOUSE_TO_STREET_OPENING) || (mSequence == ON) ||
				(mSequence == STREET_TO_HOUSE_OPEN) || (mSequence == HOUSE_TO_STREET_OPEN))
		{
			return;
		}
	}

	//when switching on, start at the correct side
	if(seq == STREET_TO_HOUSE_OPEN)
		mFlashFlag = 4;
	else
		mFlashFlag = 0;


	//keep lights on for 30s after closing
	if(seq == OFF)
	{
		if((mSequence == STREET_TO_HOUSE_CLOSING) || (mSequence == HOUSE_TO_STREET_CLOSING))
			seq = SWITCH_OFF;
	}

	mSequence = seq;

}
