#ifndef CLION_PROGRAMMING_CUBEPIECE_H
#define CLION_PROGRAMMING_CUBEPIECE_H
#include <iostream>
#include <utility>
using std::string;


class CubePiece {
private:
    //If user don't see any of planes it will be black
    string up = "black";
    string down = "black";
    string left = "black";
    string right = "black";
    string front = "black";
    string back = "black";
public:
    //Constructors
    CubePiece() = default;

    explicit CubePiece (string up_, string down_, string left_, string right_, string front_, string back_);

    //Getters

    string getUpColor();

    string getDownColor();

    string getLeftColor();

    string getRightColor();

    string getFrontColor();

    string getBackColor();

    //Setters

    void setUpColor(string color);

    void setDownColor(string color);

    void setLeftColor(string color);

    void setRightColor(string color);

    void setFrontColor(string color);

    void setBackColor(string color);
};


#endif //CLION_PROGRAMMING_CUBEPIECE_H
