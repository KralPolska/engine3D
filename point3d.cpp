#include "point3d.h"
#include "cmath"
double point3d::getX() const
{
	return this->x;
}
double point3d::getY() const
{
	return this->y;
}

double point3d::getZ() const
{
	return this->z;
}

void point3d::setX(double x)
{
	this->x = x;
}
void point3d::setY(double y)
{
	this->y = y;
}
void point3d::setZ(double z)
{
	this->z = z;
}

std::vector<double> point3d::getPosition()
{
	std::vector<double> point;
	point.push_back(this->x);
	point.push_back(this->y);
	point.push_back(this->z);
	return point;
}

void point3d::setPosition(point3d point)
{
	this->x = point.getX();
	this->y = point.getY();
	this->z = point.getZ();
}

