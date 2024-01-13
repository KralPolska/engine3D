#include "LightArray.h"

LightArray::LightArray()
{
	for (int i = 0; i < 8; i++)
	{
		lights[i].enable(false);
		lights[i].setPosition({ 0,0,0 });
		lights[i].setColor(1.0f, 1.0f, 1.0f,1.0f);
	}
}

LightArray::~LightArray()
{
	delete this;
}

void LightArray::setLights(LightSource lights[])
{
	for (int i = 0; i < 8; i++)
		this->lights[i] = lights[i];
}
