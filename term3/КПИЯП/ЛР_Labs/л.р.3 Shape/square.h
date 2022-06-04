#pragma once
#include "TwoDShape_Class.h"

class Square : public TwoDshape{
private:
    double side;
public:
    Square(string color, double side) : TwoDshape(color){
        cout << "Constructor Square" << endl << endl;
        this->side = side;
    }
    void Area() override;
    void Show() override;
    void Volume() override { };
    void Perimetr() override;
    ~Square() { 
        cout << "Destructor Square" << endl;
    };
};