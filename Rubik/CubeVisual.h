#ifndef RUBIKCUBE_CUBEVISUAL_H
#define RUBIKCUBE_CUBEVISUAL_H

#include "RubikConfig.h"


class CubeVisual {
private:
    //Array used for representing colors in RGB
    unsigned char RGB[3];
    //colors used for visual of six sides of Rubik's Cube
    int colorsVisual[6];
    //Size of each edge
    GLfloat sizeEdge;
public:
    //Rotation of each piece
    void rotateBackFront() {
        int temp = colorsVisual[5];
        colorsVisual[5] = colorsVisual[3];
        colorsVisual[3] = colorsVisual[4];
        colorsVisual[4] = colorsVisual[2];
        colorsVisual[2] = temp;
    }

    void rotateDownUp() {
        int temp = colorsVisual[0];
        colorsVisual[0] = colorsVisual[4];
        colorsVisual[4] = colorsVisual[1];
        colorsVisual[1] = colorsVisual[5];
        colorsVisual[5] = temp;
    }

    void rotateLeftRight() {
        int temp = colorsVisual[2];
        colorsVisual[2] = colorsVisual[1];
        colorsVisual[1] = colorsVisual[3];
        colorsVisual[3] = colorsVisual[0];
        colorsVisual[0] = temp;
    }

    //Setter of colors
    void setColor(int i, int color) {
        this->colorsVisual[i] = color;
    }

    //Setter of sizeEdge
    void setEdge(GLfloat size) {
        this->sizeEdge = size;
    }

    //Getter of RGB representation of color (0xFFFFFF -> [FF, FF, FF])
    unsigned char* getRGB(int i) {
        RGB[0] = colorsVisual[i] >> 16;
        RGB[1] = colorsVisual[i] >> 8;
        RGB[2] = colorsVisual[i];
        return RGB;
    }

    //Drawing Rubik's Cube, or rather setting colors and normals for each plane
    void draw() {
        //Saving current coordinates
        glPushMatrix();
        glBegin(GL_QUADS);

        //Front plane
        glColor3ubv(getRGB(0));
        glNormal3f(0, 0, 1);
        glVertex3f(0, 0, sizeEdge);
        glVertex3f(0, sizeEdge, sizeEdge);
        glVertex3f(sizeEdge, sizeEdge, sizeEdge);
        glVertex3f(sizeEdge, 0, sizeEdge);

        //Back plane
        glColor3ubv(getRGB(1));
        glNormal3f(0, 0, -1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, sizeEdge, 0);
        glVertex3f(sizeEdge, sizeEdge, 0);
        glVertex3f(sizeEdge, 0, 0);

        //Down plane
        glColor3ubv(getRGB(2));
        glNormal3f(0, -1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, sizeEdge);
        glVertex3f(sizeEdge, 0, sizeEdge);
        glVertex3f(sizeEdge, 0, 0);

        //Up plane
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
        //Return to the old coordinates system
        glPopMatrix();
    }

    //Drawing Rubik's Cube with offset
    void draw(double x, double y, double z) {
        glPushMatrix();
        glTranslated(x, y, z);
        draw();
        glPopMatrix();
    }
};


#endif //RUBIKCUBE_CUBEVISUAL_H
