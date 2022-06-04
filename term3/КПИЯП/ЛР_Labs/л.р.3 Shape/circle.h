#pragma once
#include "TwoDShape_Class.h"

class Circle : public TwoDshape{
private:
    double radius;
public:
    Circle(string color, double radius) : TwoDshape(color){
        cout << "Constructor Circle" << endl << endl;
        this->radius = radius;
    }
    void Area() override;
    void Show() override;
    void Volume() override { };
    void Perimetr() override;
    ~Circle(){
        cout << "Destructor Circle" << endl;
    };
};