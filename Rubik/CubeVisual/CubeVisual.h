#ifndef RUBIKCUBE_CUBEVISUAL_H
#define RUBIKCUBE_CUBEVISUAL_H

#include "../RubikConfig.h"


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
    void rotateBackFront();

    void rotateDownUp();

    void rotateLeftRight();

    //Setter of colors
    void setColor(int i, int color);

    //Setter of sizeEdge
    void setEdge(GLfloat size);

    //Getter of RGB representation of color (0xFFFFFF -> [FF, FF, FF])
    unsigned char* getRGB(int i);

    //Drawing Rubik's Cube, or rather setting colors and normals for each plane
    void draw();

    //Drawing Rubik's Cube with offset
    void draw(double x, double y, double z);
};


#endif //RUBIKCUBE_CUBEVISUAL_H
