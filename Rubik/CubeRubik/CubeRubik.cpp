#include "CubeRubik.h"

using std::istream, std::cin;

//Constructor

CubeRubik::CubeRubik() {
    array.resize(3, vector<vector<CubePiece>>(3, vector<CubePiece>(3)));
    initPlanes();
    generateRubikCube();
    rotatesCounter = 0;
}

//Getters of info

int CubeRubik::getRotatesCounter() const {
    return rotatesCounter;
}

//Implementation of the main function: generating, shuffling, solving etc.

//Generating right(solved) RubikCube
void CubeRubik::generateRubikCube() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            UpPlane[i][j]->setUpColor("Y");
            DownPlane[i][j]->setDownColor("W");
            LeftPlane[i][j]->setLeftColor("O");
            RightPlane[i][j]->setRightColor("R");
            FrontPlane[i][j]->setFrontColor("B");
            BackPlane[i][j]->setBackColor("G");
        }
    }
}

//Reading RubikCube from console or file
void CubeRubik::readRubikCube(istream &inStream) {
    string color;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            UpPlane[i][j]->setUpColor(color);
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            DownPlane[i][j]->setDownColor(color);
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            LeftPlane[i][j]->setLeftColor(color);
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            RightPlane[i][j]->setRightColor(color);
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            FrontPlane[i][j]->setFrontColor(color);
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            BackPlane[i][j]->setBackColor(color);
        }
    }
}

//Printing RubikCube in console or file
void CubeRubik::printRubikCube(std::ostream &outStream) const{
    outStream << "Развёртка Кубика Рубика:\n\n";
    for (int i = 0; i < 3; i++) {
        outStream << "\t\t| ";
        for (int j = 0; j < 3; j++) {
            outStream << LeftPlane[i][j]->getLeftColor() << " | ";
        }
        outStream << "\n";
    }
    for (int i = 0; i < 3; i++) {
        outStream << "| ";
        for (int j = 0; j < 3; j++) {
            outStream << BackPlane[i][j]->getBackColor() << " | ";
        }
        outStream << "* | ";
        for (int j = 0; j < 3; j++) {
            outStream << UpPlane[i][j]->getUpColor() << " | ";
        }
        outStream << "* | ";
        for (int j = 0; j < 3; j++) {
            outStream << FrontPlane[i][j]->getFrontColor() << " | ";
        }
        outStream << "* | ";
        for (int j = 0; j < 3; j++) {
            cout << DownPlane[i][j]->getDownColor() << " | ";
        }
        outStream << "\n";
    }
    for (int i = 0; i < 3; i++) {
        outStream << "\t\t| ";
        for (int j = 0; j < 3; j++) {
            outStream << RightPlane[i][j]->getRightColor() << " | ";
        }
        outStream << "\n";
    }
}

//Filling empty plane vectors
void CubeRubik::fillPlane(Plane &plane) {
    for (int i = 0; i < 3; i++) {
        vector<CubePiece*> tempArray(3);
        for (int j = 0; j < 3; j++) {
            tempArray[j] = &array[i][2][j];
        }
        plane.push_back(tempArray);
    }
}

void CubeRubik::initPlanes() {
    fillPlane(UpPlane);
    fillPlane(DownPlane);
    fillPlane(LeftPlane);
    fillPlane(RightPlane);
    fillPlane(FrontPlane);
    fillPlane(BackPlane);
}

//Rotation of planes
//Rotation of the up plane
void CubeRubik::rotateUpPlane(bool clockwise) {
    rotatesCounter++;
    //Temps for rotating up colors of up plane
    string tempUp00 = UpPlane[0][0]->getUpColor();
    string tempUp01 = UpPlane[0][1]->getUpColor();
    //Temps for rotating side colors of up plane
    string tempFront00 = FrontPlane[0][0]->getFrontColor();
    string tempFront01 = FrontPlane[0][1]->getFrontColor();
    string tempFront02 = FrontPlane[0][2]->getFrontColor();
    if (clockwise) {
        rotateUpPlaneClock(tempUp00, tempUp01, tempFront00, tempFront01, tempFront02);
    } else {
        rotateUpPlaneNotClock(tempUp00, tempUp01, tempFront00, tempFront01, tempFront02);
    }
}

//Rotation of the up plane clockwise
void CubeRubik::rotateUpPlaneClock(std::string &up00, std::string &up01, std::string &front00, std::string &front01,
                                       std::string &front02) {
    //Rotation colors of up plane clockwise
    UpPlane[0][0]->setUpColor(UpPlane[2][0]->getUpColor());
    UpPlane[0][1]->setUpColor(UpPlane[1][0]->getUpColor());
    UpPlane[2][0]->setUpColor(UpPlane[2][2]->getUpColor());
    UpPlane[2][1]->setUpColor(UpPlane[1][2]->getUpColor());
    UpPlane[2][2]->setUpColor(UpPlane[0][2]->getUpColor());
    UpPlane[1][2]->setUpColor(up01);
    UpPlane[0][2]->setUpColor(up00);
    //Rotation side colors of up plane clockwise
    //Front side
    FrontPlane[0][0]->setFrontColor(RightPlane[0][0]->getRightColor());
    FrontPlane[0][1]->setFrontColor(RightPlane[0][1]->getRightColor());
    FrontPlane[0][2]->setFrontColor(RightPlane[0][2]->getRightColor());
    //Right side
    RightPlane[0][0]->setRightColor(BackPlane[0][0]->getBackColor());
    RightPlane[0][1]->setRightColor(BackPlane[0][1]->getBackColor());
    RightPlane[0][2]->setRightColor(BackPlane[0][2]->getBackColor());
    //Back side
    BackPlane[0][0]->setBackColor(LeftPlane[0][0]->getLeftColor());
    BackPlane[0][1]->setBackColor(LeftPlane[0][1]->getLeftColor());
    BackPlane[0][2]->setBackColor(LeftPlane[0][2]->getLeftColor());
    //Left side
    LeftPlane[0][0]->setLeftColor(front00);
    LeftPlane[0][1]->setLeftColor(front01);
    LeftPlane[0][2]->setLeftColor(front02);
}

//Rotation of the up plane not clockwise
void CubeRubik::rotateUpPlaneNotClock(std::string &up00, std::string &up01, std::string &front00,
                                          std::string &front01, std::string &front02) {
    //Rotation colors of up plane not clockwise
    UpPlane[0][0]->setUpColor(UpPlane[0][2]->getUpColor());
    UpPlane[0][1]->setUpColor(UpPlane[1][2]->getUpColor());
    UpPlane[0][2]->setUpColor(UpPlane[2][2]->getUpColor());
    UpPlane[1][2]->setUpColor(UpPlane[2][1]->getUpColor());
    UpPlane[2][2]->setUpColor(UpPlane[2][0]->getUpColor());
    UpPlane[2][1]->setUpColor(up01);
    UpPlane[2][0]->setUpColor(up00);
    //Rotation side colors of up plane clockwise
    //Front side
    FrontPlane[0][0]->setFrontColor(LeftPlane[0][0]->getLeftColor());
    FrontPlane[0][1]->setFrontColor(LeftPlane[0][1]->getLeftColor());
    FrontPlane[0][2]->setFrontColor(LeftPlane[0][2]->getLeftColor());
    //Left side
    LeftPlane[0][0]->setLeftColor(BackPlane[0][0]->getBackColor());
    LeftPlane[0][1]->setLeftColor(BackPlane[0][1]->getBackColor());
    LeftPlane[0][2]->setLeftColor(BackPlane[0][2]->getBackColor());
    //Back side
    BackPlane[0][0]->setBackColor(RightPlane[0][0]->getRightColor());
    BackPlane[0][1]->setBackColor(RightPlane[0][1]->getRightColor());
    BackPlane[0][2]->setBackColor(RightPlane[0][2]->getRightColor());
    //Right side
    RightPlane[0][0]->setRightColor(front00);
    RightPlane[0][1]->setRightColor(front01);
    RightPlane[0][2]->setRightColor(front02);
}
