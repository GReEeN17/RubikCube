#include "Rubik/CubeRubik.h"
#include "Rubik/VisualFunctions.h"
#include "Other/Menu.h"

extern CubeRubik Cube;

int main(int argc, char *argv[]) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(480, 800);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("Rubik's Cube");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(5, timer, 0);
    glutSpecialFunc(specialKeys);
    createMenu();
    glutMainLoop();

    return 0;
}