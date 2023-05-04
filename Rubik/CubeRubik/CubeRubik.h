#ifndef RUBIKCUBE_CUBERUBIK_H
#define RUBIKCUBE_CUBERUBIK_H

#include <iostream>
#include <vector>

#include "../CubePiece/CubePiece.h"
using std::vector, std::istream;

#define Plane vector<vector<CubePiece*>>
#define UpCenter UpPlane[1][1]->getUpColor();
#define DownCenter DownPlane[1][1]->getDownColor();
#define LeftCenter LeftPlane[1][1]->getLeftColor();
#define RightCenter RightPlane[1][1]->getRightColor();
#define FrontCenter FrontPlane[1][1]->getFrontColor();
#define RearCenter RearPlane[1][1]->getRearColor();

class CubeRubik {
private:
    //Array for storage all cube pieces
    vector<vector<vector<CubePiece>>> array;

    //Planes for all of six sides
    Plane UpPlane;
    Plane DownPlane;
    Plane LeftPlane;
    Plane RightPlane;
    Plane FrontPlane;
    Plane RearPlane;

public:
    //Constructor

    explicit CubeRubik();

    //Implementation of the main function: generating, shuffling, solving etc.

    void generateRubikCube();

    void readRubikCube(istream &inStream);
};


#endif //RUBIKCUBE_CUBERUBIK_H
