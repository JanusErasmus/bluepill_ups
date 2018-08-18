/*
 * driveway_fsm.h
 *
 *  Created on: 18 Aug 2018
 *      Author: janus
 */

#ifndef SRC_DRIVEWAY_FSM_H_
#define SRC_DRIVEWAY_FSM_H_
#include "driveway_lights.h"
#include "motor_state_change_listener.h"

class DrivewayFSM
{
	DrivewayLights::eLightState mCurrentState;
	MotorStateChangeListener::eMotorState mPrevStreet;
	MotorStateChangeListener::eMotorState mPrevHouse;
	DrivewayLights *mLights;

	void setState(DrivewayLights::eLightState state);

public:
	DrivewayFSM(DrivewayLights *lights);
	virtual ~DrivewayFSM();

	void updateState(MotorStateChangeListener::eMotorState street,
			MotorStateChangeListener::eMotorState house);
};

#endif /* SRC_DRIVEWAY_FSM_H_ */
