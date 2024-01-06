#include "functions.h"
#include <cstdlib>
#include <ctime>
#include <string>

KeyBinder functions::keyBinder;
std::vector<std::shared_ptr<object3d>> functions::objects3D;
unsigned char functions::iterationCount = 0;

extern camera myCamera;

void functions::init() {
    glEnable(GL_DEPTH_TEST);
    glutMotionFunc(mouseMotionHandler);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutTimerFunc(1000, timer, 0);
}

void functions::drawCube() {
    glutWireCube(1.0);
}

void functions::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Przykładowy tekst
    std::string objectCountText = "Liczba obiektow: " + std::to_string(objects3D.size());

    glColor3f(1.0f, 1.0f, 1.0f);  // Biały kolor tekstu
    glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - 20);

    for (char& character : objectCountText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, character);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    myCamera.applyView();
    drawFloorAndSky();
    drawObjects();
    drawCube();

    glutSwapBuffers();
}

void functions::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
}

void functions::keyboardHandler(unsigned char key, int x, int y) {
    keyBinder.handleKeyPress(key);
    glutPostRedisplay();
}

void functions::mouseMotionHandler(int x, int y) {
    static int lastX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    static int lastY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    int deltaX = x - lastX;
    int deltaY = y - lastY;

    // Normalizacja i ograniczenie prędkości ruchu myszy
    const double sensitivityX = myCamera.getSensitivity();
    const double sensitivityY = myCamera.getSensitivity();  // Dostosuj do własnych preferencji
    const double maxSpeed = 5.0;  // Dostosuj do własnych preferencji
    deltaX = std::min(std::max(deltaX * sensitivityX, -maxSpeed), maxSpeed);
    deltaY = std::min(std::max(deltaY * sensitivityY, -maxSpeed), maxSpeed);

    // Obrót kamery na podstawie ruchu myszy
    myCamera.rotate(deltaX, -deltaY);

    // Aktualizacja ostatnich pozycji myszy
    lastX = x;
    lastY = y;

    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);  // Ustawianie kursora myszy na środek okna
    glutPostRedisplay();  // Wymuszenie ponownego rysowania
}

void functions::toggleFullscreen() {
    if (glutGet(GLUT_WINDOW_WIDTH) == glutGet(GLUT_SCREEN_WIDTH) &&
        glutGet(GLUT_WINDOW_HEIGHT) == glutGet(GLUT_SCREEN_HEIGHT)) {
        // Jeżeli jesteśmy już w trybie pełnoekranowym, zmień na okno normalne
        glutReshapeWindow(800, 600);  // Dostosuj rozmiary do własnych preferencji
        glutPositionWindow(100, 100); // Dostosuj pozycję do własnych preferencji
    }
    else {
        // Jeżeli nie jesteśmy w trybie pełnoekranowym, przełącz na pełny ekran
        glutFullScreen();
    }
}

void functions::exit()
{
    glutExit();
}

void functions::passiveMotionHandler(int x, int y) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Obliczenia kątów obrotu na podstawie różnicy pozycji myszy
    double angleX = (x - windowWidth / 2.0) * myCamera.getSensitivity();
    double angleY = (y - windowHeight / 2.0) * myCamera.getSensitivity();

    // Obrót kamery
    myCamera.rotate(angleX, angleY);

    // Opcjonalnie można zresetować pozycję myszy do środka okna
    glutWarpPointer(windowWidth / 2, windowHeight / 2);
    glutPostRedisplay();  // Wymuszenie ponownego rysowania
}

double randDouble(double min, double max) {
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}
void functions::addRandomObject() {
    srand(time(NULL));
    double radius = 0.5; // Możesz dostosować promień do własnych preferencji
    double randomX = randDouble(-5.0, 5.0);
    double randomY = randDouble(-1.0, 1.0);
    double randomZ = randDouble(-5.0, 5.0);

    // Random color
    float r = static_cast<float>(rand()) / 255;
    float g = static_cast<float>(rand()) / 255;
    float b = static_cast<float>(rand()) / 255;

    // Losowy wybór klasy obiektu
    int randomClass = rand() % 2+1;  // Zakładam, że masz dwie klasy dziedziczące po object3d
    std::cout << randomClass << " ";
    std::shared_ptr<object3d> newObject;

    // Tworzenie obiektu na podstawie losowego wyboru
    if (randomClass == 1) {
        newObject = std::make_shared<primitive_Circle>(radius);
    }
    else if (randomClass == 2) {
        newObject = std::make_shared<primitive_Box>(1.0, 3.0, 1.0);
    }

    newObject->setPosition({ randomX, randomY, randomZ });
    newObject->setColor(r, g, b);
    objects3D.push_back(newObject);
}

void functions::drawObjects()
{
    for (const auto& obj : objects3D)
        obj->draw();
}

void functions::initBinds()
{
    keyBinder.bindKey('a', [&]() {
        myCamera.moveLeft(0.1); // Przesunięcie kamery o 0.1 jednostki w lewo
        });
    keyBinder.bindKey('d', [&]() {
        myCamera.moveRight(0.1);
        });
    keyBinder.bindKey('w', [&]() {
        myCamera.moveForward(0.1); // Przesunięcie kamery o 0.1 jednostki w lewo
        });
    keyBinder.bindKey('s', [&]() {
        myCamera.moveBackward(0.1);
        });
    keyBinder.bindKey('f', [&]() {
        toggleFullscreen();
        });
    keyBinder.bindKey(27, [&]() {
        exit();
        });
    keyBinder.bindKey('q', [&]()
        {
            myCamera.rotate(-0.1, 0);
        });
    keyBinder.bindKey('e', [&]()
        {
            myCamera.rotate(0.1, 0);
        });
    keyBinder.bindKey('r', [&]() {
        addRandomObject();
        });
    keyBinder.bindKey('p', addRandomObject);
}

void functions::drawFloorAndSky() {
    // Ustaw kolor nieba (np. niebieski)
    glColor3f(0.5, 0.7, 1.0);  // RGB: (0.5, 0.7, 1.0) - przykładowy kolor nieba

    glBegin(GL_QUADS);
    glVertex3f(-10.0, 50.0, -10.0);
    glVertex3f(-10.0, 50.0, 10.0);
    glVertex3f(10.0, 50.0, 10.0);
    glVertex3f(10.0, 50.0, -10.0);
    glEnd();

    // Ustaw kolor podłogi (np. zielony)
    glColor3f(0.0, 0.3, 0.0);  // RGB: (0.0, 1.0, 0.0) - przykładowy kolor podłogi

    glBegin(GL_QUADS);
    glVertex3f(-10.0, -1.0, -10.0);
    glVertex3f(-10.0, -1.0, 10.0);
    glVertex3f(10.0, -1.0, 10.0);
    glVertex3f(10.0, -1.0, -10.0);
    glEnd();
}

void functions::timer(int value)
{
    addRandomObject();
    iterationCount++;

    if (iterationCount < 10) {
        glutTimerFunc(1000, timer, 0);
    }
}
