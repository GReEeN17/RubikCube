#include <iostream>
#include "Rubik/CubeRubik/CubeRubik.h"

int main() {
    CubeRubik cubeRubik;
    cubeRubik.printRubikCube();
    cubeRubik.rotateRightPlane(true);
    cubeRubik.printRubikCube();
    cubeRubik.rotateUpPlane(true);
    cubeRubik.printRubikCube();
    cubeRubik.rotateRightPlane(false);
    cubeRubik.printRubikCube();
    cubeRubik.rotateUpPlane(false);
    cubeRubik.printRubikCube();
    return 0;
}
