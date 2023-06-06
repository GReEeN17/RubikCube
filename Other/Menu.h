#ifndef RUBIKCUBE_MENU_H
#define RUBIKCUBE_MENU_H
#include <iostream>

void processMenu(int action) {
    try {
        switch (action) {
            case 1:
                Cube.readRubikCube(inputStream);
                break;
            case 2:
                cout << "\nCube's unfolding:\n\n";
                Cube.printRubikCube();
                break;
            case 3:
                outputStream << "\nCube's unfolding:\n\n";
                Cube.printRubikCube(outputStream);
                break;
            case 4:
                Cube.shuffle();
                cout << "\n\nCube's unfolding after shuffling:\n\n";
                Cube.printRubikCube();
                break;
            case 5:
                Cube.solveCubeRubik();
                outputStream << "\n\nCube's unfolding after solving:\n\n";
                Cube.printRubikCube(outputStream);
                break;
            case 6:
                Cube.getInfoOfSolvation();
                break;
            case 7:
                Cube.leftSolver();
                break;
            case 8:
                Cube.rightSolver();
                break;
            case 9:
                Cube.generateRubikCube();
                Cube.generateVisualCube(CUBE_SIZE, colors);
                break;
            default:
                break;
        }

    } catch (exception &e) {
        cout << e.what();
    }
}

void createMenu() {
    glutCreateMenu(processMenu);

    glutAddMenuEntry("Read Cube from file", 1);
    glutAddMenuEntry("Print Cube in console", 2);
    glutAddMenuEntry("Print Cube in file", 3);
    glutAddMenuEntry("Shuffle", 4);
    glutAddMenuEntry("Find Solution", 5);
    glutAddMenuEntry("Print solving information in console", 6);
    glutAddMenuEntry("Solve Cube using only left and up rotates", 7);
    glutAddMenuEntry("Solve Cube using only right and up rotates", 8);
    glutAddMenuEntry("Create solved Cube", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

#endif //RUBIKCUBE_MENU_H
