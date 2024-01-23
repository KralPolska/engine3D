#pragma once
#include "point3d.h"
#include "objectMaterial.h"

constexpr auto PI = 3.14159265358979323846;
class object3d
{
public:
	virtual void draw() const = 0;
	virtual void setPosition(const point3d& position) = 0;
    void setColor(float r, float g, float b, float a);
    virtual point3d getPosition() = 0;
protected:
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    objectMaterial material;
    void applyMaterial() const;
};

class primitive_Circle : public object3d
{
private:
    double radius;
    point3d position;
public:
    primitive_Circle(double radius, Material type);
    primitive_Circle(double radius);
    void draw() const override;
    void setPosition(const point3d& position) override;
    point3d getPosition();
};

class primitive_Box : public object3d
{
private:
    double depth, width, height;
    point3d position;
public:
    primitive_Box(double length, double width, double height, Material type);
    primitive_Box(double length, double width, double height);
    void draw() const override;
    void setPosition(const point3d& position) override;
    point3d getPosition();
};