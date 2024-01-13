#include "LightSource.h"

LightSource::LightSource()
{
	this->position = { 0,0,0 };
	this->color[0] = 1.0f;
	this->color[1] = 1.0f;
	this->color[2] = 1.0f;
	this->color[3] = 0.3f;
	this->enabled = false;
	this->lightIndex = GL_LIGHT0;
}

void LightSource::enable(bool enabled)
{
	this->enabled = enabled;
}

void LightSource::setPosition(point3d position)
{
	this->position = position;
}

void LightSource::setColor(float r, float g, float b, float a)
{
	if (r < 0.0f)
		r *= -1;
	if (g < 0.0f)
		g *= -1;
	if (b < 0.0f)
		b *= -1;
	if (a < 0.0f)
		a *= -1;

	if (r > 1.0f)
		r /= 255;

	if (g > 1.0f)
		g /= 255;

	if (b > 1.0f)
		b /= 255;

	if (a > 1.0f && a <= 100.0f)
		a /= 100;
	else if (a > 100.f)
		a /= 255;

	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
	this->color[3] = a;
}

void LightSource::setLightIndex(GLenum lightIndex)
{
	switch (lightIndex) {
	case GL_LIGHT0:
	case GL_LIGHT1:
	case GL_LIGHT2:
	case GL_LIGHT3:
	case GL_LIGHT4:
	case GL_LIGHT5:
	case GL_LIGHT6:
	case GL_LIGHT7:
		this->lightIndex = lightIndex;
		break;
	default:
		break;
	}
}

void LightSource::applyLight() {
	if (isEnabled()) {
		glEnable(lightIndex); // Użyj zmiennej lightIndex
		GLfloat lightPosition[] = { static_cast<GLfloat>(position.getX()),
									static_cast<GLfloat>(position.getY()*10),
									static_cast<GLfloat>(position.getZ()), 1.0f };
		glLightfv(lightIndex, GL_POSITION, lightPosition); // Użyj lightIndex zamiast GL_LIGHT0
		glLightfv(lightIndex, GL_DIFFUSE, color); // Ustaw kolor światła
	}
	else {
		glDisable(lightIndex); // Wyłącz światło
	}
}

bool LightSource::isEnabled()
{
	return this->enabled;
}
