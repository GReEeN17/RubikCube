#include <iostream>
#include "Rubik/CubeRubik/CubeRubik.h"

int main() {
    CubeRubik cubeRubik;
    cubeRubik.printRubikCube();
    cubeRubik.shuffle();
    cubeRubik.printRubikCube();
    cubeRubik.firstStep();
    cubeRubik.printRubikCube();
    cubeRubik.secondStep();
    cubeRubik.printRubikCube();
    return 0;
}
