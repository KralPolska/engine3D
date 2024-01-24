#pragma once
#include "objectMaterial.h"
#include "point3d.h"
constexpr auto PI = 3.14159265358979323846;
class object3d
{
public:

    int id = 0;

	virtual void draw() const = 0;
	virtual void setPosition(const point3d& position) = 0;
    void setColor(float r, float g, float b, float a);
    virtual point3d getPosition() = 0;
    virtual void rotate(double angle, const point3d& axis) = 0;
    virtual void translate(const point3d& translation) = 0;
    virtual void scale(double scale) = 0;
    virtual void rescale(double scale) = 0;
    virtual void size(double size) = 0;
    virtual void size(double depth, double width, double height) = 0;
    virtual void resize(double radius) = 0;
    virtual void resize(double depth, double width, double height) = 0;
protected:
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    objectMaterial material;
    double rotation;
    point3d rotationVector; 
    double o_scale;
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
    
    void rotate(double angle, const point3d& axis);
    void translate(const point3d& translation);
    void scale(double scale);
    void rescale(double scale);
    void size(double size);
    void size(double depth, double width, double height);
    void resize(double radius);
    void resize(double depth, double width, double height);
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

    void rotate(double angle, const point3d& axis);
    void translate(const point3d& translation);
    void scale(double scale);
    void rescale(double scale);
    void size(double size);
    void size(double depth, double width, double height);
    void resize(double radius);
    void resize(double depth, double width, double height);
};