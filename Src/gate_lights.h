/*
 * gate_lights.h
 *
 *  Created on: 11 Aug 2018
 *      Author: janus
 */

#ifndef SRC_GATE_LIGHTS_H_
#define SRC_GATE_LIGHTS_H_

class GateLights {
public:
	enum eSequence
	{
		ON,
		OFF,
		FLASH_ON_OFF,
		HOUSE_TO_STREET_OPENING,
		HOUSE_TO_STREET_CLOSEING,
		STREET_TO_HOUSE_OPENING,
		STREET_TO_HOUSE_CLOSEING,
		SWITCH_OFF
	};
private:
	eSequence mSequence;
	int mFlashFlag;
	int mTick;
public:
	GateLights();
	virtual ~GateLights();

	void run();
	void set(eSequence seq);
};

#endif /* SRC_GATE_LIGHTS_H_ */
