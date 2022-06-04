#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Array {
private:
    int* array;
    int size;
public:
    explicit Array(int a);
    Array();
    Array(int n, const int* arr);           //конструктор копирования
    Array(const Array& other);
    ~Array();
    Array& operator= (const Array& obj);
    void add();
    void show();
    Array unification(Array& obj2);
};