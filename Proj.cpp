#include <glut.h>

// ---------------------------------------------------------
// Constants
// ---------------------------------------------------------
// PLAYER STATE
float playerX = 0.0f;
float playerY = 0.5f;     // height above ground
float playerZ = 2.0f;     // start slightly forward on the street
float playerRot = 0.0f;   // rotation (used later)

 
 

// ---------------------------------------------------------
// VARIABLES
// ---------------------------------------------------------
float rotAng = 0;

// ---------------------------------------------------------
// LEVEL 1 - BASIC ENVIRONMENT (Street + Buildings)
// ---------------------------------------------------------

void DrawStreet() {
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);      // dark gray road
    glScalef(1.0f, 0.05f, 20.0f);     // long street
    glutSolidCube(1.0);
    glPopMatrix();
}

void DrawBuilding(float x, float z, float height) {
    glPushMatrix();
    glTranslatef(x, height / 2.0f, z);

    glColor3f(0.4f, 0.4f, 0.9f);      // blue building placeholder

    glScalef(1.0f, height, 1.0f);     // stretch cube upwards
    glutSolidCube(1.0);
    glPopMatrix();
}

void DrawBuildings() {
    // Left row
    for (float z = -15; z <= 15; z += 5) {
        DrawBuilding(-2.5f, z, 3.0f);
    }

    // Right row
    for (float z = -15; z <= 15; z += 5) {
        DrawBuilding(2.5f, z, 2.5f);
    }
}

// ---------------------------------------------------------
// LIGHTING
// ---------------------------------------------------------

void SetupLights() {
    // ---- Global ambient (soft city glow) ----
    GLfloat globalAmbient[] = { 0.2f, 0.2f, 0.25f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    // ---- Light 0: directional sky light ----
    GLfloat light0_diffuse[] = { 0.4f, 0.4f, 0.45f, 1.0f };
    GLfloat light0_specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat light0_position[] = { -1.0f, 1.0f, -0.5f, 0.0f };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    // ---- Light 1: Neon blue light ----
    GLfloat neon_diffuse[] = { 0.0f, 0.6f, 1.0f, 1.0f };
    GLfloat neon_position[] = { 2.0f, 2.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT1, GL_DIFFUSE, neon_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, neon_position);
}

// ---------------------------------------------------------
// Player
// ---------------------------------------------------------
void DrawPlayer() {
    glPushMatrix();

    // Position the player
    glTranslatef(playerX, playerY, playerZ);

    // Color placeholder (bright cyan)
    glColor3f(0.0f, 1.0f, 1.0f);

    // Simple player model now → cube
    glScalef(0.5f, 1.0f, 0.5f);   // taller shape
    glutSolidCube(1.0);

    glPopMatrix();
}

// ---------------------------------------------------------
// DISPLAY FUNCTION
// ---------------------------------------------------------

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera for Level 1 (static for now)
    gluLookAt(0.0f, 3.0f, 6.0f,     // camera pos
        0.0f, 0.0f, 0.0f,     // look-at target
        0.0f, 1.0f, 0.0f);    // up-direction

    // Setup lighting each frame
    SetupLights();

    // Draw the environment
    DrawStreet();
    DrawBuildings();
    DrawPlayer();


    glutSwapBuffers();
}

// ---------------------------------------------------------
// ANIMATION FUNCTION
// ---------------------------------------------------------

void Anim() {
    rotAng += 0.01;
    glutPostRedisplay();
}

// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(150, 150);

    // DOUBLE BUFFERING IMPORTANT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("Cyber City Chase - Level 1 Start");

    glutDisplayFunc(Display);
    glutIdleFunc(Anim);

    glClearColor(0.0f, 0.0f, 0.05f, 1.0f);  // very dark blue background

    glEnable(GL_DEPTH_TEST);

    // ---- Enable lighting ----
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // ---- Projection ----
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 300.0f);

    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();
    return 0;
}
