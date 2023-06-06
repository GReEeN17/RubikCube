#ifndef RUBIKCUBE_CUBERUBIK_CPP
#define RUBIKCUBE_CUBERUBIK_CPP
#include "CubeRubik.h"
#include <iostream>
#include <random>

using std::istream, std::cin, std::ostream, std::string, std::random_device, std::mt19937, std::uniform_int_distribution;
using std::logic_error, std::exception;

//Constructor

CubeRubik::CubeRubik() {
    array.resize(3, vector<vector<CubePiece>>(3, vector<CubePiece>(3)));
    initPlanes();
    generateRubikCube();
    rotatesCounter = 0;
}

//Getters of info

void CubeRubik::getInfoOfSolvation() const {
    cout << "Information about latest solvation: \n";
    cout << "Rotations made in first step: " << firstStepCounter << "\n";
    cout << "Rotations made in second step: " << secondStepCounter << "\n";
    cout << "Rotations made in third step: " << thirdStepCounter << "\n";
    cout << "Rotations made in fourth step: " << fourthStepCounter << "\n";
    cout << "Rotations made in fifth step: " << fifthStepCounter << "\n";
    cout << "Rotations made in sixth step: " << sixthStepCounter << "\n";
    cout << "Rotations made in seventh step: " << seventhStepCounter << "\n";
    cout << "Rotations made while solving Rubik's Cube: " << rotatesCounter << "\n";
}

int CubeRubik::getCurrentPlane() {
    return currentPlane;
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
            visualColors[j][2][i].setColor(3, getRGBRubik(color));
        }
    }
    for (int i = 0, downColor = 2; i < 3; i++, downColor--) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            DownPlane[i][j]->setDownColor(color);
            visualColors[j][0][downColor].setColor(2, getRGBRubik(color));
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            FrontPlane[i][j]->setFrontColor(color);
            visualColors[j][2 - i][2].setColor(0, getRGBRubik(color));
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            BackPlane[i][j]->setBackColor(color);
            visualColors[2 - j][2 - i][0].setColor(1, getRGBRubik(color));
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            LeftPlane[i][j]->setLeftColor(color);
            visualColors[0][2 - i][j].setColor(4, getRGBRubik(color));
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inStream >> color;
            RightPlane[i][j]->setRightColor(color);
            visualColors[2][2 - i][2 - j].setColor(5, getRGBRubik(color));
        }
    }
}

//Printing RubikCube in console or file
void CubeRubik::printRubikCube(ostream &outStream) const {
    outStream << "\n\nРазвёртка Кубика Рубика:\n\n";
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

//Shuffling Rubik's Cube
void CubeRubik::shuffle(int rotations) {
    cout << "\n\nShuffling Rubik's Cube, rotations:\n\n";
    for (int i = 0;  i < rotations; i++) {
        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> randInt(0, 6);
        //Choosing plane
        int randPlane = randInt(mt);
        //Choosing how to rotate
        bool randClock = randInt(mt) % 2 == 0;
        switch (randPlane) {
            case(0):
                rotateUpPlane(randClock);
                break;
            case(1):
                rotateDownPlane(randClock);
                break;
            case(2):
                rotateLeftPlane(randClock);
                break;
            case(3):
                rotateRightPlane(randClock);
                break;
            case (4):
                rotateFrontPlane(randClock);
                break;
            case(5):
                rotateBackPlane(randClock);
                break;
            default:
                break;
        }
    }
    cout << "\n\n";
}

bool CubeRubik::isSolved() {
    return isSeventhStepCompleted();
}

void CubeRubik::solveCubeRubik() {
    if (!checkCubeIsCorrect()) {
        throw logic_error("\n\nCube is not correct, it can not be solved\n\n");
    }
    if (isSolved()) {
        throw logic_error("Cube is already solved!!!\n\n");
    }
    try {
        cout << "\n\nSolving Rubik's Cube\n\n";
        firstStepCounter = 0;
        secondStepCounter = 0;
        thirdStepCounter = 0;
        fourthStepCounter = 0;
        fifthStepCounter = 0;
        sixthStepCounter = 0;
        seventhStepCounter = 0;
        rotatesCounter = 0;
        firstStep();
        secondStep();
        thirdStep();
        fourthStep();
        fifthStep();
        sixthStep();
        seventhStep();
    } catch (exception e) {
        cout << e.what();
    }
}

void CubeRubik::rightSolver() {
    if (!isSolved()) {
        throw logic_error("\n\nRubik's Cube is not solver, you can not use this algorithm\n\n");
    }
    do {
        rotatePlanes("R U R'U'");
    } while (!isSolved());
    cout << "\nCube is solved one more time!!!\n";
}

void CubeRubik::leftSolver() {
    if (!isSolved()) {
        throw logic_error("\n\nRubik's Cube is not solver, you can not use this algorithm\n\n");
    }
    do {
        rotatePlanes("L'U'L U ");
    } while (!isSolved());
    cout << "\nCube is solved one more time!!!\n";
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

//Checking if cube is correct
bool CubeRubik::checkCubeIsCorrect() const {
    //Checking if amount of colors is correct
    unsigned char amountYellow = 0;
    unsigned char amountWhite = 0;
    unsigned char amountOrange = 0;
    unsigned char amountRed = 0;
    unsigned char amountBlue = 0;
    unsigned char amountGreen = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            increaseColor(amountYellow, amountWhite, amountOrange, amountRed, amountBlue, amountGreen,
                          UpPlane[i][j]->getUpColor());
            increaseColor(amountYellow, amountWhite, amountOrange, amountRed, amountBlue, amountGreen,
                          DownPlane[i][j]->getDownColor());
            increaseColor(amountYellow, amountWhite, amountOrange, amountRed, amountBlue, amountGreen,
                          LeftPlane[i][j]->getLeftColor());
            increaseColor(amountYellow, amountWhite, amountOrange, amountRed, amountBlue, amountGreen,
                          RightPlane[i][j]->getRightColor());
            increaseColor(amountYellow, amountWhite, amountOrange, amountRed, amountBlue, amountGreen,
                          FrontPlane[i][j]->getFrontColor());
            increaseColor(amountYellow, amountWhite, amountOrange, amountRed, amountBlue, amountGreen,
                          BackPlane[i][j]->getBackColor());
        }
    }
    bool amountColors = amountYellow == 9 && amountWhite == 9 && amountOrange == 9 && amountRed == 9 && amountBlue == 9
            && amountGreen == 9;
    bool yellowWhiteCheck = ((UpCenter == "Y") && (DownCenter == "W") || (DownCenter == "Y") && (UpCenter == "W")||
            (LeftCenter == "Y") && (RightCenter == "W") || (RightCenter == "Y") && (LeftCenter == "W") ||
            (FrontCenter == "Y") && (BackCenter == "W") || (BackCenter == "Y") && (FrontCenter == "W"));
    bool orangeRedCheck = ((UpCenter == "O") && (DownCenter == "R") || (DownCenter == "O") && (UpCenter == "R")||
            (LeftCenter == "O") && (RightCenter == "R") || (RightCenter == "O") && (LeftCenter == "R") ||
            (FrontCenter == "O") && (BackCenter == "R") || (BackCenter == "O") && (FrontCenter == "R"));
    bool blueGreenCheck = ((UpCenter == "B") && (DownCenter == "G") || (DownCenter == "B") && (UpCenter == "G")||
            (LeftCenter == "B") && (RightCenter == "G") || (RightCenter == "B") && (LeftCenter == "G") ||
            (FrontCenter == "B") && (BackCenter == "G") || (BackCenter == "B") && (FrontCenter == "G"));
    return amountColors && yellowWhiteCheck && orangeRedCheck && blueGreenCheck;
}

//Helping function for checking is Cube correct
void CubeRubik::increaseColor(unsigned char &yellow, unsigned char &white, unsigned char &orange, unsigned char &red,
                              unsigned char &blue, unsigned char &green, const string& color) const {
    if (color == "Y") {
        yellow++;
    } else if (color == "W") {
        white++;
    } else if (color == "O") {
        orange++;
    } else if (color == "R") {
        red++;
    } else if (color == "B") {
        blue++;
    } else if (color == "G") {
        green++;
    }
}

//Checking if steps are completed
//Checking if first step completed
[[nodiscard]] bool CubeRubik::isFirstStepCompleted() {
    bool downCompleted = DownPlane[0][1]->getDownColor() == DownCenter && DownPlane[1][0]->getDownColor() == DownCenter
            && DownPlane[1][2]->getDownColor() == DownCenter && DownPlane[2][1]->getDownColor() == DownCenter;
    bool frontCompleted = FrontPlane[2][1]->getFrontColor() == FrontCenter;
    bool rightCompleted = RightPlane[2][1]->getRightColor() == RightCenter;
    bool backCompleted = BackPlane[2][1]->getBackColor() == BackCenter;
    bool leftCompleted = LeftPlane[2][1]->getLeftColor() == LeftCenter;
    return downCompleted && frontCompleted && rightCompleted && backCompleted && leftCompleted;
}

//Checking if second step is completed
[[nodiscard]] bool CubeRubik::isSecondStepCompleted() {
    bool firstCompleted = isFirstStepCompleted();
    bool downCompleted = DownPlane[0][0]->getDownColor() == DownCenter && DownPlane[0][2]->getDownColor() == DownCenter
            && DownPlane[2][0]->getDownColor() == DownCenter && DownPlane[2][2]->getDownColor() == DownCenter;
    bool frontCompleted = FrontPlane[2][0]->getFrontColor() == FrontCenter && FrontPlane[2][2]->getFrontColor() == FrontCenter;
    bool rightCompleted = RightPlane[2][0]->getRightColor() == RightCenter && RightPlane[2][2]->getRightColor() == RightCenter;
    bool backCompleted = BackPlane[2][0]->getBackColor() == BackCenter && BackPlane[2][2]->getBackColor() == BackCenter;
    bool leftCompleted = LeftPlane[2][0]->getLeftColor() == LeftCenter && LeftPlane[2][2]->getLeftColor() == LeftCenter;
    return firstCompleted && downCompleted && frontCompleted && rightCompleted && backCompleted && leftCompleted;
}

//Checking if third step completed
[[nodiscard]] bool CubeRubik::isThirdStepCompleted() {
    bool secondCompleted = isSecondStepCompleted();
    bool frontCompleted = FrontPlane[1][0]->getFrontColor() == FrontCenter && FrontPlane[1][2]->getFrontColor() == FrontCenter;
    bool rightCompleted = RightPlane[1][0]->getRightColor() == RightCenter && RightPlane[1][2]->getRightColor() == RightCenter;
    bool backCompleted = BackPlane[1][0]->getBackColor() == BackCenter && BackPlane[1][2]->getBackColor() == BackCenter;
    bool leftCompleted = LeftPlane[1][0]->getLeftColor() == LeftCenter && LeftPlane[1][2]->getLeftColor() == LeftCenter;
    return secondCompleted && frontCompleted && rightCompleted && backCompleted && leftCompleted;
}

//Checking if fourth step completed
[[nodiscard]] bool CubeRubik::isFourthStepCompleted() {
    bool thirdCompleted = isThirdStepCompleted();
    bool upCompleted = UpPlane[0][1]->getUpColor() == UpCenter && UpPlane[1][0]->getUpColor() == UpCenter &&
            UpPlane[1][2]->getUpColor() == UpCenter && UpPlane[2][1]->getUpColor() == UpCenter;
    return thirdCompleted && upCompleted;
}

//Checking if fifth step completed
[[nodiscard]] bool CubeRubik::isFifthStepCompleted() {
    bool fourthCompleted = isFourthStepCompleted();
    //Checking if upper angles are correct
    bool frontLeftCompleted = (FrontPlane[0][0]->getFrontColor() == FrontCenter || FrontPlane[0][0]->getFrontColor() ==
            LeftCenter || FrontPlane[0][0]->getFrontColor() == UpCenter) && (LeftPlane[0][2]->getLeftColor() ==
                    LeftCenter || LeftPlane[0][2]->getLeftColor() == FrontCenter || LeftPlane[0][2]->getLeftColor()
                    == UpCenter) && (UpPlane[2][0]->getUpColor() == UpCenter || UpPlane[2][0]->getUpColor()
                            == FrontCenter || UpPlane[2][0]->getUpColor() == LeftCenter);
    bool frontRightCompleted = (FrontPlane[0][2]->getFrontColor() == FrontCenter || FrontPlane[0][2]->getFrontColor()
            == RightCenter || FrontPlane[0][2]->getFrontColor() == UpCenter) && (RightPlane[0][0]->getRightColor()
                    == RightCenter || RightPlane[0][0]->getRightColor() == FrontCenter ||
                    RightPlane[0][0]->getRightColor() == UpCenter) && (UpPlane[2][2]->getUpColor() == UpCenter ||
                            UpPlane[2][2]->getUpColor() == FrontCenter || UpPlane[2][2]->getUpColor() == RightCenter);
    bool backLeftCompleted = (BackPlane[0][2]->getBackColor() == BackCenter || BackPlane[0][2]->getBackColor() ==
            LeftCenter || BackPlane[0][2]->getBackColor() == UpCenter) && (LeftPlane[0][0]->getLeftColor() == LeftCenter
                    || LeftPlane[0][0]->getLeftColor() == BackCenter || LeftPlane[0][0]->getLeftColor() == UpCenter) &&
                            (UpPlane[0][0]->getUpColor() == UpCenter || UpPlane[0][0]->getUpColor() == BackCenter ||
                            UpPlane[0][0]->getUpColor() == LeftCenter);
    bool backRightCompleted = (BackPlane[0][0]->getBackColor() == BackCenter || BackPlane[0][0]->getBackColor() ==
            RightCenter || BackPlane[0][0]->getBackColor() == UpCenter) && (RightPlane[0][2]->getRightColor() ==
                    RightCenter || RightPlane[0][2]->getRightColor() == BackCenter || RightPlane[0][2]->getRightColor()
                    == UpCenter) && (UpPlane[0][2]->getUpColor() == UpCenter || UpPlane[0][2]->getUpColor() ==
                            BackCenter || UpPlane[0][2]->getUpColor() == RightCenter);
    return fourthCompleted && frontLeftCompleted && frontRightCompleted && backLeftCompleted && backRightCompleted;
}

//Checking if sixth step completed
[[nodiscard]] bool CubeRubik::isSixthStepCompleted() {
    //bool fifthCompleted = isFifthStepCompleted();
    bool fifthCompleted = isFifthStepCompleted();
    //Checking if angles correct
    bool frontLeftCompleted = FrontPlane[0][0]->getFrontColor() == FrontCenter && LeftPlane[0][2]->getLeftColor()
            == LeftCenter && UpPlane[2][0]->getUpColor() == UpCenter;
    bool frontRightCompleted = FrontPlane[0][2]->getFrontColor() == FrontCenter && RightPlane[0][0]->getRightColor()
            == RightCenter && UpPlane[2][2]->getUpColor() == UpCenter;
    bool backLeftCompleted = BackPlane[0][2]->getBackColor() == BackCenter && LeftPlane[0][0]->getLeftColor() ==
            LeftCenter && UpPlane[0][0]->getUpColor() == UpCenter;
    bool backRightCompleted = BackPlane[0][0]->getBackColor() == BackCenter && RightPlane[0][2]->getRightColor() ==
            RightCenter && UpPlane[0][2]->getUpColor() == UpCenter;
    return fifthCompleted && frontLeftCompleted && frontRightCompleted && backLeftCompleted && backRightCompleted;
}

//Checking if seventh step completed
[[nodiscard]] bool CubeRubik::isSeventhStepCompleted() {
    bool sixthCompleted = isSixthStepCompleted();
    //Checking if up middle pieces are correct;
    bool frontCompleted = FrontPlane[0][1]->getFrontColor() == FrontCenter && UpPlane[2][1]->getUpColor() == UpCenter;
    bool rightCompleted = RightPlane[0][1]->getRightColor() == RightCenter && UpPlane[1][2]->getUpColor() == UpCenter;
    bool backCompleted = BackPlane[0][1]->getBackColor() == BackCenter && UpPlane[0][1]->getUpColor() == UpCenter;
    bool leftCompleted = LeftPlane[0][1]->getLeftColor() == LeftCenter && UpPlane[1][0]->getUpColor() == UpCenter;
    return sixthCompleted && frontCompleted && rightCompleted && backCompleted && leftCompleted;
}

//First step of solving Rubik's Cube
void CubeRubik::firstStep() {
    int count = 0;
    int i;
    for (i = 0; i < 128 && !isFirstStepCompleted(); i++) {
        if (FrontCenter == FrontPlane[0][1]->getFrontColor() && UpPlane[2][1]->getUpColor() == DownCenter) {
            rotatePlanes("F F ");
            firstStepCounter += 2;
            rotatesCounter += 2;
            count = 0;
            continue;
        }
        if (RightCenter == RightPlane[0][1]->getRightColor() && UpPlane[1][2]->getUpColor() == DownCenter) {
            rotatePlanes("R R ");
            firstStepCounter += 2;
            rotatesCounter += 2;
            count = 0;
            continue;
        }
        if (BackCenter == BackPlane[0][1]->getBackColor() && UpPlane[0][1]->getUpColor() == DownCenter) {
            rotatePlanes("B B ");
            firstStepCounter += 2;
            rotatesCounter += 2;
            count = 0;
            continue;
        }
        if (LeftCenter == LeftPlane[0][1]->getLeftColor() && UpPlane[1][0]->getLeftColor() == DownCenter) {
            rotatePlanes("L L ");
            firstStepCounter += 2;
            rotatesCounter += 2;
            count = 0;
            continue;
        }
        if (FrontPlane[0][1]->getFrontColor() == DownCenter && UpPlane[2][1]->getUpColor() == FrontCenter) {
            rotatePlanes("U'R'F R ");
            firstStepCounter += 4;
            rotatesCounter += 4;
            count = 0;
            continue;
        }
        if (RightPlane[0][1]->getRightColor() == DownCenter && UpPlane[1][2]->getUpColor() == RightCenter) {
            rotatePlanes("U'B'R B ");
            firstStepCounter += 4;
            rotatesCounter += 4;
            count = 0;
            continue;
        }
        if (BackPlane[0][1]->getBackColor() == DownCenter && UpPlane[0][1]->getUpColor() == BackCenter) {
            rotatePlanes("U'L'B L ");
            firstStepCounter += 4;
            rotatesCounter += 4;
            count = 0;
            continue;
        }
        if (LeftPlane[0][1]->getLeftColor() == DownCenter && UpPlane[1][0]->getUpColor() == LeftCenter) {
            rotatePlanes("U'F'L F ");
            firstStepCounter += 4;
            rotatesCounter += 4;
            count = 0;
            continue;
        }
        if (FrontPlane[1][2]->getFrontColor() == DownCenter) {
            rotatePlanes("F'U'F ");
            firstStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (RightPlane[1][2]->getRightColor() == DownCenter) {
            rotatePlanes("R'U'R ");
            firstStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (BackPlane[1][2]->getBackColor() == DownCenter) {
            rotatePlanes("B'U'B ");
            firstStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (LeftPlane[1][2]->getLeftColor() == DownCenter) {
            rotatePlanes("L'U'L ");
            firstStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (FrontPlane[1][0]->getFrontColor() == DownCenter) {
            rotatePlanes("F U'F'");
            firstStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (RightPlane[1][0]->getRightColor() == DownCenter) {
            rotatePlanes("R U'R'");
            firstStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (BackPlane[1][0]->getBackColor() == DownCenter) {
            rotatePlanes("B U'B'");
            firstStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (LeftPlane[1][0]->getLeftColor() == DownCenter) {
            rotatePlanes("L U'L'");
            firstStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (FrontPlane[2][1]->getFrontColor() == DownCenter ||
            (DownPlane[0][1]->getDownColor() == DownCenter && FrontPlane[2][1]->getFrontColor() != FrontCenter)) {
            rotatePlanes("F F U'F F ");
            firstStepCounter += 5;
            rotatesCounter += 5;
            count = 0;
            continue;
        }
        if (RightPlane[2][1]->getRightColor() == DownCenter ||
            (DownPlane[1][2]->getDownColor() == DownCenter && RightPlane[2][1]->getRightColor() != RightCenter)) {
            rotatePlanes("R R U'R R ");
            firstStepCounter += 5;
            rotatesCounter += 5;
            count = 0;
            continue;
        }
        if (BackPlane[2][1]->getBackColor() == DownCenter ||
            (DownPlane[2][1]->getDownColor() == DownCenter && BackPlane[2][1]->getBackColor() != BackCenter)) {
            rotatePlanes("B B U'B B ");
            firstStepCounter += 5;
            rotatesCounter += 5;
            count = 0;
            continue;
        }
        if (LeftPlane[2][1]->getLeftColor() == DownCenter ||
            (DownPlane[1][0]->getDownColor() == DownCenter && LeftPlane[2][1]->getLeftColor() != LeftCenter)) {
            rotatePlanes("L L U'L L ");
            firstStepCounter += 5;
            rotatesCounter += 5;
            count = 0;
            continue;
        }
        if (!isFirstStepCompleted() && count < 4) {
            count++;
            rotatePlanes("U ");
            firstStepCounter++;
            rotatesCounter++;
        } else if (!isFirstStepCompleted() && count >= 4) {
            shuffle(3);
            count = 0;
        }
    }
    if (i > 127) {
        throw logic_error("\n\nError occurred while solving first step\n\n");
    }
}

//Second step of solving Rubik's Cube
void CubeRubik::secondStep() {
    int count = 0;
    int i;
    for (i = 0; i < 128 && !isSecondStepCompleted(); i++) {
        if (FrontPlane[0][2]->getFrontColor() == FrontCenter && RightPlane[0][0]->getRightColor() == DownCenter
            && UpPlane[2][2]->getUpColor() == RightCenter) {
            rotatePlanes("R U R'");
            secondStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (RightPlane[0][2]->getRightColor() == RightCenter && BackPlane[0][0]->getBackColor() == DownCenter
            && UpPlane[0][2]->getUpColor() == BackCenter) {
            rotatePlanes("B U B'");
            secondStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (BackPlane[0][2]->getBackColor() == BackCenter && LeftPlane[0][0]->getLeftColor() == DownCenter
            && UpPlane[0][0]->getUpColor() == LeftCenter) {
            rotatePlanes("L U L'");
            secondStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (LeftPlane[0][2]->getLeftColor() == LeftCenter && FrontPlane[0][0]->getFrontColor() == DownCenter
            && UpPlane[2][0]->getUpColor() == FrontCenter) {
            rotatePlanes("F U F'");
            secondStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (FrontPlane[2][2]->getFrontColor() == RightCenter && RightPlane[2][0]->getRightColor() == DownCenter
            && DownPlane[0][2]->getDownColor() == FrontCenter) {
            rotatePlanes("R U R'U'R U R'");
            secondStepCounter += 7;
            rotatesCounter += 7;
            count = 0;
            continue;
        }
        if (RightPlane[2][2]->getRightColor() == BackCenter && BackPlane[2][0]->getBackColor() == DownCenter
            && DownPlane[2][2]->getDownColor() == RightCenter) {
            rotatePlanes("B U B'U'B U B'");
            secondStepCounter += 7;
            rotatesCounter += 7;
            count = 0;
            continue;
        }
        if (BackPlane[2][2]->getBackColor() == LeftCenter && LeftPlane[2][0]->getLeftColor() == DownCenter
            && DownPlane[2][0]->getDownColor() == BackCenter) {
            rotatePlanes("L U L'U'L U L'");
            secondStepCounter += 7;
            rotatesCounter += 7;
            count = 0;
            continue;
        }
        if (LeftPlane[2][2]->getLeftColor() == FrontCenter && FrontPlane[2][0]->getFrontColor() == DownCenter
            && DownPlane[0][0]->getDownColor() == LeftCenter) {
            rotatePlanes("F U F'U'F U F'");
            secondStepCounter += 7;
            rotatesCounter += 7;
            count = 0;
            continue;
        }
        if (FrontPlane[0][2]->getFrontColor() == RightCenter && RightPlane[0][0]->getRightColor() == FrontCenter
            && UpPlane[2][2]->getUpColor() == DownCenter) {
            rotatePlanes("R U R'U'R U R'U'R U R'");
            secondStepCounter += 11;
            rotatesCounter += 11;
            count = 0;
            continue;
        }
        if (RightPlane[0][2]->getRightColor() == BackCenter && BackPlane[0][0]->getBackColor() == RightCenter
            && UpPlane[0][2]->getUpColor() == DownCenter) {
            rotatePlanes("B U B'U'B U B'U'B U B'");
            secondStepCounter += 11;
            rotatesCounter += 11;
            count = 0;
            continue;
        }
        if (BackPlane[0][2]->getBackColor() == LeftCenter && LeftPlane[0][0]->getLeftColor() == BackCenter
            && UpPlane[0][0]->getUpColor() == DownCenter) {
            rotatePlanes("L U L'U'L U L'U'L U L'");
            secondStepCounter += 11;
            rotatesCounter += 11;
            count = 0;
            continue;
        }
        if (LeftPlane[0][2]->getLeftColor() == FrontCenter && FrontPlane[0][0]->getFrontColor() == LeftCenter
            && UpPlane[2][0]->getUpColor() == DownCenter) {
            rotatePlanes("F U F'U'F U F'U'F U F'");
            secondStepCounter += 11;
            rotatesCounter += 11;
            count = 0;
            continue;
        }
        if (FrontPlane[2][2]->getFrontColor() == DownCenter && RightPlane[2][0]->getRightColor() == FrontCenter
            && DownPlane[0][2]->getDownColor() == RightCenter) {
            rotatePlanes("R U R'U'R U R'U'R U R'U'R U R'");
            secondStepCounter += 15;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (RightPlane[2][2]->getRightColor() == DownCenter && BackPlane[2][0]->getBackColor() == RightCenter
            && DownPlane[2][2]->getDownColor() == BackCenter) {
            rotatePlanes("B U B'U'B U B'U'B U B'U'B U B'");
            secondStepCounter += 15;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (BackPlane[2][2]->getBackColor() == DownCenter && LeftPlane[2][0]->getLeftColor() == BackCenter
            && DownPlane[2][0]->getDownColor() == LeftCenter) {
            rotatePlanes("L U L'U'L U L'U'L U L'U'L U L'");
            secondStepCounter += 15;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (LeftPlane[2][2]->getLeftColor() == DownCenter && FrontPlane[2][0]->getFrontColor() == LeftCenter
            && DownPlane[0][0]->getDownColor() == FrontCenter) {
            rotatePlanes("F U F'U'F U F'U'F U F'U'F U F'");
            secondStepCounter += 15;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (FrontPlane[0][2]->getFrontColor() == DownCenter && RightPlane[0][0]->getRightColor() == RightCenter
            && UpPlane[2][2]->getUpColor() == FrontCenter) {
            rotatePlanes("R U R'U'R U R'U'R U R'U'R U R'U'R U R'");
            secondStepCounter += 19;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (RightPlane[0][2]->getRightColor() == DownCenter && BackPlane[0][0]->getBackColor() == BackCenter
            && UpPlane[0][2]->getUpColor() == RightCenter) {
            rotatePlanes("B U B'U'B U B'U'B U B'U'B U B'U'B U B'");
            secondStepCounter += 19;
            rotatesCounter += 19;
            count = 0;
            continue;
        }
        if (BackPlane[0][2]->getBackColor() == DownCenter && LeftPlane[0][0]->getLeftColor() == LeftCenter
            && UpPlane[0][0]->getUpColor() == BackCenter) {
            rotatePlanes("L U L'U'L U L'U'L U L'U'L U L'U'L U L'");
            secondStepCounter += 19;
            rotatesCounter += 19;
            count = 0;
            continue;
        }
        if (LeftPlane[0][2]->getLeftColor() == DownCenter && FrontPlane[0][0]->getFrontColor() == FrontCenter
            && UpPlane[2][0]->getUpColor() == LeftCenter) {
            rotatePlanes("F U F'U'F U F'U'F U F'U'F U F'U'F U F'");
            secondStepCounter += 19;
            rotatesCounter += 19;
            count = 0;
            continue;
        }
        bool wrongFrontColors = (DownPlane[0][2]->getDownColor() == DownCenter || DownPlane[0][2]->getDownColor() == FrontCenter
                || DownPlane[0][2]->getDownColor() == RightCenter) && (RightPlane[2][0]->getRightColor() == DownCenter
                        || RightPlane[2][0]->getRightColor() == FrontCenter || RightPlane[2][0]->getRightColor() == RightCenter)
                                && (FrontPlane[2][2]->getFrontColor() == DownCenter || FrontPlane[2][2]->getFrontColor() == FrontCenter
                                || FrontPlane[2][2]->getFrontColor() == RightCenter);
        bool extraFrontColors = DownPlane[0][2]->getDownColor() == DownCenter || FrontPlane[2][2]->getFrontColor() == DownCenter
                || RightPlane[2][0]->getRightColor() == DownCenter;
        if (!wrongFrontColors && extraFrontColors) {
            rotatePlanes("R U R'");
            secondStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        bool wrongRightColors = (DownPlane[2][2]->getDownColor() == DownCenter || DownPlane[2][2]->getDownColor() == RightCenter
                || DownPlane[2][2]->getDownColor() == BackCenter) && (RightPlane[2][2]->getRightColor() == DownCenter
                        || RightPlane[2][2]->getRightColor() == RightCenter || RightPlane[2][2]->getRightColor() == BackCenter)
                                && (BackPlane[2][0]->getBackColor() == DownCenter || BackPlane[2][0]->getBackColor() == RightCenter
                                || BackPlane[2][0]->getBackColor() == BackCenter);
        bool extraRightColors = DownPlane[2][2]->getDownColor() == DownCenter || RightPlane[2][2]->getRightColor() == DownCenter
                || BackPlane[2][0]->getBackColor() == DownCenter;
        if (!wrongRightColors && extraRightColors) {
            rotatePlanes("B U B'");
            secondStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        bool wrongBackColors = (DownPlane[2][0]->getDownColor() == DownCenter || DownPlane[2][0]->getDownColor() == BackCenter
                || DownPlane[2][0]->getDownColor() == LeftCenter) && (BackPlane[2][2]->getBackColor() == DownCenter
                        || BackPlane[2][2]->getBackColor() == BackCenter || BackPlane[2][2]->getBackColor() == LeftCenter)
                                && (LeftPlane[2][0]->getLeftColor() == DownCenter || LeftPlane[2][0]->getLeftColor() == BackCenter
                                || LeftPlane[2][0]->getLeftColor() == LeftCenter);
        bool extraBackColors = DownPlane[2][0]->getDownColor() == DownCenter || BackPlane[2][2]->getBackColor() == DownCenter
                || LeftPlane[2][0]->getLeftColor() == DownCenter;
        if (!wrongBackColors && extraBackColors) {
            rotatePlanes("L U L'");
            secondStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        bool wrongLeftColors = (DownPlane[0][0]->getDownColor() == DownCenter || DownPlane[0][0]->getDownColor() == LeftCenter
                || DownPlane[0][0]->getDownColor() == FrontCenter) && (LeftPlane[2][2]->getLeftColor() == DownCenter
                        || LeftPlane[2][2]->getLeftColor() == LeftCenter || LeftPlane[2][2]->getLeftColor() == FrontCenter)
                                && (FrontPlane[2][0]->getFrontColor() == DownCenter || FrontPlane[2][0]->getFrontColor() == LeftCenter
                                || FrontPlane[2][0]->getFrontColor() == FrontCenter);
        bool extraLeftColors = DownPlane[0][0]->getDownColor() == DownCenter || LeftPlane[2][2]->getLeftColor() == DownCenter
                || FrontPlane[2][0]->getFrontColor() == DownCenter;
        if (!wrongLeftColors && extraLeftColors) {
            rotatePlanes("F U F'");
            secondStepCounter += 3;
            rotatesCounter += 3;
            count = 0;
            continue;
        }
        if (count < 4 && !isSecondStepCompleted()) {
            count++;
            rotatePlanes("U ");
            secondStepCounter++;
            rotatesCounter++;
        } else if (count == 4 && !isSecondStepCompleted()) {
            shuffle(3);
            firstStep();
            count = 0;
        }
    }
    if (i > 127) {
        throw logic_error("\n\nError occurred while solving second step\n\n");
    }
}

void CubeRubik::thirdStep() {
    int count = 0;
    int i;
    for (i = 0; i < 128 && !isThirdStepCompleted(); i++) {
        if (FrontPlane[0][1]->getFrontColor() == FrontCenter && UpPlane[2][1]->getUpColor() == RightCenter) {
            rotatePlanes("U R U R'U'F'U'F ");
            thirdStepCounter += 8;
            rotatesCounter += 8;
            count = 0;
            continue;
        }
        if (FrontPlane[0][1]->getFrontColor() == FrontCenter && UpPlane[2][1]->getUpColor() == LeftCenter) {
            rotatePlanes("U'L'U'L U F U F'");
            thirdStepCounter += 8;
            rotatesCounter += 8;
            count = 0;
            continue;
        }
        if (RightPlane[0][1]->getRightColor() == RightCenter && UpPlane[1][2]->getUpColor() == BackCenter) {
            rotatePlanes("U B U B'U'R'U'R ");
            thirdStepCounter += 8;
            rotatesCounter += 8;
            count = 0;
            continue;
        }
        if (RightPlane[0][1]->getRightColor() == RightCenter && UpPlane[1][2]->getUpColor() == FrontCenter) {
            rotatePlanes("U'F'U'F U R U R'");
            thirdStepCounter += 8;
            rotatesCounter += 8;
            count = 0;
            continue;
        }
        if (BackPlane[0][1]->getBackColor() == BackCenter && UpPlane[0][1]->getUpColor() == LeftCenter) {
            rotatePlanes("U L U L'U'B'U'B ");
            thirdStepCounter += 8;
            rotatesCounter += 8;
            count = 0;
            continue;
        }
        if (BackPlane[0][1]->getBackColor() == BackCenter && UpPlane[0][1]->getUpColor() == RightCenter) {
            rotatePlanes("U'R'U'R U B U B'");
            thirdStepCounter += 8;
            rotatesCounter += 8;
            count = 0;
            continue;
        }
        if (LeftPlane[0][1]->getLeftColor() == LeftCenter && UpPlane[1][0]->getUpColor() == FrontCenter) {
            rotatePlanes("U F U F'U'L'U'L ");
            thirdStepCounter += 8;
            rotatesCounter += 8;
            count = 0;
            continue;
        }
        if (LeftPlane[0][1]->getLeftColor() == LeftCenter && UpPlane[1][0]->getUpColor() == BackCenter) {
            rotatePlanes("U'B'U'B U L U L'");
            thirdStepCounter += 8;
            rotatesCounter += 8;
            count = 0;
            continue;
        }
        if (FrontPlane[1][2]->getFrontColor() == RightCenter && RightPlane[1][0]->getRightColor() == FrontCenter) {
            rotatePlanes("R U R'U'F'U'F ");
            thirdStepCounter += 7;
            rotatesCounter += 7;
            count = 0;
            continue;
        }
        if (RightPlane[1][2]->getRightColor() == BackCenter && BackPlane[1][0]->getBackColor() == RightCenter) {
            rotatePlanes("B U B'U'R'U'R ");
            thirdStepCounter += 7;
            rotatesCounter += 7;
            count = 0;
            continue;
        }
        if (BackPlane[1][2]->getBackColor() == LeftCenter && LeftPlane[1][0]->getLeftColor() == BackCenter) {
            rotatePlanes("L U L'U'B'U'B ");
            thirdStepCounter += 7;
            rotatesCounter += 7;
            count = 0;
            continue;
        }
        if (LeftPlane[1][2]->getLeftColor() == FrontCenter && FrontPlane[1][0]->getFrontColor() == LeftCenter) {
            rotatePlanes("F U F'U'L'U'L ");
            thirdStepCounter += 7;
            rotatesCounter += 7;
            count = 0;
            continue;
        }
        if (count < 4 && !isThirdStepCompleted()) {
            count++;
            rotatePlanes("U ");
            thirdStepCounter++;
            rotatesCounter++;
        } else if (count == 4 && !isThirdStepCompleted()) {
            shuffle(3);
            count = 0;
            firstStep();
            secondStep();
        }
    }
    if (i > 127) {
        throw logic_error("\n\nError occurred while solving third step\n\n");
    }
}

void CubeRubik::fourthStep() {
    int count = 0;
    int i;
    for (i = 0; i < 128 && !isFourthStepCompleted(); i++) {
        if (UpPlane[0][1]->getUpColor() == UpCenter && UpPlane[1][0]->getUpColor() == UpCenter
        || UpPlane[1][0]->getUpColor() == UpCenter && UpPlane[1][2]->getUpColor() == UpCenter ||
        UpPlane[0][1]->getUpColor() != UpCenter && UpPlane[1][0]->getUpColor() != UpCenter &&
        UpPlane[2][1]->getUpColor() != UpCenter && UpPlane[1][2]->getUpColor() != UpCenter) {
            rotatePlanes("F R U R'U'R U R'U'F'");
            fourthStepCounter += 10;
            rotatesCounter += 10;
            count = 0;
            continue;
        }
        if (UpPlane[1][0]->getUpColor() == UpCenter && UpPlane[2][1]->getUpColor() == UpCenter
        || UpPlane[2][1]->getUpColor() == UpCenter && UpPlane[0][1]->getUpColor() == UpCenter) {
            rotatePlanes("R B U B'U'B U B'U'R'");
            fourthStepCounter += 10;
            rotatesCounter += 10;
            count = 0;
            continue;
        }
        if (UpPlane[2][1]->getUpColor() == UpCenter && UpPlane[1][2]->getUpColor() == UpCenter) {
            rotatePlanes("B L U L'U'L U L'U'B'");
            fourthStepCounter += 10;
            rotatesCounter += 10;
            count = 0;
            continue;
        }
        if (UpPlane[1][2]->getUpColor() == UpCenter && UpPlane[0][1]->getUpColor() == UpCenter) {
            rotatePlanes("L F U F'U'F U F'U'L'");
            fourthStepCounter += 10;
            rotatesCounter += 10;
            count = 0;
            continue;
        }
        if (count < 4 && !isFourthStepCompleted()) {
            count++;
        } else if (count == 4 && !isFourthStepCompleted()) {
            shuffle();
            firstStep();
            secondStep();
            thirdStep();
            count = 0;
        }
    }
    if (i > 127) {
        throw logic_error("\n\nError occurred while solving fourth step\n\n");
    }
}

void CubeRubik::fifthStep() {
    int count = 0;
    int i;
    for (i = 0; i < 128 && !isFifthStepCompleted(); i++) {
        bool leftFrontAngle = (FrontPlane[0][0]->getFrontColor() == FrontCenter || FrontPlane[0][0]->getFrontColor() == UpCenter
                || FrontPlane[0][0]->getFrontColor() == LeftCenter) && (UpPlane[2][0]->getUpColor() == FrontCenter ||
                        UpPlane[2][0]->getUpColor() == UpCenter || UpPlane[2][0]->getUpColor() == LeftCenter) &&
                                (LeftPlane[0][2]->getLeftColor() == FrontCenter || LeftPlane[0][2]->getLeftColor() == UpCenter
                                || LeftPlane[0][2]->getLeftColor() == LeftCenter);
        bool rightFrontAngle = (FrontPlane[0][2]->getFrontColor() == FrontCenter || FrontPlane[0][2]->getFrontColor() == UpCenter
                || FrontPlane[0][2]->getFrontColor() == RightCenter) && (UpPlane[2][2]->getUpColor() == FrontCenter
                        || UpPlane[2][2]->getUpColor() == UpCenter || UpPlane[2][2]->getUpColor() == RightCenter) &&
                                (RightPlane[0][0]->getRightColor() == FrontCenter || RightPlane[0][0]->getRightColor() == UpCenter
                                || RightPlane[0][0]->getRightColor() == RightCenter);
        bool leftBackAngle = (BackPlane[0][2]->getBackColor() == BackCenter || BackPlane[0][2]->getBackColor() == UpCenter
                || BackPlane[0][2]->getBackColor() == LeftCenter) && (LeftPlane[0][0]->getLeftColor() == BackCenter ||
                        LeftPlane[0][0]->getLeftColor() == UpCenter || LeftPlane[0][0]->getLeftColor() == LeftCenter) &&
                                (UpPlane[0][0]->getUpColor() == BackCenter || UpPlane[0][0]->getUpColor() == UpCenter
                                || UpPlane[0][0]->getUpColor() == LeftCenter);
        bool rightBackAngle = (BackPlane[0][0]->getBackColor() == BackCenter || BackPlane[0][0]->getBackColor() == UpCenter
                || BackPlane[0][0]->getBackColor() == RightCenter) && (UpPlane[0][2]->getUpColor() == BackCenter ||
                        UpPlane[0][2]->getUpColor() == UpCenter || UpPlane[0][2]->getUpColor() == RightCenter) &&
                                (RightPlane[0][2]->getRightColor() == BackCenter || RightPlane[0][2]->getRightColor() == UpCenter
                                || RightPlane[0][2]->getRightColor() == RightCenter);
        if (leftFrontAngle && leftBackAngle || leftFrontAngle && rightBackAngle) {
            rotatePlanes("R U R'U'R U R'U'R U R'U'F'U'F U F'U'F U F'U'F ");
            fifthStepCounter += 15;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (rightFrontAngle && leftFrontAngle || rightFrontAngle && leftBackAngle) {
            rotatePlanes("B U B'U'B U B'U'B U B'U'R'U'R U R'U'R U R'U'R ");
            fifthStepCounter += 15;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (rightBackAngle && rightFrontAngle) {
            rotatePlanes("L U L'U'L U L'U'L U L'U'B'U'B U B'U'B U B'U'B ");
            fifthStepCounter += 15;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (leftBackAngle && rightBackAngle) {
            rotatePlanes("F U F'U'F U F'U'F U F'U'L'U'L U L'U'L U L'U'L ");
            fifthStepCounter += 15;
            rotatesCounter += 15;
            count = 0;
            continue;
        }
        if (count < 4 && !isFifthStepCompleted()) {
            count++;
            rotatePlanes("U ");
            fifthStepCounter++;
            rotatesCounter++;
        } else if (count == 4 && !isFifthStepCompleted()) {
            shuffle(3);
            firstStep();
            secondStep();
            thirdStep();
            fourthStep();
            count = 0;
        }
    }
    if (i > 127) {
        throw logic_error("\n\nError occurred while solving fifth step\n\n");
    }
}

void CubeRubik::sixthStep() {
    int count = 0;
    int i;
    for (i = 0; i < 124 && !isSixthStepCompleted(); i++) {
        if (UpPlane[2][0]->getUpColor() != UpCenter) {
            rotatePlanes("L D L'D'");
            sixthStepCounter += 4;
            rotatesCounter += 4;
            count = 0;
            continue;
        }
        if (count < 4 && !isSixthStepCompleted()) {
            rotatePlanes("U ");
            sixthStepCounter++;
            rotatesCounter++;
            count++;
        } else if (count == 4 && !isSixthStepCompleted()) {
            shuffle(3);
            firstStep();
            secondStep();
            thirdStep();
            fourthStep();
            fifthStep();
            count = 0;
        }
    }
    if (i > 127) {
        throw logic_error("\n\nError occurred while solving sixth step\n\n");
    }
}

void CubeRubik::seventhStep() {
    int count = 0;
    int i;
    for (i = 0; i < 128 && !isSeventhStepCompleted(); i++) {
        bool frontAnglesCorrect = FrontPlane[0][0]->getFrontColor() == FrontCenter && FrontPlane[0][2]->getFrontColor() == FrontCenter;
        bool frontCenterCorrect = FrontPlane[0][1]->getFrontColor() == FrontCenter;
        bool rightAnglesCorrect = RightPlane[0][0]->getRightColor() == RightCenter && RightPlane[0][2]->getRightColor() == RightCenter;
        bool rightCenterCorrect = RightPlane[0][1]->getRightColor() == RightCenter;
        bool backAnglesCorrect = BackPlane[0][0]->getBackColor() == BackCenter && BackPlane[0][2]->getBackColor() == BackCenter;
        bool backCenterCorrect = BackPlane[0][1]->getBackColor() == BackCenter;
        bool leftAnglesCorrect = LeftPlane[0][0]->getLeftColor() == LeftCenter && LeftPlane[0][2]->getLeftColor() == LeftCenter;
        bool leftCenterCorrect = LeftPlane[0][1]->getLeftColor() == LeftCenter;
        if (frontAnglesCorrect && frontCenterCorrect) {
            rotatePlanes("R U R'U'L'U'L U R U R'U'R U R'U'R U R'U'R U R'U'R U R'U'L'U'L U L'U'L U L'U'L U L'U'L U L'U'L U ");
            seventhStepCounter += 28;
            rotatesCounter += 28;
            count = 0;
            continue;
        }
        if (rightAnglesCorrect && rightCenterCorrect) {
            rotatePlanes("B U B'U'F'U'F U B U B'U'B U B'U'B U B'U'B U B'U'B U B'U'F'U'F U F'U'F U F'U'F U F'U'F U F'U'F U ");
            seventhStepCounter += 28;
            rotatesCounter += 28;
            count = 0;
            continue;
        }
        if (backAnglesCorrect && backCenterCorrect) {
            rotatePlanes("L U L'U'R'U'R U L U L'U'L U L'U'L U L'U'L U L'U'L U L'U'R'U'R U R'U'R U R'U'R U R'U'R U R'U'R U ");
            seventhStepCounter += 28;
            rotatesCounter += 28;
            count = 0;
            continue;
        }
        if (leftAnglesCorrect && leftCenterCorrect) {
            rotatePlanes("F U F'U'B'U'B U F U F'U'F U F'U'F U F'U'F U F'U'F U F'U'B'U'B U B'U'B U B'U'B U B'U'B U B'U'B U ");
            seventhStepCounter += 28;
            rotatesCounter += 28;
            count = 0;
            continue;
        }
        if (frontAnglesCorrect) {
            rotatePlanes("R U R'U'L'U'L U R U R'U'R U R'U'R U R'U'R U R'U'R U R'U'L'U'L U L'U'L U L'U'L U L'U'L U L'U'L U ");
            seventhStepCounter += 28;
            rotatesCounter += 28;
            count = 0;
            continue;
        }
        if (rightAnglesCorrect) {
            rotatePlanes("B U B'U'F'U'F U B U B'U'B U B'U'B U B'U'B U B'U'B U B'U'F'U'F U F'U'F U F'U'F U F'U'F U F'U'F U ");
            seventhStepCounter += 28;
            rotatesCounter += 28;
            count = 0;
            continue;
        }
        if (backAnglesCorrect) {
            rotatePlanes("L U L'U'R'U'R U L U L'U'L U L'U'L U L'U'L U L'U'L U L'U'R'U'R U R'U'R U R'U'R U R'U'R U R'U'R U ");
            seventhStepCounter += 28;
            rotatesCounter += 28;
            count = 0;
            continue;
        }
        if (leftAnglesCorrect) {
            rotatePlanes("F U F'U'B'U'B U F U F'U'F U F'U'F U F'U'F U F'U'F U F'U'B'U'B U B'U'B U B'U'B U B'U'B U B'U'B U ");
            seventhStepCounter += 28;
            rotatesCounter += 28;
            count = 0;
            continue;
        }
        if (count < 4 && !isSeventhStepCompleted()) {
            count++;
            rotatePlanes("U ");
            seventhStepCounter++;
            rotatesCounter++;
        } else if (count == 4 && !isSeventhStepCompleted()) {
            shuffle(3);
            firstStep();
            secondStep();
            thirdStep();
            fourthStep();
            fifthStep();
            sixthStep();
            count = 0;
        }
    }
    if (i > 127) {
        throw logic_error("\n\nError occurred while solving seventh step\n\n");
    }
}

//Make numerous rotations
void CubeRubik::rotatePlanes(string rotations) {
    //Checking what plane should we rotate and in arguments we pass how we should rotate it(clockwise or not)
    for (int i = 0; i < rotations.size(); i += 2) {
        if (rotations[i] == 'U') {
            rotateUpPlane(rotations[i + 1] != '\'');
        } else if (rotations[i] == 'D') {
            rotateDownPlane(rotations[i + 1] != '\'');
        } else if (rotations[i] == 'L') {
            rotateLeftPlane(rotations[i + 1] != '\'');
        } else if (rotations[i] == 'R') {
            rotateRightPlane(rotations[i + 1] != '\'');
        } else if (rotations[i] == 'F') {
            rotateFrontPlane(rotations[i + 1] != '\'');
        } else if (rotations[i] == 'B') {
            rotateBackPlane(rotations[i + 1] != '\'');
        }
    }
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
        cout << "U ";
        rotateUpPlaneClock(tempUp00, tempUp01, tempFront00, tempFront01, tempFront02);
    } else {
        cout << "U' ";
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
        cout << "D ";
        rotateDownPlaneClock(tempDown00, tempDown01, tempFront20, tempFront21, tempFront22);
    } else {
        cout << "D' ";
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
        cout << "L ";
        rotateLeftPlaneClock(tempLeft00, tempLeft01, tempFront00, tempFront10, tempFront20);
    } else {
        cout << "L' ";
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
        cout << "R ";
        rotateRightPlaneClock(tempRight00, tempRight01, tempFront02, tempFront12, tempFront22);
    } else {
        cout << "R' ";
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
        cout << "F ";
        rotateFrontPlaneClock(tempFront00, tempFront01, tempUp20, tempUp21, tempUp22);
    } else {
        cout << "F' ";
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
        cout << "B ";
        rotateBackPlaneClock(tempBack00, tempBack01, tempUp00, tempUp01, tempUp02);
    } else {
        cout << "B' ";
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

//Visualisation of Rubik's Cube
void CubeRubik::generateVisualCube(GLfloat size, unsigned int *color) {
    memset(rotateAngle, 0, sizeof(rotateAngle));
    this->sizeCube = size;
    currentPlane = -1;
    //Up plane
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            visualColors[i][j][2].setColor(0, color[0]);
        }
    }
    //Down plane
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            visualColors[i][j][0].setColor(1, color[1]);
        }
    }
    //Front plane
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            visualColors[i][2][k].setColor(2, color[2]);
        }
    }
    //Back plane
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            visualColors[i][0][k].setColor(3, color[3]);
        }
    }
    //Left plane
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            visualColors[2][j][k].setColor(4, color[4]);
        }
    }
    //Right plane
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            visualColors[0][j][k].setColor(5, color[5]);
        }
    }
    //Setting size for all the pieces in visual colors
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                visualColors[i][j][k].setEdge(size / 3 * 0.95);
            }
        }
    }
}

void CubeRubik::display() {
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glTranslatef(0, 0, translateZ);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glTranslatef(CUBE_SIZE / -2, CUBE_SIZE / -2, CUBE_SIZE / -2);
    draw();
    glPopMatrix();
    glutSwapBuffers();
}

void CubeRubik::visualRotate(int plane, int degree) {
    if (degree == -1) degree = 3;
    for (int i = 0; i < degree; i++) {
        switch (plane) {
            case 0:
                visualRotateFront();
                break;
            case 1:
                visualRotateBack();
                break;
            case 2:
                visualRotateDown();
                break;
            case 3:
                visualRotateUp();
                break;
            case 4:
                visualRotateRight();
                break;
            case 5:
                visualRotateLeft();
                break;
            default:
                break;
        }
    }
}

void CubeRubik::visualRotateUp() {
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            temp[k][2 - i] = visualColors[i][2][k];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            temp[i][k].rotateDownUp();
            visualColors[i][2][k] = temp[i][k];
        }
    }
}

void CubeRubik::visualRotateDown() {
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            temp[k][2 - i] = visualColors[i][0][k];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            temp[i][k].rotateDownUp();
            visualColors[i][0][k] = temp[i][k];
        }
    }
}

void CubeRubik::visualRotateFront() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[j][2 - i] = visualColors[i][j][0];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j].rotateBackFront();
            visualColors[i][j][0] = temp[i][j];
        }
    }
}

void CubeRubik::visualRotateBack() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[j][2 - i] = visualColors[i][j][2];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j].rotateBackFront();
            visualColors[i][j][2] = temp[i][j];
        }
    }
}

void CubeRubik::visualRotateLeft() {
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            temp[k][2 - j] = visualColors[2][j][k];
        }
    }
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            temp[j][k].rotateLeftRight();
            visualColors[2][j][k] = temp[j][k];
        }
    }
}

void CubeRubik::visualRotateRight() {
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            temp[k][2 - j] = visualColors[0][j][k];
        }
    }
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            temp[j][k].rotateLeftRight();
            visualColors[0][j][k] = temp[j][k];
        }
    }
}

void CubeRubik::timer(int degree, int) {
    if (currentPlane == -1)
        return;

    display();
    visualRotatePlanes(currentPlane, ROTATE_SPEED_STEP, degree);
}

void CubeRubik::visualRotatePlanes(int plane, int angle, int degree) {
    if (currentPlane == -1 || currentPlane == plane) {
        if (degree == -1)
            rotateAngle[plane] -= angle;
        else if (degree == 1)
            rotateAngle[plane] += angle;

        if (rotateAngle[plane] % 90 != 0) {
            currentPlane = plane;
            timer(degree, 0);
        } else {
            if ((rotateAngle[plane] < 0) ^ (currentPlane == 2 || currentPlane == 3))
                visualRotate(plane, 1);
            else
                visualRotate(plane, -1);

            rotateAngle[plane] = 0;
            currentPlane = -1;
        }
    }
}

void CubeRubik::draw() {
    const GLfloat K = 0.25;
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(((1 - K) / 2) * sizeCube + K * sizeCube / 2, ((1 - K) / 2) * sizeCube + K * sizeCube / 2, ((1 - K) / 2) * sizeCube + K * sizeCube / 2);
    glutSolidCube(sizeCube * K);
    glPopMatrix();

    memset(usedVisualCube, true, sizeof(usedVisualCube));
    if (currentPlane != -1) {
        glPushMatrix();

        if (currentPlane == 0 || currentPlane == 1) {
            int k = (currentPlane & 1) * 2;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    usedVisualCube[i][j][k] = false;

            glTranslated(sizeCube / 2, sizeCube / 2, 0);   // translation to center
            glRotatef(rotateAngle[currentPlane], 0, 0, 1);   // rotate
            glTranslated(-sizeCube / 2, -sizeCube / 2, 0); // translation to start position

            // drawing
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    visualColors[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k);

        } else if (currentPlane == 2 || currentPlane == 3) {
            int j = (currentPlane & 1) * 2;
            for (int i = 0; i < 3; ++i)
                for (int k = 0; k < 3; ++k)
                    usedVisualCube[i][j][k] = false;

            glTranslated(sizeCube / 2, 0, sizeCube / 2);
            glRotatef(rotateAngle[currentPlane], 0, 1, 0);
            glTranslated(-sizeCube / 2, 0, -sizeCube / 2);
            for (int i = 0; i < 3; ++i)
                for (int k = 0; k < 3; ++k)
                    visualColors[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k);

        } else if (currentPlane == 4 || currentPlane == 5) {
            int i = (currentPlane & 1) * 2;
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    usedVisualCube[i][j][k] = false;

            glTranslated(0, sizeCube / 2, sizeCube / 2);
            glRotatef(rotateAngle[currentPlane], 1, 0, 0);
            glTranslated(0, -sizeCube / 2, -sizeCube / 2);
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    visualColors[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k);
        }
        glPopMatrix();
    }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                if (usedVisualCube[i][j][k])
                    visualColors[i][j][k].draw(sizeCube / 3 * i, sizeCube / 3 * j, sizeCube / 3 * k);
}
#endif //RUBIKCUBE_CUBERUBIK_CPP

