#include "parallelepiped.h"
#include <math.h>

void Parallelepiped::Volume(){
    cout << "Volume is  " << (sideA * sideB * hight)/2 << endl;
}

void Parallelepiped::Area() {
    cout << "Area is  " << (sideA * sideB) + (hight * sideA) + (hight * sideB) << endl;
}

void Parallelepiped::Show(){
    cout << "__Parallelepiped__ " << color << endl;
    cout << "A,B,h are  " << sideA << ", " << sideB << ", "
        << hight << endl;
    Volume();
    Area();
    cout << endl;
}