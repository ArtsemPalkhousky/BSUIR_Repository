#include "TwoDShape_Class.h"

TwoDshape::TwoDshape(string color){
	cout << "Constructor 2D" << endl;
	this->color = color;
}
TwoDshape::~TwoDshape(){
	cout << "Destructor 2D" << endl;
}