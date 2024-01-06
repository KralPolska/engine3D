#include "object3d.h"

void object3d::setColor(float r, float g, float b) {
    color[0] = r/255;
    color[1] = g/255;
    color[2] = b/255;
}

primitive_Circle::primitive_Circle(double radius) : radius(radius) {}

void primitive_Circle::draw() const {
    const int slices = 30;
    const int stacks = 30;
    glColor3fv(color);

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

            // Draw two triangles
            glVertex3d(x1, y1, z1);
            glVertex3d(x2, y2, z2);
            glVertex3d(x4, y4, z4);

            glVertex3d(x1, y1, z1);
            glVertex3d(x4, y4, z4);
            glVertex3d(x3, y3, z3);
        }
    }

    glEnd();
}

void primitive_Circle::setPosition(const point3d& newPosition) {
    position = newPosition;
}

primitive_Box::primitive_Box(double length, double width, double height)
    : depth(length), width(width), height(height) {}

void primitive_Box::draw() const {
    glColor3fv(color);

    // Obliczenia dla współrzędnych prostopadłościanu
    double halfWidth = width / 2.0;
    double halfHeight = height / 2.0;
    double halfDepth = depth / 2.0;

    double xMin = position.getX() - halfWidth;
    double xMax = position.getX() + halfWidth;
    double yMin = position.getY() - halfHeight;
    double yMax = position.getY() + halfHeight;
    double zMin = position.getZ() - halfDepth;
    double zMax = position.getZ() + halfDepth;

    glBegin(GL_QUADS);

    // Przednia ściana
    glVertex3d(xMin, yMin, zMin);
    glVertex3d(xMax, yMin, zMin);
    glVertex3d(xMax, yMax, zMin);
    glVertex3d(xMin, yMax, zMin);

    // Tylna ściana
    glVertex3d(xMin, yMin, zMax);
    glVertex3d(xMax, yMin, zMax);
    glVertex3d(xMax, yMax, zMax);
    glVertex3d(xMin, yMax, zMax);

    // Pozostałe ściany
    glVertex3d(xMin, yMin, zMin);
    glVertex3d(xMin, yMax, zMin);
    glVertex3d(xMin, yMax, zMax);
    glVertex3d(xMin, yMin, zMax);

    glVertex3d(xMax, yMin, zMin);
    glVertex3d(xMax, yMax, zMin);
    glVertex3d(xMax, yMax, zMax);
    glVertex3d(xMax, yMin, zMax);

    glVertex3d(xMin, yMin, zMin);
    glVertex3d(xMax, yMin, zMin);
    glVertex3d(xMax, yMin, zMax);
    glVertex3d(xMin, yMin, zMax);

    glVertex3d(xMin, yMax, zMin);
    glVertex3d(xMax, yMax, zMin);
    glVertex3d(xMax, yMax, zMax);
    glVertex3d(xMin, yMax, zMax);

    glEnd();
}

void primitive_Box::setPosition(const point3d& newPosition) {
    position = newPosition;
}