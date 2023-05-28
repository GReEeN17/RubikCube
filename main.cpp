#include <iostream>
#include "Rubik/CubeRubik/CubeRubik.h"

int main() {
    CubeRubik cubeRubik;
    cubeRubik.printRubikCube();
    cubeRubik.shuffle();
    cubeRubik.printRubikCube();
    cubeRubik.solveCubeRubik();
    cubeRubik.printRubikCube();
    cubeRubik.getInfoOfSolvation();
    return 0;
}
