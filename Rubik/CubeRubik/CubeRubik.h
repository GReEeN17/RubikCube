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
    void printRubikCube(ostream &outStream = cout) const ;

public:

    //Filling empty plane vectors
    void fillPlane(Plane &plane);

    void initPlanes();

    //Rotations of planes
    //Rotation of the up plane
    void rotateUpPlane(bool clockwise);

    //Rotation of the up plane clockwise
    void rotateUpPlaneClock(string& up00, string& up01, string& front00, string& front01, string& front02);

    //Rotation of the up plane not clockwise
    void rotateUpPlaneNotClock(string& up00, string& up01, string& front00, string& front01, string& front02);


    //Rotation of the down plane
    void rotateDownPlane(bool clockwise);

    //Rotation of the down plane clockwise
    void rotateDownPlaneClock(string& down00, string& down01, string& front20, string& front21, string& front22);

    //Rotation of the down plane not clockwise
    void rotateDownPlaneNotClock(string& down00, string& down01, string& front20, string& front21, string& front22);


    //Rotation of the left plane
    void rotateLeftPlane(bool clockwise);

    //Rotation of the left plane clockwise
    void rotateLeftPlaneClock(string& left00, string& left01, string& front00, string& front10, string& front20);

    //Rotation of the left plane not clockwise
    void rotateLeftPlaneNotClock(string& left00, string& left01, string& front00, string& front10, string& front20);


    //Rotation of the right plane
    void rotateRightPlane(bool clockwise);

    //Rotation of the right plane clockwise
    void rotateRightPlaneClock(string& right00, string& right01, string& front02, string& front12, string& front22);

    //Rotation of the right plane not clockwise
    void rotateRightPlaneNotClock(string& right00, string& right01, string& front02, string& front12, string& front22);


    //Rotation of the front plane
    void rotateFrontPlane(bool clockwise);

    //Rotation of the front plane clockwise
    void rotateFrontPlaneClock(string& front00, string& front01, string& up20, string& up21, string& up22);

    //Rotation of the front plane not clockwise
    void rotateFrontPlaneNotClock(string& front00, string& front01, string& up20, string& up21, string& up22);


    //Rotation of the back plane
    void rotateBackPlane(bool clockwise);

    //Rotation of the back plane clockwise
    void rotateBackPlaneClock(string& back00, string& back01, string& up00, string& up01, string& up02);

    //Rotation of the back plane not clockwise
    void rotateBackPlaneNotClock(string& back00, string& back01, string& up00, string& up01, string& up02);
};


#endif //RUBIKCUBE_CUBERUBIK_H
