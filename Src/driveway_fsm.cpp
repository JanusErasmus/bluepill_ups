/*
 * driveway_fsm.cpp
 *
 *  Created on: 18 Aug 2018
 *      Author: janus
 */
#include <stdio.h>
#include "driveway_fsm.h"

DrivewayFSM::DrivewayFSM(DrivewayLights *lights) : mLights(lights)
{
	mCurrentState = DrivewayLights::SWITCH_OFF;
	mPrevStreet = MotorStateChangeListener::UNKNOWN;
	mPrevHouse = MotorStateChangeListener::UNKNOWN;
}

DrivewayFSM::~DrivewayFSM()
{
}

void DrivewayFSM::updateState(MotorStateChangeListener::eMotorState street,
		MotorStateChangeListener::eMotorState house)
{
	//printf("%d %d,%d\n", mCurrentState, street, house);
	switch(mCurrentState)
	{
	case DrivewayLights::SWITCH_OFF:
	{
		if(street == MotorStateChangeListener::OPENING)
			setState(DrivewayLights::STREET_TO_HOUSE_OPENING);

		if(house == MotorStateChangeListener::OPENING)
			setState(DrivewayLights::HOUSE_TO_STREET_OPENING);

		if(street == MotorStateChangeListener::OPEN)
			setState(DrivewayLights::STREET_TO_HOUSE_OPEN);

		if(house == MotorStateChangeListener::OPEN)
			setState(DrivewayLights::HOUSE_TO_STREET_OPEN);
	}
			break;
		case DrivewayLights::FLASH_ON_OFF:
			break;
		case DrivewayLights::HOUSE_TO_STREET_OPENING:
		case DrivewayLights::STREET_TO_HOUSE_OPENING:
		{
			if(street == MotorStateChangeListener::OPEN)
				setState(DrivewayLights::STREET_TO_HOUSE_OPEN);

			if(house == MotorStateChangeListener::OPEN)
				setState(DrivewayLights::HOUSE_TO_STREET_OPEN);
		}
			break;
		case DrivewayLights::HOUSE_TO_STREET_OPEN:
		case DrivewayLights::STREET_TO_HOUSE_OPEN:
		{
			if(street == MotorStateChangeListener::CLOSING)
				setState(DrivewayLights::STREET_TO_HOUSE_CLOSING);

			if(house == MotorStateChangeListener::CLOSING)
				setState(DrivewayLights::HOUSE_TO_STREET_CLOSING);

			if(street == MotorStateChangeListener::OPEN)
				setState(DrivewayLights::STREET_TO_HOUSE_OPEN);

			if(house == MotorStateChangeListener::OPEN)
				setState(DrivewayLights::HOUSE_TO_STREET_OPEN);
		}
			break;
		case DrivewayLights::HOUSE_TO_STREET_CLOSING:
		case DrivewayLights::STREET_TO_HOUSE_CLOSING:
		{
			if(street == MotorStateChangeListener::OPEN)
				setState(DrivewayLights::STREET_TO_HOUSE_OPEN);

			if(house == MotorStateChangeListener::OPEN)
				setState(DrivewayLights::HOUSE_TO_STREET_OPEN);
		}
			break;
		case DrivewayLights::ON:
		case DrivewayLights::OFF:
			break;
	}

	//both closed, always switch off
	if((street == MotorStateChangeListener::CLOSED) && (house == MotorStateChangeListener::CLOSED))
	{
		if(mCurrentState != DrivewayLights::SWITCH_OFF)
			setState(DrivewayLights::SWITCH_OFF);
	}


	mPrevStreet = street;
	mPrevHouse = house;
}

void DrivewayFSM::setState(DrivewayLights::eLightState state)
{
	mCurrentState = state;
	mLights->set(state);
}
