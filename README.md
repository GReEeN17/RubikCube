# Rubik's Cube solvation and visualization using `OpenGL` and `GLUT` frameworks
### OS: `macOS`
### Language `C++`
* Project requires **OpenGl** and **GLUT** frameworks
* Average amount of time to solve Rubik's Cube is `20` seconds (with 5 millis delay)
* Average amount of rotations to solve Rubik's Cube is about `300`
### Information about functions of this project
* Using **cursor control buttons** you can rotate Rubik's Cube in all three planes (x, y, z)
  ![Rotating Rubik's Cube](https://github.com/GReEeN17/RubikCube/assets/70602093/f6e861be-5a33-4171-a4a3-e118488e1cd4)
* Using **"1", "2", "3", "4", "5", "6"** buttons you can rotate up, left, front, right, back and down planes respectivly clockwise
   ![Shuffling Rubik's Cube](https://github.com/GReEeN17/RubikCube/assets/70602093/d27b3758-3a4e-4ec6-9ca8-871dc8dab168)
### By using right button you can see menu, by which you can: 
* **Print** your Rubik's Cube layout in console or file
  <div><img width="500" alt="Снимок экрана 2023-06-10 в 00 43 41" src="https://github.com/GReEeN17/RubikCube/assets/70602093/091ab94e-9b1d-4a1e-91d4-192fa9306509"></div>
* **Make 3D visual model** of Rubik's Cube from input file (it is important to maintain a clear sequence of entering planes, or rather up->down->front->back->left->right)
  <div><img width="479" alt="Снимок экрана 2023-06-10 в 21 26 47" src="https://github.com/GReEeN17/RubikCube/assets/70602093/e5dc0130-9762-4120-9af0-5811d3c612ed"></div>
* **Shuffle** Rubik's Cube by only one click
  ![ShufflingOneClick](https://github.com/GReEeN17/RubikCube/assets/70602093/352ac991-fc0c-4d9c-ae26-a8f5a673b893)
* **Solve** Rubik's Cube by only one click
  ![Solving Rubik's Cube](https://github.com/GReEeN17/RubikCube/assets/70602093/5564dd9c-225c-435f-8509-c6656a921af8)
### Information about files
Name of the file             | file content
-----------------------------|-------------
main.cpp                     |main file, in which there is GLUT loop (infinite loop)
input.txt                    |file with Rubik's Cube layout to read
output.txt                   |file in which you can write your visualized Rubik's Cube
CMakeLists.txt               |all files, which project needs to build and all frmeworks to include
Other/HelpingFunctions.h     |file in which there are functions to solve Rubik's Cube (or rather getRGBRubik function)
Other/Menu.h                 |file with content for menu
Rubik/CubePiece/CubePiece.h  |header file, which represents one of 26 "mini" cubes of Rubik's Cube
Rubik/CubePiece/CubePiece.cpp|cpp file, which implements functions of header file
Rubik/CubeVisual.h           |file, which represents one of 26 "mini" cubes, but for its' visualization
Rubik/VisualFunctions.h      |file for visualization Rubik's Cube, it implements interaction with buttons and sets timer for GLUT functions
Rubik/RubikConfig.h          |file with configuration of input/output files, visual content etc.
Rubik/CubeRubik.h            |file with all Rubik's Cube functions: shuffling, rotating, reading, writing, visualizating etc.
  




