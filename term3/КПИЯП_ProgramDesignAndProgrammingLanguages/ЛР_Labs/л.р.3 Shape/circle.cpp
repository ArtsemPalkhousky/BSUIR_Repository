#include "circle.h"

void Circle::Area(){
	cout << "Area is  " << 3.141592 * pow(radius, 2) << endl;
}

void Circle::Perimetr() {
	cout << "Perimetr is  " << 3.141592 * 2 * radius << endl;
}

void Circle::Show() {
	cout << "__Circle__ " << color << endl;
	cout << "Radius is  " << radius << endl;
	Area();
	Perimetr();
	cout << endl;
}