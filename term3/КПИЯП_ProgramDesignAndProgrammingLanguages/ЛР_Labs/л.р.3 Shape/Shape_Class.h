#pragma once
#include <iostream>
#include <string>
using namespace std;

class Shape{
public:
	Shape(){
		cout << "---------Constructor shape---------" << endl;
	}
	~Shape(){
		cout << "--Destructor shape" << endl;
	}
	virtual void Show() = 0;
	virtual void Volume() = 0;
	virtual void Area() = 0;
	virtual void Perimetr() = 0;
};
