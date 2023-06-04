#include "CubeVisual.h"

void CubeVisual::rotateBackFront() {
    int temp = colorsVisual[5];
    colorsVisual[5] = colorsVisual[3];
    colorsVisual[3] = colorsVisual[4];
    colorsVisual[4] = colorsVisual[2];
    colorsVisual[2] = temp;
}

void CubeVisual::rotateDownUp() {
    int temp = colorsVisual[0];
    colorsVisual[0] = colorsVisual[4];
    colorsVisual[4] = colorsVisual[1];
    colorsVisual[1] = colorsVisual[5];
    colorsVisual[5] = temp;
}

void CubeVisual::rotateLeftRight() {
    int temp = colorsVisual[2];
    colorsVisual[2] = colorsVisual[1];
    colorsVisual[1] = colorsVisual[3];
    colorsVisual[3] = colorsVisual[0];
    colorsVisual[0] = temp;
}

void CubeVisual::setColor(int i, int color) {
    this->colorsVisual[i] = color;
}

void CubeVisual::setEdge(GLfloat size) {
    this->sizeEdge = size;
}

unsigned char* CubeVisual::getRGB(int i) {
    RGB[0] = colorsVisual[i] >> 16;
    RGB[1] = colorsVisual[i] >> 8;
    RGB[2] = colorsVisual[i];
    return RGB;
}

void CubeVisual::draw() {
    //Saving current coordinates
    glPushMatrix();
    glBegin(GL_QUADS);

    //Up plane
    glColor3ubv(getRGB(0));
    glNormal3f(0, 0, 1);
    glVertex3f(0, 0, sizeEdge);
    glVertex3f(0, sizeEdge, sizeEdge);
    glVertex3f(sizeEdge, sizeEdge, sizeEdge);
    glVertex3f(sizeEdge, 0, sizeEdge);

    //Down plane
    glColor3ubv(getRGB(1));
    glNormal3f(0, 0, -1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, sizeEdge, 0);
    glVertex3f(sizeEdge, sizeEdge, 0);
    glVertex3f(sizeEdge, 0, 0);

    //Front plane
    glColor3ubv(getRGB(2));
    glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, sizeEdge, 0);
    glVertex3f(sizeEdge, sizeEdge, 0);
    glVertex3f(sizeEdge, 0, 0);

    //Back plane
    glColor3ubv(getRGB(3));
    glNormal3f(0, 1, 0);
    glVertex3f(0, sizeEdge, 0);
    glVertex3f(0, sizeEdge, sizeEdge);
    glVertex3f(sizeEdge, sizeEdge, sizeEdge);
    glVertex3f(sizeEdge, sizeEdge, 0);

    //Left plane
    glColor3ubv(getRGB(4));
    glNormal3f(-1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, sizeEdge);
    glVertex3f(0, sizeEdge, sizeEdge);
    glVertex3f(0, sizeEdge, 0);

    //Right plane
    glColor3ubv(getRGB(5));
    glNormal3f(1, 0, 0);
    glVertex3f(sizeEdge, 0, 0);
    glVertex3f(sizeEdge, 0, sizeEdge);
    glVertex3f(sizeEdge, sizeEdge, sizeEdge);
    glVertex3f(sizeEdge, sizeEdge, 0);

    glEnd();
    //Return to the pld coordinates system
    glPopMatrix();
}

void CubeVisual::draw(double x, double y, double z) {
    glPushMatrix();
    glTranslated(x, y, z);
    draw();
    glPopMatrix();
}
