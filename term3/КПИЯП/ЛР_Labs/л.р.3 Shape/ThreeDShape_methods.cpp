#include "ThreeDShape_Class.h"

ThreeDshape ::ThreeDshape(string color){
	cout << "Constructor 3D" << endl;
	this->color = color;
}
ThreeDshape::~ThreeDshape(){
	cout << "Destructor 3D" << endl;
}