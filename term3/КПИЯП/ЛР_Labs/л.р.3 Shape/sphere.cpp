#include "sphere.h"
#include <math.h>

void Sphere::Volume(){
    cout << "Volume is  " << 4 / 3 * (3.14 * pow(radius, 3)) << endl;
}

void Sphere::Area() {
    cout << "Area is  " << 4 * (3.14 * pow(radius, 2)) << endl;
}

void Sphere::Show(){
    cout << "_Sphere__" << color << endl;
    cout << "Radius is  " << radius << endl;
    Volume();
    Area();
    cout << endl;
}
