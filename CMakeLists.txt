cmake_minimum_required(VERSION 3.25)
project(RubikCube)

set(CMAKE_CXX_STANDARD 23)

add_executable(RubikCube main.cpp CubePiece/CubePiece.cpp CubePiece/CubePiece.h)
