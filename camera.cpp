#include "camera.h"
#include <GL/freeglut.h>
#include <iostream>

camera::camera()
{
	this->cameraOrientation = { 0,1,0 };
	this->cameraPosition = { 0,0,-3};
	this->cameraUp = { 0,1,0 };
	this->lastMouseX = 0;
	this->lastMouseY = 0;
	this->sensitivity = 0.01;
}

void camera::setCameraPosition(point3d point)
{
	cameraPosition = point;
}

void camera::setCameraLook(point3d point) 
{
	cameraOrientation = point;
}

void camera::setCameraUp(point3d point) 
{
	cameraUp = point;
}

void camera::setCamera(const point3d& position, const point3d& look, const point3d& up) {
	cameraPosition = position;
	cameraOrientation = look;
	cameraUp = up;
	// Ustawienie wektora kierunkowego kamery
	point3d directionVector = look - position;
	directionVector.normalize();
	cameraOrientation = directionVector; // Znormalizowanie i przypisanie

	// Ustawienie wektora "góry" kamery
	up.normalize();
	cameraUp = up;
}


// W klasie camera
void camera::applyView() {
	// Ustawienie punktu obserwatora (kamery)
	double eyeX = cameraPosition.getX();
	double eyeY = cameraPosition.getY();
	double eyeZ = cameraPosition.getZ();

	// Ustawienie punktu, na który patrzy kamera
	double centerX = eyeX + cameraOrientation.getX();
	double centerY = eyeY + cameraOrientation.getY();
	double centerZ = eyeZ + cameraOrientation.getZ();

	// Ustawienie wektora "góry" kamery
	double upX = cameraUp.getX();
	double upY = cameraUp.getY();
	double upZ = cameraUp.getZ();

	// Ustawienie macierzy widoku za pomocą gluLookAt
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}


void camera::moveLeft(double distance) {
	point3d left = cameraOrientation.crossProduct(cameraUp);
	left.normalize();
	point3d distanceVector = { distance, distance, distance };
	left *= distanceVector;
	cameraPosition -= left;

	/*std::cout << "cameraPosition: "
		<< cameraPosition.getX() 
		<< " " << cameraPosition.getY() 
		<< " " << cameraPosition.getZ()		
		<< "\n";
	*/
	// Aktualizacja kierunku patrzenia
	point3d lookAt = cameraPosition + cameraOrientation;
	
	/*std::cout << "lookAt: "
		<< lookAt.getX()
		<< " " << lookAt.getY()
		<< " " << lookAt.getZ()
		<< "\n";
	*/
	setCamera(cameraPosition, lookAt, cameraUp);
}

void camera::moveRight(double distance)
{
	point3d right = cameraUp.crossProduct(cameraOrientation);
	right.normalize();
	point3d distanceVectorRight = { distance, distance, distance };
	right *= distanceVectorRight;
	cameraPosition -= right;
}

void camera::moveForward(double distance)
{
	point3d forward = cameraOrientation;
	forward.normalize();
	point3d distanceVectorForward = { distance, distance, distance };
	forward *= distanceVectorForward;
	cameraPosition += forward;
}

void camera::moveBackward(double distance)
{
	point3d backward = -cameraOrientation;
	backward.normalize();
	point3d distanceVectorBackward = { distance, distance, distance };
	backward *= distanceVectorBackward;
	cameraPosition += backward;

}

void camera::rotate(double angleX, double angleY) {
	// Obrót kamery wokół osi Y
	double cosY = cos(angleX);
	double sinY = sin(angleX);

	point3d right = cameraOrientation.crossProduct(cameraUp);
	right.normalize();

	// Zastosowanie korekty dla osi Y
	double deltaY = -angleY;  // Odwrócenie kierunku ruchu myszy dla osi Y
	cameraOrientation = cameraOrientation * cosY + right * sinY;

	// Obrót kamery wokół osi X
	double cosX = cos(deltaY);
	double sinX = sin(deltaY);

	cameraOrientation = cameraOrientation * cosX + cameraUp * sinX;

	// Normalizacja wektora orientacji kamery
	cameraOrientation.normalize();
}

// Funkcja do obrotu wektora wokół osi Y
void camera::rotateVectorY(point3d& vec, double angle) {
	double cosA = cos(angle);
	double sinA = sin(angle);

	double x = cosA * vec.getX() + sinA * vec.getZ();
	double z = -sinA * vec.getX() + cosA * vec.getZ();

	vec.setX(x);
	vec.setZ(z);
}

// Funkcja do ogólnego obrotu wektora wokół dowolnej osi
void camera::rotateVector(point3d& vec, double angle, const point3d& axis) {
	double cosA = cos(angle);
	double sinA = sin(angle);

	double x = (cosA + (1 - cosA) * axis.getX() * axis.getX()) * vec.getX();
	x += ((1 - cosA) * axis.getX() * axis.getY() - sinA * axis.getZ()) * vec.getY();
	x += ((1 - cosA) * axis.getX() * axis.getZ() + sinA * axis.getY()) * vec.getZ();

	double y = ((1 - cosA) * axis.getX() * axis.getY() + sinA * axis.getZ()) * vec.getX();
	y += (cosA + (1 - cosA) * axis.getY() * axis.getY()) * vec.getY();
	y += ((1 - cosA) * axis.getY() * axis.getZ() - sinA * axis.getX()) * vec.getZ();

	double z = ((1 - cosA) * axis.getX() * axis.getZ() - sinA * axis.getY()) * vec.getX();
	z += ((1 - cosA) * axis.getY() * axis.getZ() + sinA * axis.getX()) * vec.getY();
	z += (cosA + (1 - cosA) * axis.getZ() * axis.getZ()) * vec.getZ();

	// Modyfikacja wartości wektora
	vec.setX(x);
	vec.setY(y);
	vec.setZ(z);
}

void camera::setSensitivity(double sensitivity)
{
	this->sensitivity = sensitivity;
}

double camera::getSensitivity()
{
	return this->sensitivity;
}
