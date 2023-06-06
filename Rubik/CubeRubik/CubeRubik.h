#ifndef RUBIKCUBE_CUBERUBIK_H
#define RUBIKCUBE_CUBERUBIK_H

#include <iostream>
#include <vector>

#include "../CubePiece/CubePiece.h"
#include "../CubeVisual/CubeVisual.h"
#include "../../Other/HelpingFunctions.h"
using std::vector, std::istream, std::cin, std::cout, std::ostream;

#define Plane vector<vector<CubePiece*>>
#define UpCenter UpPlane[1][1]->getUpColor()
#define DownCenter DownPlane[1][1]->getDownColor()
#define LeftCenter LeftPlane[1][1]->getLeftColor()
#define RightCenter RightPlane[1][1]->getRightColor()
#define FrontCenter FrontPlane[1][1]->getFrontColor()
#define BackCenter BackPlane[1][1]->getBackColor()

class CubeRubik {
private:

    friend void specialKeys(int, int, int);
    friend void display();
    friend void init();
    friend void processMenu(int);

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
    int rotatesCounter = 0;
    int firstStepCounter = 0;
    int secondStepCounter = 0;
    int thirdStepCounter = 0;
    int fourthStepCounter = 0;
    int fifthStepCounter = 0;
    int sixthStepCounter = 0;
    int seventhStepCounter = 0;

    //3D visualization of Rubik's Cube
    bool usedVisualCube[3][3][3];
    //3 planes in each we have matrix 3 by 3
    CubeVisual visualColors[3][3][3];
    //temp used for rotating planes
    CubeVisual temp[3][3];
    //Rotate angle for each plane
    int rotateAngle[6];
    //Rubik's cube size in window
    GLfloat sizeCube;
    //Current plane for rotation
    int currentPlane;

public:
    //Constructor

    explicit CubeRubik();

    //Getters of Info

    void getInfoOfSolvation() const;

    int getCurrentPlane();

    //Implementation of the main function: generating, shuffling, solving etc.

    //Generating right(solved) RubikCube
    void generateRubikCube();

    //Reading RubikCube from console or file
    void readRubikCube(istream &inStream = cin);

    //Printing RubikCube in console or file
    void printRubikCube(ostream &outStream = cout) const ;

    //Shuffling Rubik's Cube
    void shuffle(int rotations = 30);

    //Checking if Rubik;s Cube is already solved
    bool isSolved();

    //Solving Rubik's Cube
    void solveCubeRubik();

    //Functions for fun
    void rightSolver();

    void leftSolver();

//Rotate planes but visually
void visualRotatePlanes(int plane, int angle, int degree);

private:

    //Filling empty plane vectors
    void fillPlane(Plane &plane);

    void initPlanes();

    //Checking if cube is correct
    [[nodiscard]] bool checkCubeIsCorrect() const;

    //Helping function for checking is Cube correct
    void increaseColor(unsigned char& yellow, unsigned char& white, unsigned char& orange, unsigned char& red,
                       unsigned char& blue, unsigned char& green, const string& color) const;

    //Checking if steps are completed
    //Checking if first step completed
    [[nodiscard]] bool isFirstStepCompleted();

    //Checking if second step completed
    [[nodiscard]] bool isSecondStepCompleted();

    //Checking if third step completed
    [[nodiscard]] bool isThirdStepCompleted();

    //Checking if fourth step completed
    [[nodiscard]] bool isFourthStepCompleted();

    //Checking if fifth step completed
    [[nodiscard]] bool isFifthStepCompleted();

    //Checking if sixth step completed
    [[nodiscard]] bool isSixthStepCompleted();

    //Checking if seventh step completed
    [[nodiscard]] bool isSeventhStepCompleted();

    //First step of solving Rubik's Cube
    void firstStep();

    //Second step of solving Rubik's Cube
    void secondStep();

    //Third step of solving Rubik's Cube
    void thirdStep();

    //Fourth step of solving Rubik's Cube
    void fourthStep();

    //Fifth step of solving Rubik's Cube
    void fifthStep();

    //Sixth step of solving Rubik's Cube
    void sixthStep();

    //Seventh step of solving Rubik's Cube
    void seventhStep();

    //Make numerous rotations
    void rotatePlanes(string rotations);

    //Rotations of planes
public:
    //Rotation of the up plane, public because of key access
    void rotateUpPlane(bool clockwise);
private:
    //Rotation of the up plane clockwise
    void rotateUpPlaneClock(string& up00, string& up01, string& front00, string& front01, string& front02);

    //Rotation of the up plane not clockwise
    void rotateUpPlaneNotClock(string& up00, string& up01, string& front00, string& front01, string& front02);

public:
    //Rotation of the down plane
    void rotateDownPlane(bool clockwise);
private:
    //Rotation of the down plane clockwise
    void rotateDownPlaneClock(string& down00, string& down01, string& front20, string& front21, string& front22);

    //Rotation of the down plane not clockwise
    void rotateDownPlaneNotClock(string& down00, string& down01, string& front20, string& front21, string& front22);

public:
    //Rotation of the left plane
    void rotateLeftPlane(bool clockwise);
private:
    //Rotation of the left plane clockwise
    void rotateLeftPlaneClock(string& left00, string& left01, string& front00, string& front10, string& front20);

    //Rotation of the left plane not clockwise
    void rotateLeftPlaneNotClock(string& left00, string& left01, string& front00, string& front10, string& front20);

public:
    //Rotation of the right plane
    void rotateRightPlane(bool clockwise);
private:
    //Rotation of the right plane clockwise
    void rotateRightPlaneClock(string& right00, string& right01, string& front02, string& front12, string& front22);

    //Rotation of the right plane not clockwise
    void rotateRightPlaneNotClock(string& right00, string& right01, string& front02, string& front12, string& front22);

public:
    //Rotation of the front plane
    void rotateFrontPlane(bool clockwise);
private:
    //Rotation of the front plane clockwise
    void rotateFrontPlaneClock(string& front00, string& front01, string& up20, string& up21, string& up22);

    //Rotation of the front plane not clockwise
    void rotateFrontPlaneNotClock(string& front00, string& front01, string& up20, string& up21, string& up22);

public:
    //Rotation of the back plane
    void rotateBackPlane(bool clockwise);
private:
    //Rotation of the back plane clockwise
    void rotateBackPlaneClock(string& back00, string& back01, string& up00, string& up01, string& up02);

    //Rotation of the back plane not clockwise
    void rotateBackPlaneNotClock(string& back00, string& back01, string& up00, string& up01, string& up02);

    //Visualisation of Rubik's Cube
    void generateVisualCube(GLfloat size, unsigned int* colors);

    //Function for right displaying Rubik's Cube in window
    void display();

    //Rotate plane for angle
    void visualRotate(int plane, int angle);

    //Functions for rotating each plane
    void visualRotateUp();

    void visualRotateDown();

    void visualRotateFront();

    void visualRotateBack();

    void visualRotateLeft();

    void visualRotateRight();

public:
    void visualRotatePlanes();

private:
    //Function for smooth rotation of Rubik's Cube
    void timer(int degree, int);

    //Drawing Rubik's Cube visually
    void draw();
};

static CubeRubik Cube;

#endif //RUBIKCUBE_CUBERUBIK_H
