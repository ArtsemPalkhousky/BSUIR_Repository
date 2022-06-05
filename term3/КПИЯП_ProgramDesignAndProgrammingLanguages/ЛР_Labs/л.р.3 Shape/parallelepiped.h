#pragma once
#include "ThreeDShape_Class.h"

class Parallelepiped : public ThreeDshape{
private:
    int sideA, sideB, hight;
public:
    Parallelepiped(string color, int sideA, int sideB, int hight): ThreeDshape(color){
        cout << "Constructor Parallelepiped" << endl << endl;
        this->sideA = sideA;
        this->sideB = sideB;
        this->hight = hight;
    }
    void Volume() override;
    void Area() override;
    void Show() override;
    void Perimetr() override { };
    ~Parallelepiped() {
        cout << "Destructor Parallelepiped" << endl;
    };
};