#include "Rubik/CubeRubik/CubeRubik.h"
#include "Other/Menu.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(480, 800);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("Rubik's Cube");
    createMenu();
    return 0;
}