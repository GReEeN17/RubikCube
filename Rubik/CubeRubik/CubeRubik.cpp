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
    string tempUp00 = UpPlane[0][0]->getUpColor();
    if (clockwise) {
        UpPlane[0][0]->setUpColor(UpPlane[2][0]->getUpColor());
        UpPlane[0][1]->setUpColor(UpPlane[1][0]->getUpColor());
    }
}
