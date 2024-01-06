#include <GL/freeglut.h>
#include "functions.h"
#include "camera.h"
#include "object3d.h"
// Inicjalizacja obiektu kamery
camera myCamera;
// Inicjalizacja obiektu klasy functions
functions myFunctions;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Prosty program 3D");

    myFunctions.init();  // Inicjalizacja funkcji (inicjalizacja GL_DEPTH_TEST)

    point3d initialPos(0.0, 0.0, -3.0);
    point3d initialLook(0.0, 0.0, 0.0);
    point3d initialUp(0.0, 1.0, 0.0);   

    myCamera.setCamera(initialPos, initialLook, initialUp);

    myFunctions.initBinds();

    glutDisplayFunc(myFunctions.display);
    glutReshapeFunc(myFunctions.reshape);
    glutKeyboardFunc(myFunctions.keyboardHandler);
    glutMotionFunc(myFunctions.mouseMotionHandler);
    glutPassiveMotionFunc(myFunctions.passiveMotionHandler);

    glutTimerFunc(10000, myFunctions.timer, 0);

    glutMainLoop();
    return 0;
}