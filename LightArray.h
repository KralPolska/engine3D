#pragma once
#include "LightSource.h"
class LightArray
{
public:
	LightArray();
	~LightArray();

	LightSource lights[8];
	void setLights(LightSource lights[]);
	
	LightArray& operator= (LightArray& other)
	{
		for (int i = 0; i < 8; i++)
			this->lights[i] = other.lights[i];
	}
};

