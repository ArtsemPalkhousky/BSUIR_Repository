#include "square.h"
#include <math.h>

void Square::Area(){
	cout << "Area is  " << pow(side, 2) << endl;
}
void Square::Perimetr() {
	cout << "Perimetr is  " << side * 4 << endl;
}

void Square::Show(){
	cout << "__Square__ " << color << endl;
	cout << "Side is  " << side << endl;
	Area();
	Perimetr();
	cout << endl;
}