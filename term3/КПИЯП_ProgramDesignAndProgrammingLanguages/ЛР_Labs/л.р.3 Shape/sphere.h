#pragma once
#include "ThreeDShape_Class.h"

class Sphere:public ThreeDshape{
private:
    double radius;
public:
    Sphere(string color, double radius) :ThreeDshape(color){
        cout << "Constructor Sphere" << endl << endl;
        this->radius = radius;
    }
    void Volume() override;
    void Show() override;
    void Area() override;
    void Perimetr() override { };
    ~Sphere() { 
        cout << "Destructor Sphere" << endl;
    };
};