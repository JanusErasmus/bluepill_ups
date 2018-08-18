/*
 * driveway_motors.cpp
 *
 *  Created on: 12 Aug 2018
 *      Author: janus
 */

#include "driveway_motors.h"

DrivewayMotors::DrivewayMotors(DrivewayLights *lights,
								CenturionGate *street_gate,
								CenturionGate *house_gate) :
								mStreetGate(street_gate),
								mHouseGate(house_gate),
								mFSM(lights)
{
	mStreetGate->setStateListener(this);
	mHouseGate->setStateListener(this);
}

DrivewayMotors::~DrivewayMotors()
{
}

void DrivewayMotors::run()
{
    //sample gate light every 3.2 seconds second
    static int checkGate = 0;
    int tick = HAL_GetTick();
    if(tick < (checkGate + 3200))
    	return;

  	  checkGate = tick;

  	  mStreetGate->run();
  	  mHouseGate->run();
}

extern void reportNow();

void DrivewayMotors::stateChanged(CenturionGate* gate, eMotorState state)
{
	if(gate == mStreetGate)
	{
		printf("StreetGate: %s\n", stateToString(state));
	}

	if(gate == mHouseGate)
	{
		printf("HouseGate: %s\n", stateToString(state));
	}

	mFSM.updateState(mStreetGate->getState(), mHouseGate->getState());

	//do not report moving states
	//if(!((state == CLOSING) || (state == OPENING)))
	reportNow();
}
