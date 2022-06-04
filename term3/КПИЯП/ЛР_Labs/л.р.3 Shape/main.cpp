#include "Shape_Class.h"
#include "circle.h"
#include "sphere.h"
#include "square.h"
#include "parallelepiped.h"

int main(){
	Shape* arrayShapes[4];
	Circle crcl("color1 - green", 5);
	arrayShapes[0] = &crcl;
	arrayShapes[0]->Show();
	Sphere sphr("color2 - red", 5);
	arrayShapes[1] = &sphr;
	arrayShapes[1]->Show();
	Square sqr("color3 - pink", 12);
	arrayShapes[2] = &sqr;
	arrayShapes[2]->Show();
	Parallelepiped prl("color4 - blue", 5, 3, 5);
	arrayShapes[3] = &prl;
	arrayShapes[3]->Show();
	return 0;
}