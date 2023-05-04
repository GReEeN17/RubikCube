#include "CubePiece.h"
#include <iostream>
using std::string;

//Constructor

CubePiece::CubePiece(string up_, string down_, string left_, string right_, string front_, string back_)  {
    this->up = std::move(up_);
    this->down = std::move(down_);
    this->left = std::move(left_);
    this->right = std::move(right_);
    this->front = std::move(front_);
    this->back = std::move(back_);
}

//Getters

string CubePiece::getUpColor() {return up;}

string CubePiece::getDownColor() {return down;}

string CubePiece::getLeftColor() {return left;}

string CubePiece::getRightColor() {return right;}

string CubePiece::getFrontColor() {return front;}

string CubePiece::getBackColor() {return back;}

//Setters

void CubePiece::setUpColor(std::string color) {this->up = std::move(color);}

void CubePiece::setDownColor(std::string color) {this->down = std::move(color);}

void CubePiece::setLeftColor(std::string color) {this->left = std::move(color);}

void CubePiece::setRightColor(std::string color) {this->right = std::move(color);}

void CubePiece::setFrontColor(std::string color) {this->front = std::move(color);}

void CubePiece::setBackColor(std::string color) {this->back = std::move(color);}
