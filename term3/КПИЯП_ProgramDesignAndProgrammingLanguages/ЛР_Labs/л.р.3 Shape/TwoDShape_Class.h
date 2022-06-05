#pragma once
#include "Shape_Class.h"

class TwoDshape: public Shape{
protected:
    string color;
public:
    TwoDshape(string color);
    ~TwoDshape();
};
