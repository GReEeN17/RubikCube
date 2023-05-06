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
void CubeRubik::printRubikCube(std::ostream &outStream) const {
    outStream << "\nРазвёртка Кубика Рубика:\n\n";
    for (int i = 0; i < 3; i++) {
        outStream << "\t\t| ";
        for (int j = 0; j < 3; j++) {
            outStream << UpPlane[i][j]->getUpColor() << " | ";
        }
        outStream << "\n";
    }
    for (int i = 0; i < 3; i++) {
        outStream << "| ";
        for (int j = 0; j < 3; j++) {
            outStream << LeftPlane[i][j]->getLeftColor() << " | ";
        }
        outStream << "* | ";
        for (int j = 0; j < 3; j++) {
            outStream << FrontPlane[i][j]->getFrontColor() << " | ";
        }
        outStream << "* | ";
        for (int j = 0; j < 3; j++) {
            outStream << RightPlane[i][j]->getRightColor() << " | ";
        }
        outStream << "* | ";
        for (int j = 0; j < 3; j++) {
            cout << BackPlane[i][j]->getBackColor() << " | ";
        }
        outStream << "\n";
    }
    for (int i = 0; i < 3; i++) {
        outStream << "\t\t| ";
        for (int j = 0; j < 3; j++) {
            outStream << DownPlane[i][j]->getDownColor() << " | ";
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
    //Checking how to rotate up plane and calling the corresponding function
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
    UpPlane[1][0]->setUpColor(UpPlane[2][1]->getUpColor());
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
    UpPlane[2][1]->setUpColor(UpPlane[1][0]->getUpColor());
    UpPlane[2][0]->setUpColor(up00);
    UpPlane[1][0]->setUpColor(up01);
    //Rotation side colors of up plane not clockwise
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

//Rotation of the down plane
void CubeRubik::rotateDownPlane(bool clockwise) {
    //Temps for rotating down colors of down plane
    string tempDown00 = DownPlane[0][0]->getDownColor();
    string tempDown01 = DownPlane[0][1]->getDownColor();
    //Temps for rotating side colors of down plane
    string tempFront20 = FrontPlane[2][0]->getFrontColor();
    string tempFront21 = FrontPlane[2][1]->getFrontColor();
    string tempFront22 = FrontPlane[2][2]->getFrontColor();
    //Checking how to rotate down plane and calling the corresponding function
    if (clockwise) {
        rotateDownPlaneClock(tempDown00, tempDown01, tempFront20, tempFront21, tempFront22);
    } else {
        rotateDownPlaneNotClock(tempDown00, tempDown01, tempFront20, tempFront21, tempFront22);
    }
}

//Rotation of the down plane clockwise
void CubeRubik::rotateDownPlaneClock(string& down00, string& down01, string& front20, string& front21, string& front22) {
    //Rotating down colors of down plane
    DownPlane[0][0]->setDownColor(DownPlane[2][0]->getDownColor());
    DownPlane[0][1]->setDownColor(DownPlane[1][0]->getDownColor());
    DownPlane[2][0]->setDownColor(DownPlane[2][2]->getDownColor());
    DownPlane[1][0]->setDownColor(DownPlane[2][1]->getDownColor());
    DownPlane[2][2]->setDownColor(DownPlane[0][2]->getDownColor());
    DownPlane[2][1]->setDownColor(DownPlane[1][2]->getDownColor());
    DownPlane[0][2]->setDownColor(down00);
    DownPlane[1][2]->setDownColor(down01);
    //Rotating side colors of down plane
    //Front plane
    FrontPlane[2][0]->setFrontColor(LeftPlane[2][0]->getLeftColor());
    FrontPlane[2][1]->setFrontColor(LeftPlane[2][1]->getLeftColor());
    FrontPlane[2][2]->setFrontColor(LeftPlane[2][2]->getLeftColor());
    //Left plane
    LeftPlane[2][0]->setLeftColor(BackPlane[2][0]->getBackColor());
    LeftPlane[2][1]->setLeftColor(BackPlane[2][1]->getBackColor());
    LeftPlane[2][2]->setLeftColor(BackPlane[2][2]->getBackColor());
    //Back plane
    BackPlane[2][0]->setBackColor(RightPlane[2][0]->getRightColor());
    BackPlane[2][1]->setBackColor(RightPlane[2][1]->getRightColor());
    BackPlane[2][2]->setBackColor(RightPlane[2][2]->getRightColor());
    //Right plane
    RightPlane[2][0]->setRightColor(front20);
    RightPlane[2][1]->setRightColor(front21);
    RightPlane[2][2]->setRightColor(front22);
}

//Rotation of the down plane not clockwise
void CubeRubik::rotateDownPlaneNotClock(string& down00, string& down01, string& front20, string& front21, string& front22) {
    //Rotating down colors of down plane
    DownPlane[0][0]->setDownColor(DownPlane[0][2]->getDownColor());
    DownPlane[0][1]->setDownColor(DownPlane[1][2]->getDownColor());
    DownPlane[0][2]->setDownColor(DownPlane[2][2]->getDownColor());
    DownPlane[1][2]->setDownColor(DownPlane[2][1]->getDownColor());
    DownPlane[2][2]->setDownColor(DownPlane[2][0]->getDownColor());
    DownPlane[2][1]->setDownColor(DownPlane[1][0]->getDownColor());
    DownPlane[2][0]->setDownColor(down00);
    DownPlane[1][0]->setDownColor(down01);
    //Rotating side colors of down plane
    //Front plane
    FrontPlane[2][0]->setFrontColor(RightPlane[2][0]->getRightColor());
    FrontPlane[2][1]->setFrontColor(RightPlane[2][1]->getRightColor());
    FrontPlane[2][2]->setFrontColor(RightPlane[2][2]->getRightColor());
    //Right plane
    RightPlane[2][0]->setRightColor(BackPlane[2][0]->getBackColor());
    RightPlane[2][1]->setRightColor(BackPlane[2][1]->getBackColor());
    RightPlane[2][2]->setRightColor(BackPlane[2][2]->getBackColor());
    //Back plane
    BackPlane[2][0]->setBackColor(LeftPlane[2][0]->getLeftColor());
    BackPlane[2][1]->setBackColor(LeftPlane[2][1]->getLeftColor());
    BackPlane[2][2]->setBackColor(LeftPlane[2][2]->getLeftColor());
    //Left plane
    LeftPlane[2][0]->setLeftColor(front20);
    LeftPlane[2][1]->setLeftColor(front21);
    LeftPlane[2][2]->setLeftColor(front22);
}


//Rotation of the left plane
void CubeRubik::rotateLeftPlane(bool clockwise) {
    //Temps for rotating left colors of left plane
    string tempLeft00 = LeftPlane[0][0]->getLeftColor();
    string tempLeft01 = LeftPlane[0][1]->getLeftColor();
    //Temps for rotating side colors of left plane
    string tempFront00 = FrontPlane[0][0]->getFrontColor();
    string tempFront10 = FrontPlane[1][0]->getFrontColor();
    string tempFront20 = FrontPlane[2][0]->getFrontColor();
    //Checking how to rotate left plane and calling the corresponding function
    if (clockwise) {
        rotateLeftPlaneClock(tempLeft00, tempLeft01, tempFront00, tempFront10, tempFront20);
    } else {
        rotateLeftPlaneNotClock(tempLeft00, tempLeft01, tempFront00, tempFront10, tempFront20);
    }
}

//Rotation of the left plane clockwise
void CubeRubik::rotateLeftPlaneClock(string& left00, string& left01, string& front00, string& front10, string& front20) {
    //Rotating left colors of left plane
    LeftPlane[0][0]->setLeftColor(LeftPlane[2][0]->getLeftColor());
    LeftPlane[0][1]->setLeftColor(LeftPlane[1][0]->getLeftColor());
    LeftPlane[2][0]->setLeftColor(LeftPlane[2][2]->getLeftColor());
    LeftPlane[1][0]->setLeftColor(LeftPlane[2][1]->getLeftColor());
    LeftPlane[2][2]->setLeftColor(LeftPlane[0][2]->getLeftColor());
    LeftPlane[2][1]->setLeftColor(LeftPlane[1][2]->getLeftColor());
    LeftPlane[0][2]->setLeftColor(left00);
    LeftPlane[1][2]->setLeftColor(left01);
    //Rotating side color sof left plane
    //Front plane
    FrontPlane[0][0]->setFrontColor(UpPlane[0][0]->getUpColor());
    FrontPlane[1][0]->setFrontColor(UpPlane[1][0]->getUpColor());
    FrontPlane[2][0]->setFrontColor(UpPlane[2][0]->getUpColor());
    //Up plane
    UpPlane[0][0]->setUpColor(BackPlane[2][2]->getBackColor());
    UpPlane[1][0]->setUpColor(BackPlane[1][2]->getBackColor());
    UpPlane[2][0]->setUpColor(BackPlane[0][2]->getBackColor());
    //Back plane
    BackPlane[0][2]->setBackColor(DownPlane[2][0]->getDownColor());
    BackPlane[1][2]->setBackColor(DownPlane[1][0]->getDownColor());
    BackPlane[2][2]->setBackColor(DownPlane[0][0]->getDownColor());
    //Down plane
    DownPlane[0][0]->setDownColor(front00);
    DownPlane[1][0]->setDownColor(front10);
    DownPlane[2][0]->setDownColor(front20);
}

//Rotation of the left plane not clockwise
void CubeRubik::rotateLeftPlaneNotClock(string& left00, string& left01, string& front00, string& front10, string& front20) {
    //Rotating left colors of left plane
    LeftPlane[0][0]->setLeftColor(LeftPlane[0][2]->getLeftColor());
    LeftPlane[0][1]->setLeftColor(LeftPlane[1][2]->getLeftColor());
    LeftPlane[0][2]->setLeftColor(LeftPlane[2][2]->getLeftColor());
    LeftPlane[1][2]->setLeftColor(LeftPlane[2][1]->getLeftColor());
    LeftPlane[2][2]->setLeftColor(LeftPlane[2][0]->getLeftColor());
    LeftPlane[2][1]->setLeftColor(LeftPlane[1][0]->getLeftColor());
    LeftPlane[2][0]->setLeftColor(left00);
    LeftPlane[1][0]->setLeftColor(left01);
    //Rotating side colors of left plane
    //Front side
    FrontPlane[0][0]->setFrontColor(DownPlane[0][0]->getDownColor());
    FrontPlane[1][0]->setFrontColor(DownPlane[1][0]->getDownColor());
    FrontPlane[2][0]->setFrontColor(DownPlane[2][0]->getDownColor());
    //Down plane
    DownPlane[0][0]->setDownColor(BackPlane[2][2]->getBackColor());
    DownPlane[1][0]->setDownColor(BackPlane[1][2]->getBackColor());
    DownPlane[2][0]->setDownColor(BackPlane[0][2]->getBackColor());
    //Back plane
    BackPlane[0][2]->setBackColor(UpPlane[2][0]->getUpColor());
    BackPlane[1][2]->setBackColor(UpPlane[1][0]->getUpColor());
    BackPlane[2][2]->setBackColor(UpPlane[0][0]->getUpColor());
    //Up plane
    UpPlane[0][0]->setUpColor(front00);
    UpPlane[1][0]->setUpColor(front10);
    UpPlane[2][0]->setUpColor(front20);
}


//Rotation of the right plane
void CubeRubik::rotateRightPlane(bool clockwise) {
    //Temps for rotating right colors of right plane
    string tempRight00 = RightPlane[0][0]->getRightColor();
    string tempRight01 = RightPlane[0][1]->getRightColor();
    //Temps for rotating side colors of right plane
    string tempFront02 = FrontPlane[0][2]->getFrontColor();
    string tempFront12 = FrontPlane[1][2]->getFrontColor();
    string tempFront22 = FrontPlane[2][2]->getFrontColor();
    //Checking how to rotate right plane and calling the corresponding function
    if (clockwise) {
        rotateRightPlaneClock(tempRight00, tempRight01, tempFront02, tempFront12, tempFront22);
    } else {
        rotateRightPlaneNotClock(tempRight00, tempRight01, tempFront02, tempFront12, tempFront22);
    }
}

//Rotation of the right plane clockwise
void CubeRubik::rotateRightPlaneClock(string& right00, string& right01, string& front02, string& front12, string& front22) {
    //Rotating right colors of right plane
    RightPlane[0][0]->setRightColor(RightPlane[2][0]->getRightColor());
    RightPlane[0][1]->setRightColor(RightPlane[1][0]->getRightColor());
    RightPlane[2][0]->setRightColor(RightPlane[2][2]->getRightColor());
    RightPlane[1][0]->setRightColor(RightPlane[2][1]->getRightColor());
    RightPlane[2][2]->setRightColor(RightPlane[0][2]->getRightColor());
    RightPlane[2][1]->setRightColor(RightPlane[1][2]->getRightColor());
    RightPlane[0][2]->setRightColor(right00);
    RightPlane[1][2]->setRightColor(right01);
    //Rotating side colors of right plane
    //Front plane
    FrontPlane[0][2]->setFrontColor(DownPlane[0][2]->getDownColor());
    FrontPlane[1][2]->setFrontColor(DownPlane[1][2]->getDownColor());
    FrontPlane[2][2]->setFrontColor(DownPlane[2][2]->getDownColor());
    //Down plane
    DownPlane[0][2]->setDownColor(BackPlane[2][0]->getBackColor());
    DownPlane[1][2]->setDownColor(BackPlane[1][0]->getBackColor());
    DownPlane[2][2]->setDownColor(BackPlane[0][0]->getBackColor());
    //Back plane
    BackPlane[0][0]->setBackColor(UpPlane[2][2]->getUpColor());
    BackPlane[1][0]->setBackColor(UpPlane[1][2]->getUpColor());
    BackPlane[2][0]->setBackColor(UpPlane[0][2]->getUpColor());
    //Up plane
    UpPlane[0][2]->setUpColor(front02);
    UpPlane[1][2]->setUpColor(front12);
    UpPlane[2][2]->setUpColor(front22);
}

//Rotation of the right plane not clockwise
void CubeRubik::rotateRightPlaneNotClock(string& right00, string& right01, string& front02, string& front12, string& front22) {
    //Rotating right colors of right plane
    RightPlane[0][0]->setRightColor(RightPlane[0][2]->getRightColor());
    RightPlane[0][1]->setRightColor(RightPlane[1][2]->getRightColor());
    RightPlane[0][2]->setRightColor(RightPlane[2][2]->getRightColor());
    RightPlane[1][2]->setRightColor(RightPlane[2][1]->getRightColor());
    RightPlane[2][2]->setRightColor(RightPlane[2][0]->getRightColor());
    RightPlane[2][1]->setRightColor(RightPlane[1][0]->getRightColor());
    RightPlane[2][0]->setRightColor(right00);
    RightPlane[1][0]->setRightColor(right01);
    //Rotating side colors of right plane
    //Front plane
    FrontPlane[0][2]->setFrontColor(UpPlane[0][2]->getUpColor());
    FrontPlane[1][2]->setFrontColor(UpPlane[1][2]->getUpColor());
    FrontPlane[2][2]->setFrontColor(UpPlane[2][2]->getUpColor());
    //Up plane
    UpPlane[0][2]->setUpColor(BackPlane[2][0]->getBackColor());
    UpPlane[1][2]->setUpColor(BackPlane[1][0]->getBackColor());
    UpPlane[2][2]->setUpColor(BackPlane[0][0]->getBackColor());
    //Back plane
    BackPlane[2][0]->setBackColor(DownPlane[0][2]->getDownColor());
    BackPlane[1][0]->setBackColor(DownPlane[1][2]->getDownColor());
    BackPlane[0][0]->setBackColor(DownPlane[2][2]->getDownColor());
    //Down plane
    DownPlane[0][2]->setDownColor(front02);
    DownPlane[1][2]->setDownColor(front12);
    DownPlane[2][2]->setDownColor(front22);
}


//Rotation of the front plane
void CubeRubik::rotateFrontPlane(bool clockwise) {
    //Temps for rotating front colors of front plane
    string tempFront00 = FrontPlane[0][0]->getFrontColor();
    string tempFront01 = FrontPlane[0][1]->getFrontColor();
    //Temps for rotating side colors of front plane
    string tempUp20 = UpPlane[2][0]->getUpColor();
    string tempUp21 = UpPlane[2][1]->getUpColor();
    string tempUp22 = UpPlane[2][2]->getUpColor();
    //Checking how to rotate front plane and calling the corresponding function
    if (clockwise) {
        rotateFrontPlaneClock(tempFront00, tempFront01, tempUp20, tempUp21, tempUp22);
    } else {
        rotateFrontPlaneNotClock(tempFront00, tempFront01, tempUp20, tempUp21, tempUp22);
    }
}

//Rotation of the front plane clockwise
void CubeRubik::rotateFrontPlaneClock(string& front00, string& front01, string& up20, string& up21, string& up22) {
    //Rotating front colors of front plane
    FrontPlane[0][0]->setFrontColor(FrontPlane[2][0]->getFrontColor());
    FrontPlane[0][1]->setFrontColor(FrontPlane[1][0]->getFrontColor());
    FrontPlane[2][0]->setFrontColor(FrontPlane[2][2]->getFrontColor());
    FrontPlane[1][0]->setFrontColor(FrontPlane[2][1]->getFrontColor());
    FrontPlane[2][2]->setFrontColor(FrontPlane[0][2]->getFrontColor());
    FrontPlane[2][1]->setFrontColor(FrontPlane[1][2]->getFrontColor());
    FrontPlane[0][2]->setFrontColor(front00);
    FrontPlane[1][2]->setFrontColor(front01);
    //Rotating side colors of front plane
    //Up plane
    UpPlane[2][0]->setUpColor(LeftPlane[2][2]->getLeftColor());
    UpPlane[2][1]->setUpColor(LeftPlane[1][2]->getLeftColor());
    UpPlane[2][2]->setUpColor(LeftPlane[0][2]->getLeftColor());
    //Left plane
    LeftPlane[0][2]->setLeftColor(DownPlane[0][0]->getDownColor());
    LeftPlane[1][2]->setLeftColor(DownPlane[0][1]->getDownColor());
    LeftPlane[2][2]->setLeftColor(DownPlane[0][2]->getDownColor());
    //Down plane
    DownPlane[0][0]->setDownColor(RightPlane[2][0]->getRightColor());
    DownPlane[0][1]->setDownColor(RightPlane[1][0]->getRightColor());
    DownPlane[0][2]->setDownColor(RightPlane[0][0]->getRightColor());
    //Right plane
    RightPlane[0][0]->setRightColor(up20);
    RightPlane[1][0]->setRightColor(up21);
    RightPlane[2][0]->setRightColor(up22);
}

//Rotation of the front plane not clockwise
void CubeRubik::rotateFrontPlaneNotClock(string& front00, string& front01, string& up20, string& up21, string& up22) {
    //Rotating front colors of front plane
    FrontPlane[0][0]->setFrontColor(FrontPlane[0][2]->getFrontColor());
    FrontPlane[0][1]->setFrontColor(FrontPlane[1][2]->getFrontColor());
    FrontPlane[0][2]->setFrontColor(FrontPlane[2][2]->getFrontColor());
    FrontPlane[1][2]->setFrontColor(FrontPlane[2][1]->getFrontColor());
    FrontPlane[2][2]->setFrontColor(FrontPlane[2][0]->getFrontColor());
    FrontPlane[2][1]->setFrontColor(FrontPlane[1][0]->getFrontColor());
    FrontPlane[2][0]->setFrontColor(front00);
    FrontPlane[1][0]->setFrontColor(front01);
    //Rotating side colors of front plane
    //Up plane
    UpPlane[2][0]->setUpColor(RightPlane[0][0]->getRightColor());
    UpPlane[2][1]->setUpColor(RightPlane[1][0]->getRightColor());
    UpPlane[2][2]->setUpColor(RightPlane[2][0]->getRightColor());
    //Right plane
    RightPlane[0][0]->setRightColor(DownPlane[0][2]->getDownColor());
    RightPlane[1][0]->setRightColor(DownPlane[0][1]->getDownColor());
    RightPlane[2][0]->setRightColor(DownPlane[0][0]->getDownColor());
    //Down plane
    DownPlane[0][0]->setDownColor(LeftPlane[0][2]->getLeftColor());
    DownPlane[0][1]->setDownColor(LeftPlane[1][2]->getLeftColor());
    DownPlane[0][2]->setDownColor(LeftPlane[2][2]->getLeftColor());
    //Left plane
    LeftPlane[0][2]->setLeftColor(up22);
    LeftPlane[1][2]->setLeftColor(up21);
    LeftPlane[2][2]->setLeftColor(up20);
}


//Rotation of the back plane
void CubeRubik::rotateBackPlane(bool clockwise) {
    //Temps for rotating back colors of back plane
    string tempBack00 = BackPlane[0][0]->getBackColor();
    string tempBack01 = BackPlane[0][1]->getBackColor();
    //Temps for rotating side colors of back plane
    string tempUp00 = UpPlane[0][0]->getUpColor();
    string tempUp01 = UpPlane[0][1]->getUpColor();
    string tempUp02 = UpPlane[0][2]->getUpColor();
    //Checking how to rotate back plane and calling the corresponding function
    if (clockwise) {
        rotateBackPlaneClock(tempBack00, tempBack01, tempUp00, tempUp01, tempUp02);
    } else {
        rotateBackPlaneNotClock(tempBack00, tempBack01, tempUp00, tempUp01, tempUp02);
    }
}

//Rotation of the back plane clockwise
void CubeRubik::rotateBackPlaneClock(string& back00, string& back01, string& up00, string& up01, string& up02) {
    //Rotating back colors of back plane
    BackPlane[0][0]->setBackColor(BackPlane[2][0]->getBackColor());
    BackPlane[0][1]->setBackColor(BackPlane[1][0]->getBackColor());
    BackPlane[2][0]->setBackColor(BackPlane[2][2]->getBackColor());
    BackPlane[1][0]->setBackColor(BackPlane[2][1]->getBackColor());
    BackPlane[2][2]->setBackColor(BackPlane[0][2]->getBackColor());
    BackPlane[2][1]->setBackColor(BackPlane[1][2]->getBackColor());
    BackPlane[0][2]->setBackColor(back00);
    BackPlane[1][2]->setBackColor(back01);
    //Rotating side colors of back plane
    //Up plane
    UpPlane[0][0]->setUpColor(RightPlane[0][2]->getRightColor());
    UpPlane[0][1]->setUpColor(RightPlane[1][2]->getRightColor());
    UpPlane[0][2]->setUpColor(RightPlane[2][2]->getRightColor());
    //Right plane
    RightPlane[0][2]->setRightColor(DownPlane[2][2]->getDownColor());
    RightPlane[1][2]->setRightColor(DownPlane[2][1]->getDownColor());
    RightPlane[2][2]->setRightColor(DownPlane[2][0]->getDownColor());
    //Down plane
    DownPlane[2][0]->setDownColor(LeftPlane[0][0]->getLeftColor());
    DownPlane[2][1]->setDownColor(LeftPlane[1][0]->getLeftColor());
    DownPlane[2][2]->setDownColor(LeftPlane[2][0]->getLeftColor());
    //Left plane
    LeftPlane[0][0]->setLeftColor(up02);
    LeftPlane[1][0]->setLeftColor(up01);
    LeftPlane[2][0]->setLeftColor(up00);

}

//Rotation of the back plane not clockwise
void CubeRubik::rotateBackPlaneNotClock(string& back00, string& back01, string& up00, string& up01, string& up02) {
    //Rotating back colors of back plane
    BackPlane[0][0]->setBackColor(BackPlane[0][2]->getBackColor());
    BackPlane[0][1]->setBackColor(BackPlane[1][2]->getBackColor());
    BackPlane[0][2]->setBackColor(BackPlane[2][2]->getBackColor());
    BackPlane[1][2]->setBackColor(BackPlane[2][1]->getBackColor());
    BackPlane[2][2]->setBackColor(BackPlane[2][0]->getBackColor());
    BackPlane[2][1]->setBackColor(BackPlane[1][0]->getBackColor());
    BackPlane[2][0]->setBackColor(back00);
    BackPlane[1][0]->setBackColor(back01);
    //Rotating side colors of back plane
    //Up plane
    UpPlane[0][0]->setUpColor(LeftPlane[2][0]->getLeftColor());
    UpPlane[0][1]->setUpColor(LeftPlane[1][0]->getLeftColor());
    UpPlane[0][2]->setUpColor(LeftPlane[0][0]->getLeftColor());
    //Left plane
    LeftPlane[0][0]->setLeftColor(DownPlane[2][0]->getDownColor());
    LeftPlane[1][0]->setLeftColor(DownPlane[2][1]->getDownColor());
    LeftPlane[2][0]->setLeftColor(DownPlane[2][2]->getDownColor());
    //Down plane
    DownPlane[2][0]->setDownColor(RightPlane[2][2]->getRightColor());
    DownPlane[2][1]->setDownColor(RightPlane[1][2]->getRightColor());
    DownPlane[2][2]->setDownColor(RightPlane[0][2]->getRightColor());
    //Right plane
    RightPlane[0][2]->setRightColor(up00);
    RightPlane[1][2]->setRightColor(up01);
    RightPlane[2][2]->setRightColor(up02);
}
