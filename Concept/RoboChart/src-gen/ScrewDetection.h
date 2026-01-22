#ifndef ROBOCALC_CONTROLLERS_SCREWDETECTION_H_
#define ROBOCALC_CONTROLLERS_SCREWDETECTION_H_

#include "UR5WithCamera.h"
#include "RoboCalcAPI/Controller.h"
#include "DataTypes.h"

#include "stm0.h"

class ScrewDetection: public robocalc::Controller 
{
public:
	ScrewDetection(UR5WithCamera& _platform) : platform(&_platform){};
	ScrewDetection() : platform(nullptr){};
	
	~ScrewDetection() = default;
	
	void Execute()
	{
		stm0.execute();
	}
	
	struct Channels
	{
		ScrewDetection& instance;
		Channels(ScrewDetection& _instance) : instance(_instance) {}
		
	};
	
	Channels channels{*this};
	
	UR5WithCamera* platform;
	stm0_StateMachine<ScrewDetection> stm0{*platform, *this, &stm0};
};

#endif
