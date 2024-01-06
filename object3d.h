#pragma once
#include "point3d.h"
constexpr auto PI = 3.14159265358979323846;
class object3d
{
public:
	virtual void draw() const = 0;
	virtual void setPosition(const point3d& position) = 0;
    void setColor(float r, float g, float b);

protected:
    float color[3] = { 1.0f, 1.0f, 1.0f };
};

class primitive_Circle : public object3d
{
private:
    double radius;
    point3d position;
public:
    primitive_Circle(double radius);
    void draw() const override;
    void setPosition(const point3d& position) override;
};

class primitive_Box : public object3d
{
private:
    double depth, width, height;
    point3d position;
public:
    primitive_Box(double length, double width, double height);
    void draw() const override;
    void setPosition(const point3d& position) override;
};