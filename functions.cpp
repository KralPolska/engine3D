#include "functions.h"
#include <cstdlib>
#include <ctime>
#include <string>

KeyBinder functions::keyBinder;
std::vector<std::shared_ptr<object3d>> functions::objects3D;
unsigned char functions::iterationCount = 0;

extern camera myCamera;

bool enableLight = false;

void functions::init() {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND); //T
    glutMotionFunc(mouseMotionHandler);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutTimerFunc(1000, timer, 0);
    drawFloorAndSky();
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

    myCamera.sun.setPosition(point3d(10.0, 1.0f, 0.0));  // Ustaw pozycję słońca
    myCamera.sun.setColor(1.0f, 1.0f, 3.0f, 0.3f);         // Ustaw kolor światła słońca (biały
    myCamera.sun.applyLight();

    //glUseProgram do shaderów i cieniowania
    //glew podpiąć

    drawObjects();
    drawCube();
    WHERETHEFUCKISLIGHT();
    glutSwapBuffers();
}

void functions::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);

    myCamera.sun.applyLight();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

void functions::addRandomObject() {
    srand(time(NULL));
    double radius = 0.5; // Możesz dostosować promień do własnych preferencji
    double randomX = rand() % 20 - 10;
    double randomY = rand() % 10+2;
    double randomZ = rand() % 20 - 10;
    std::cout << "\n[" << randomX << " | " << randomY << " | " << randomZ << "]\n";

    // Random color
    float r = static_cast<float>(rand()) / 255;
    float g = static_cast<float>(rand()) / 255;
    float b = static_cast<float>(rand()) / 255;
    float a = rand() % 99 + 1;
    // Losowy wybór klasy obiektu
    int randomClass = rand() % 2 + 1;  // Zakładam, że masz dwie klasy dziedziczące po object3d
    std::cout << randomClass << " ";
    std::shared_ptr<object3d> newObject;

    // Tworzenie obiektu na podstawie losowego wyboru
    if (randomClass == 1) {
        newObject = std::make_shared<primitive_Circle>(radius,Material::Glass);
    }
    else if (randomClass == 2) {
        newObject = std::make_shared<primitive_Box>(1.0, 3.0, 1.0,Material::Glass);
    }

    newObject->setPosition({ randomX, randomY, randomZ });
    newObject->setColor(r, g, b, a);
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
    keyBinder.bindKey('l', [&]()
        {
            enableLight = !enableLight;
            myCamera.sun.enable(enableLight);
        });
}

void functions::drawFloorAndSky() {
    // Ustaw kolor nieba (np. niebieski)
    std::shared_ptr<object3d> floor = std::make_shared<primitive_Box>(20, 20, 0.2,Material::Sand);
    floor->setColor(0, 255, 0, 1.0f);
    floor->setPosition({ 0,-1,0 });
    objects3D.push_back(floor);

    std::shared_ptr<object3d> sky = std::make_shared<primitive_Box>(20, 20, 0.2,Material::Water);
    sky->setColor(0, 10, 200, 1.0f);
    sky->setPosition({ 0,20,0 });
    objects3D.push_back(sky);

    std::shared_ptr<object3d> klocek = std::make_shared<primitive_Box>(1, 1, 1,Material::Metal);
    klocek->setColor(255, 0, 0, 1.0f);
    klocek->setPosition({ 10,1,0 });
    //objects3D.push_back(klocek);
}

void functions::timer(int value)
{
    addRandomObject();
    iterationCount++;

    if (iterationCount < 10) {
        glutTimerFunc(1000, timer, 0);
    }
}

void functions::WHERETHEFUCKISLIGHT()
{
    //for (int i = -25; i < 25; i+=2)
    //{
    //    std::shared_ptr<object3d> kolo = std::make_shared<primitive_Circle>(1.0, Material::Water);
    //    kolo->setColor(255, 255, 0);
    //    kolo->setPosition(point3d(i, 1.0, 0));
    //    objects3D.push_back(kolo);  
    //    std::shared_ptr<object3d> kolo2 = std::make_shared<primitive_Circle>(1.0, Material::Water);
    //    kolo2->setColor(0, 255, 255);
    //    kolo2->setPosition(point3d(0, 1.0, i));
    //    objects3D.push_back(kolo2);        
    //    std::shared_ptr<object3d> kolo3 = std::make_shared<primitive_Circle>(1.0, Material::Water);
    //    kolo3->setColor(255, 0, 255);
    //    kolo3->setPosition(point3d(0, i, 0));
    //    objects3D.push_back(kolo3);
    //}
        //std::shared_ptr<object3d> krechax = std::make_shared<primitive_Box>(30, 0.1, 0.1,Material::Glass);
        //std::shared_ptr<object3d> krechay = std::make_shared<primitive_Box>(0.1, 0.1, 30, Material::Glass);
        //std::shared_ptr<object3d> krechaz = std::make_shared<primitive_Box>(0.1, 30, 0.1,Material::Glass);
        //krechax->setColor(255, 0, 0);
        //krechay->setColor(0, 255, 0);
        //krechaz->setColor(0, 0, 255);

        //krechax->setPosition({ 0,0,-15 });
        //krechay->setPosition({ 0,-15,0 });
        //krechaz->setPosition({ -15,0,0 });

        //objects3D.push_back(krechax);
        //objects3D.push_back(krechay);
        //objects3D.push_back(krechaz);

        glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        glBegin(GL_LINES);

        // Red X axis
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(5, 0.0f, 0.0f);

        // Green Y axis
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 5, 0.0f);

        // Blue Z axis
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 5);

        glEnd();

        glPopAttrib();
}