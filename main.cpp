#include <iostream>
#include "Rubik/CubeRubik/CubeRubik.h"

int main() {
    CubeRubik cubeRubik;
    cubeRubik.printRubikCube();
    cubeRubik.shuffle();
    cubeRubik.printRubikCube();
    return 0;
}
