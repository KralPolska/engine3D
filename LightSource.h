#pragma once
#include "point3d.h"
class LightSource
{
private:
	point3d position;
	float color[4];
	bool enabled;
	GLenum lightIndex;
public:
	LightSource();

	void enable(bool enabled);
	void setPosition(point3d position);
	void setColor(float r, float g, float b, float a);
	void setLightIndex(GLenum lightIndex);
	void applyLight();
	bool isEnabled();
	point3d getPosition();
	std::vector<float> getColor();

	LightSource& operator = (LightSource& other)
	{
		this->position = other.position;
		for (int i = 0; i < 4; i++)
			this->color[i] = other.color[i];
		this->enabled = other.enabled;
		this->lightIndex = other.lightIndex;

		return *this;
	}

};

