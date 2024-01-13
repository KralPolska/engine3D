#include <GL/freeglut.h>
#include "camera.h"
#include "keyBind.h"
#include "object3d.h"
#include <vector>
#include <functional>
#include <ctime>
#include <iostream>
class functions {
public:
    static KeyBinder keyBinder;  // Deklaracja zmiennej keyBinder
    static std::vector<std::shared_ptr<object3d>> objects3D;
    static unsigned char iterationCount;

public:
    static void init();
    static void drawCube();
    static void display();
    static void reshape(int width, int height);
    static void keyboardHandler(unsigned char key, int x, int y);
    static void mouseMotionHandler(int x, int y);
    static void toggleFullscreen();
    static void exit();
    static void passiveMotionHandler(int x, int y);
    static void drawObjects();
    static void addRandomObject();
    static void initBinds();
    static void drawFloorAndSky();
    static void timer(int value);
    static void WHERETHEFUCKISLIGHT();
};