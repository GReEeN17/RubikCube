#ifndef RUBIKCUBE_CUBERUBIK_H
#define RUBIKCUBE_CUBERUBIK_H

#include <iostream>
#include <vector>

#include "../CubePiece/CubePiece.h"
using std::vector, std::istream, std::cin, std::cout, std::ostream;

#define Plane vector<vector<CubePiece*>>
#define UpCenter UpPlane[1][1]->getUpColor();
#define DownCenter DownPlane[1][1]->getDownColor();
#define LeftCenter LeftPlane[1][1]->getLeftColor();
#define RightCenter RightPlane[1][1]->getRightColor();
#define FrontCenter FrontPlane[1][1]->getFrontColor();
#define BackCenter BackPlane[1][1]->getBackColor();

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
    Plane BackPlane;

    //Info of solving cube
    int rotatesCounter;

public:
    //Constructor

    explicit CubeRubik();

    //Getters of Info

    [[nodiscard]] int getRotatesCounter() const;

    //Implementation of the main function: generating, shuffling, solving etc.

    //Generating right(solved) RubikCube
    void generateRubikCube();

    //Reading RubikCube from console or file
    void readRubikCube(istream &inStream = cin);

    //Printing RubikCube in console or file
    void printRubikCube(ostream &outStream = cout) const;

private:

    //Filling empty plane vectors
    void fillPlane(Plane &plane);

    void initPlanes();

    //Rotations of planes
    void rotateUpPlane(bool clockwise);
};


#endif //RUBIKCUBE_CUBERUBIK_H
