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
    cout << "Развёртка Кубика Рубика:\n\n";
    for (int i = 0; i < 3; i++) {
        cout << "\t\t| ";
        for (int j = 0; j < 3; j++) {
            cout << LeftPlane[i][j]->getLeftColor() << " | ";
        }
        cout << "\n";
    }
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << BackPlane[i][j]->getBackColor() << " | ";
        }
        cout << "* | ";
        for (int j = 0; j < 3; j++) {
            cout << UpPlane[i][j]->getUpColor() << " | ";
        }
        cout << "* | ";
        for (int j = 0; j < 3; j++) {
            cout << FrontPlane[i][j]->getFrontColor() << " | ";
        }
        cout << "* | ";
        for (int j = 0; j < 3; j++) {
            cout << DownPlane[i][j]->getDownColor() << " | ";
        }
        cout << "\n";
    }
    for (int i = 0; i < 3; i++) {
        cout << "\t\t| ";
        for (int j = 0; j < 3; j++) {
            cout << RightPlane[i][j]->getRightColor() << " | ";
        }
        cout << "\n";
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
        //Rotation colors of up plane clockwise
        UpPlane[0][0]->setUpColor(UpPlane[2][0]->getUpColor());
        UpPlane[0][1]->setUpColor(UpPlane[1][0]->getUpColor());
        UpPlane[2][0]->setUpColor(UpPlane[2][2]->getUpColor());
        UpPlane[2][1]->setUpColor(UpPlane[1][2]->getUpColor());
        UpPlane[2][2]->setUpColor(UpPlane[0][2]->getUpColor());
        UpPlane[1][2]->setUpColor(tempUp01);
        UpPlane[0][2]->setUpColor(tempUp00);
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
        LeftPlane[0][0]->setLeftColor(tempFront00);
        LeftPlane[0][1]->setLeftColor(tempFront01);
        LeftPlane[0][2]->setLeftColor(tempFront02);
    } else {
        //Rotation colors of up plane not clockwise
        UpPlane[0][0]->setUpColor(UpPlane[0][2]->getUpColor());
        UpPlane[0][1]->setUpColor(UpPlane[1][2]->getUpColor());
        UpPlane[0][2]->setUpColor(UpPlane[2][2]->getUpColor());
        UpPlane[1][2]->setUpColor(UpPlane[2][1]->getUpColor());
        UpPlane[2][2]->setUpColor(UpPlane[2][0]->getUpColor());
        UpPlane[2][1]->setUpColor(tempUp01);
        UpPlane[2][0]->setUpColor(tempUp00);
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
        RightPlane[0][0]->setRightColor(tempFront00);
        RightPlane[0][1]->setRightColor(tempFront01);
        RightPlane[0][2]->setRightColor(tempFront02);
    }
}
