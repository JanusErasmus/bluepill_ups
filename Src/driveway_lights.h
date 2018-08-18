/*
 * gate_lights.h
 *
 *  Created on: 11 Aug 2018
 *      Author: janus
 */

#ifndef SRC_DRIVEWAY_LIGHTS_H_
#define SRC_DRIVEWAY_LIGHTS_H_

class DrivewayLights {
public:
	enum eLightState
	{
		ON,
		OFF,
		FLASH_ON_OFF,
		HOUSE_TO_STREET_OPENING,
		HOUSE_TO_STREET_OPEN,
		HOUSE_TO_STREET_CLOSING,
		STREET_TO_HOUSE_OPENING,
		STREET_TO_HOUSE_OPEN,
		STREET_TO_HOUSE_CLOSING,
		SWITCH_OFF
	};
private:
	eLightState mState;
	int mFlashFlag;
	bool mFillFlag;
	int mTick;
public:
	DrivewayLights();
	virtual ~DrivewayLights();

	void run();
	void set(eLightState state);
};

#endif /* SRC_DRIVEWAY_LIGHTS_H_ */
