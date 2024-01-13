#pragma once
#include "point3d.h"
#include "LightSource.h"
#include <GL/freeglut.h>
class camera
{
private:
	point3d cameraPosition;
	point3d cameraOrientation;
	point3d cameraUp;
	int lastMouseX;
	int lastMouseY;
	double sensitivity;
public:
	LightSource sun;

public:
	camera();
	void setCameraPosition(point3d point);
	void setCameraLook(point3d point);
	void setCameraUp(point3d point);
	void setCamera(const point3d& position, const point3d& look, const point3d& up);
	void applyView();
	void moveLeft(double distance);
	void moveRight(double distance);
	void moveForward(double distance);
	void moveBackward(double distance);
	void rotate(double x, double y);
	void rotateVectorY(point3d& vec, double angle);
	void rotateVector(point3d& vec, double angle, const point3d& axis);
	void setSensitivity(double sensitivity);
	double getSensitivity();
};

