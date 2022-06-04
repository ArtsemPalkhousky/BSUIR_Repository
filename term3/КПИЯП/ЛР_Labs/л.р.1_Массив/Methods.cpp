#include "Header.h"

Array::Array(int a){
    size = a;
    array = new int[size];
}

Array::Array(){
    size = 0;
    array = nullptr;
}

Array::Array(const Array& arr){
    this->size = arr.size;
    this->array = new int[this->size];
    for (int i = 0; i < this->size; i++)
        this->array[i] = arr.array[i];
}

Array::Array(int n, const int* arr){
    size = n;
    array = new int[size];
    for (int i = 0; i < size; ++i)
        array[i] = arr[i];
}

Array::~Array(){
    delete[] array;
}

Array& Array::operator=(const Array& obj){
    if (this == &obj)
        return *this;
    delete[] array;
    size = obj.size;
    array = new int[size];
    for (int i = 0; i < size; i++) array[i] = obj.array[i];
    return *this;
}

void Array::add(){
    for (int i = 0; i < size; i++)
        cin >> array[i];
}

void Array::show(){
    for (int i = 0; i < size; ++i)
        cout << setw(4) << array[i]; 
    cout << endl;
}

class Array  Array::unification(class Array& SecondArray){
    Array ResultArray(size + SecondArray.size);
    int fl = 0;
    int dinamSize = size;
    for (int i = 0; i < size; ++i) 
        ResultArray.array[i] = array[i];
    for (int i = 0; i < SecondArray.size; i++){
        for (int j = 0; j < size; ++j){
            fl = 0;
            if (array[j] == SecondArray.array[i]){
                fl = 1;
                break;
            }
        }
        if (fl == 0){
            ResultArray.array[dinamSize] = SecondArray.array[i];
            dinamSize++;
        }
    }
    ResultArray.size = dinamSize;
    return ResultArray;
}