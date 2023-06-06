cmake_minimum_required(VERSION 3.25)
project(RubikCube)

set(CMAKE_CXX_STANDARD 23)


add_executable(RubikCube main.cpp Rubik/CubePiece/CubePiece.cpp Rubik/CubePiece/CubePiece.h Rubik/CubeRubik.h Rubik/RubikConfig.h Rubik/CubeVisual.h Other/HelpingFunctions.h Other/Menu.h Rubik/VisualFunctions.h)
find_package(OpenGL REQUIRED)

target_include_directories(RubikCube PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(RubikCube PUBLIC ${OPENGL_LIBRARIES})

find_package(GLUT REQUIRED)

target_include_directories(RubikCube PUBLIC ${GLUT_INCLUDE_DIR})
target_link_libraries(RubikCube PUBLIC ${GLUT_LIBRARIES})
