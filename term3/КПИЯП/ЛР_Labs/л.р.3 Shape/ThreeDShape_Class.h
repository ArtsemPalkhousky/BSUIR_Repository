#pragma once
#include "Shape_Class.h"

class ThreeDshape : public Shape{
protected:
    string color;
public:
    ThreeDshape(string color);
    virtual ~ThreeDshape();
};