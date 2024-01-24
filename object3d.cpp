#include "object3d.h"

void object3d::setColor(float r, float g, float b, float a) {
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


void object3d::applyMaterial() const{
    glDisable(GL_LIGHTING);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    this->material.apply();
    glEnable(GL_LIGHTING);
}

primitive_Circle::primitive_Circle(double radius, Material type) : radius(radius) {
    this->material = getMaterial(type);
    this->rotation = 0;
    this->o_scale = 1;
    this->rotationVector = { 0,0,0 };
}
primitive_Circle::primitive_Circle(double radius) : radius(radius) {
    this->material = getMaterial(Material::Default);
    this->rotation = 0;
    this->o_scale = 1;
    this->rotationVector = { 0,0,0 };
}

void primitive_Circle::draw() const {
    const int slices = 30;
    const int stacks = 30;
    applyMaterial();

    glPushMatrix(); // Zapisz obecne przekształcenia
    glTranslatef(position.getX(), position.getY(), position.getZ());
    glRotated(rotation, rotationVector.getX(), rotationVector.getY(), rotationVector.getZ()); // Obrót
    glScaled(o_scale, o_scale, o_scale); // Skalowanie

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < stacks; ++i) {
        double phi1 = i * PI / stacks;
        double phi2 = (i + 1) * PI / stacks;
         
        for (int j = 0; j < slices; ++j) {
            double theta1 = j * 2 * PI / slices;
            double theta2 = (j + 1) * 2 * PI / slices;

            // Vertices
            double x1 = position.getX() + radius * std::sin(phi1) * std::cos(theta1);
            double y1 = position.getY() + radius * std::sin(phi1) * std::sin(theta1);
            double z1 = position.getZ() + radius * std::cos(phi1);

            double x2 = position.getX() + radius * std::sin(phi1) * std::cos(theta2);
            double y2 = position.getY() + radius * std::sin(phi1) * std::sin(theta2);
            double z2 = position.getZ() + radius * std::cos(phi1);

            double x3 = position.getX() + radius * std::sin(phi2) * std::cos(theta1);
            double y3 = position.getY() + radius * std::sin(phi2) * std::sin(theta1);
            double z3 = position.getZ() + radius * std::cos(phi2);

            double x4 = position.getX() + radius * std::sin(phi2) * std::cos(theta2);
            double y4 = position.getY() + radius * std::sin(phi2) * std::sin(theta2);
            double z4 = position.getZ() + radius * std::cos(phi2);

            point3d normal1 = { x1 - position.getX(), y1 - position.getY(), z1 - position.getZ() };
            normal1 = normal1.normalize();
            point3d normal2 = { x2 - position.getX(), y2 - position.getY(), z2 - position.getZ() };
            normal2 = normal2.normalize();
            point3d normal3 = { x3 - position.getX(), y3 - position.getY(), z3 - position.getZ() };
            normal3 = normal3.normalize();
            point3d normal4 = { x4 - position.getX(), y4 - position.getY(), z4 - position.getZ() };
            normal4 = normal4.normalize();

            // Draw two triangles
            glNormal3d(normal1.getX(), normal1.getY(), normal1.getZ());
            glVertex3d(x1, y1, z1);

            glNormal3d(normal2.getX(), normal2.getY(), normal2.getZ());
            glVertex3d(x2, y2, z2);

            glNormal3d(normal4.getX(), normal4.getY(), normal4.getZ());
            glVertex3d(x4, y4, z4);

            glNormal3d(normal1.getX(), normal1.getY(), normal1.getZ());
            glVertex3d(x1, y1, z1);

            glNormal3d(normal4.getX(), normal4.getY(), normal4.getZ());
            glVertex3d(x4, y4, z4);

            glNormal3d(normal3.getX(), normal3.getY(), normal3.getZ());
            glVertex3d(x3, y3, z3);
        }
    }
    glEnd();
    glPopMatrix();
}

void primitive_Circle::setPosition(const point3d& newPosition) {
    position = newPosition;
}

point3d primitive_Circle::getPosition()
{
    return position;
}

void primitive_Circle::rotate(double angle, const point3d& axis) {
    this->rotation += angle;
    if (rotation > 360)
        rotation -= 360;
    this->rotationVector = axis;
}

void primitive_Circle::translate(const point3d& translation) {
    this->position += translation;
}

void primitive_Circle::scale(double scale)
{
    this->o_scale *= scale;
}

void primitive_Circle::rescale(double scale)
{
    this->o_scale = scale;
}

void primitive_Circle::resize(double depth, double width, double height)
{
    this->radius = depth;
}

void primitive_Circle::resize(double radius)
{
    this->radius = radius;
}

void primitive_Circle::size(double size)
{
    this->radius += size;
}

void primitive_Circle::size(double depth, double width, double height)
{
    this->radius += depth;
}

primitive_Box::primitive_Box(double length, double width, double height, Material type)
    : depth(length), width(width), height(height) {
    this->material = getMaterial(type);
    this->rotation = 0;
    this->rotationVector = { 0,0,0 };
    this->o_scale = 1;
}
primitive_Box::primitive_Box(double length, double width, double height)
    : depth(length), width(width), height(height) {
    this->material = getMaterial(Material::Default);
    this->rotation = 0;
    this->rotationVector = { 0,0,0 };
    this->o_scale = 1;
}

void primitive_Box::draw() const {
    applyMaterial(); // Zastosowanie właściwości materiału

    double halfWidth = (width * o_scale) / 2.0;
    double halfHeight = (height * o_scale) / 2.0;
    double halfDepth = (depth * o_scale) / 2.0;

    double xMin = position.getX() - halfWidth;
    double xMax = position.getX() + halfWidth;
    double yMin = position.getY() - halfHeight;
    double yMax = position.getY() + halfHeight;
    double zMin = position.getZ() - halfDepth;
    double zMax = position.getZ() + halfDepth;

    glPushMatrix();
    glTranslatef(position.getX(), position.getY(), position.getZ());
    glRotated(rotation, rotationVector.getX(), rotationVector.getY(), rotationVector.getZ());
    glTranslatef(-position.getX(), -position.getY(), -position.getZ());
    glScaled(o_scale, o_scale, o_scale);

    glBegin(GL_QUADS);

    // Przednia ściana
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3d(xMin, yMin, zMin);
    glVertex3d(xMax, yMin, zMin);
    glVertex3d(xMax, yMax, zMin);
    glVertex3d(xMin, yMax, zMin);

    // Tylna ściana
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3d(xMin, yMin, zMax);
    glVertex3d(xMax, yMin, zMax);
    glVertex3d(xMax, yMax, zMax);
    glVertex3d(xMin, yMax, zMax);

    // Lewa ściana
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3d(xMin, yMin, zMin);
    glVertex3d(xMin, yMax, zMin);
    glVertex3d(xMin, yMax, zMax);
    glVertex3d(xMin, yMin, zMax);

    // Prawa ściana
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3d(xMax, yMin, zMin);
    glVertex3d(xMax, yMax, zMin);
    glVertex3d(xMax, yMax, zMax);
    glVertex3d(xMax, yMin, zMax);

    // Górna ściana
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3d(xMin, yMax, zMin);
    glVertex3d(xMax, yMax, zMin);
    glVertex3d(xMax, yMax, zMax);
    glVertex3d(xMin, yMax, zMax);

    // Dolna ściana
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3d(xMin, yMin, zMin);
    glVertex3d(xMax, yMin, zMin);
    glVertex3d(xMax, yMin, zMax);
    glVertex3d(xMin, yMin, zMax);

    glEnd();

    glPopMatrix();
}


void primitive_Box::setPosition(const point3d& newPosition) {
    position = newPosition;
}

point3d primitive_Box::getPosition()
{
    return position;
}

void primitive_Box::rotate(double angle, const point3d& axis) {
    this->rotation += angle;
    if (rotation > 360)
        rotation -= 360;
    this->rotationVector = axis;
}

void primitive_Box::translate(const point3d& translation) {
    this->position += translation;
}

void primitive_Box::scale(double scale)
{
    this->o_scale *= scale;
}

void primitive_Box::rescale(double scale)
{
    this->o_scale = scale;
}

void primitive_Box::resize(double depth, double width, double height)
{
    this->depth = depth;
    this->width = width;
    this->height = height;
}

void primitive_Box::resize(double radius)
{
    this->depth = radius;
    this->width = radius;
    this->height = radius;
}

void primitive_Box::size(double depth, double width, double height)
{
    this->depth += depth;
    this->width += width;
    this->height += height;
}

void primitive_Box::size(double size)
{
    this->depth += size;
    this->width += size;
    this->height += size;

}
