#ifndef RUBIKCUBE_VISUALFUNCTIONS_H
#define RUBIKCUBE_VISUALFUNCTIONS_H
#include "RubikConfig.h"

unsigned int colors[6] = {blue, green, white, yellow, orange, red};

void display() {
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glTranslatef(0, 0, translateZ);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glTranslatef(CUBE_SIZE / -2, CUBE_SIZE / -2, CUBE_SIZE / -2);
    Cube.draw();
    glPopMatrix();
    glutSwapBuffers();
}

void init() {
    // Background color
    glClearColor(0.75, 0.75, 0.75, 0.4);

    // Lighting
    float matSpecular[] = {0.3, 0.3, 0.3, 0};
    float diffuseLight[] = {0.2, 0.2, 0.2, 1};
    float ambientLight[] = {0.9, 0.9, 0.9, 1};
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    // Cube initialization
    Cube.generateVisualCube(CUBE_SIZE, colors);
}

void specialKeys(int key, int, int) {

    if (key == GLUT_KEY_DOWN) {
        xRot -= 10;
        if (xRot >= 360)
            xRot -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_UP) {
        xRot += 10;
        if (xRot < 0)
            xRot += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_RIGHT) {
        yRot -= 10;
        if (yRot >= 360)
            yRot -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_LEFT) {
        yRot += 10;
        if (yRot < 0)
            yRot += 360;
        glutPostRedisplay();
    }

    if (key == '1') {
        Cube.rotateUpPlane(true);
        glutPostRedisplay();
    }

    if (key == '2') {
        Cube.rotateLeftPlane(true);
        glutPostRedisplay();
    }

    if (key == '3') {
        Cube.rotateFrontPlane(true);
        glutPostRedisplay();
    }

    if (key == '4') {
        Cube.rotateRightPlane(true);
        glutPostRedisplay();
    }

    if (key == '5') {
        Cube.rotateBackPlane(true);
        glutPostRedisplay();
    }

    if (key == '6') {
        Cube.rotateDownPlane(true);
        glutPostRedisplay();
    }
}

void timer(int) {
    glutTimerFunc(5, timer, 0);
    if (Cube.getCurrentPlane() != -1)
        Cube.visualRotatePlanes(Cube.getCurrentPlane(), ROTATE_START_VALUE, -1);

    display();
}

void processMenu(int action);

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat) width / (GLfloat) height;
    gluPerspective(60, fAspect, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#endif //RUBIKCUBE_VISUALFUNCTIONS_H
