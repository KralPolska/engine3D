#pragma once
#include <vector>
#include <GL/freeglut.h>
#include <cmath>
class point3d
{
private:
	double x;
	double y;
	double z;
public:
	point3d() :x(0.0), y(0.0), z(0.0) {}

	point3d(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	double getX() const;
	double getY() const;
	double getZ() const;

	void setX(double x);
	void setY(double y);
	void setZ(double z);

	std::vector<double> getPosition();
	void setPosition(point3d point);

public:
	point3d operator+(const point3d& other) const
	{
		return point3d(x + other.x, y + other.y, z + other.z);
	}

	point3d& operator+=(const point3d& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	point3d operator-(const point3d& other) const
	{
		return point3d(x - other.x, y - other.y, z - other.z);
	}

	point3d operator-() const
	{
		return point3d(-x, -y, -z);
	}

	point3d& operator-=(const point3d& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	point3d operator*(const point3d& other) const
	{
		return point3d(x * other.x, y * other.y, z * other.z);
	}

	point3d operator*(double scalar) const
	{
		return point3d(x * scalar, y * scalar, z * scalar);
	}

	point3d& operator*=(const point3d& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	point3d operator/(const point3d& other) const
	{
		return point3d(x / other.x, y / other.y, z / other.z);
	}

	point3d& operator/=(const point3d& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	point3d& operator=(const point3d& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	double length() const {
		return std::sqrt(this->x * this->x + y * y + z * z);
	}

	point3d normalize() const {
		double length = std::sqrt(x * x + y * y + z * z);

		if (length != 0.0) {
			return point3d(x / length, y / length, z / length);
		}
		else {
			// Zabezpieczenie przed dzieleniem przez zero (wektor zerowy)
			return *this;
		}
	}

	point3d crossProduct(const point3d& other) const {
		return point3d(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}
};
