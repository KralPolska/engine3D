#pragma once
#include <GL/freeglut.h>
#include <algorithm>
#include <iterator>
#include <iostream>
class objectMaterial
{
private:
    GLfloat ambient[4];   // Kolor światła otoczenia
    GLfloat diffuse[4];   // Kolor światła dyfuzyjnego
    GLfloat specular[4];  // Kolor światła spekularnego
    GLfloat shininess;    // Stopień połysku
    GLfloat emission[4];  // Kolor emisyjny

public:
    objectMaterial();
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setShininess(GLfloat s);
    void setEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void apply() const;

    objectMaterial& operator=(const objectMaterial& other) {
        if (this != &other) { // Ochrona przed samoprzypisaniem
            std::copy(std::begin(other.ambient), std::end(other.ambient), std::begin(ambient));
            std::copy(std::begin(other.diffuse), std::end(other.diffuse), std::begin(diffuse));
            std::copy(std::begin(other.specular), std::end(other.specular), std::begin(specular));
            std::copy(std::begin(other.emission), std::end(other.emission), std::begin(emission));
            shininess = other.shininess;
        }
        return *this;
    }
};

enum class Material {
    Default,
    Wood,
    Stone,
    Glass,
    Sand,
    Metal,
    Plastic,
    Water
};

objectMaterial getMaterial(Material type);