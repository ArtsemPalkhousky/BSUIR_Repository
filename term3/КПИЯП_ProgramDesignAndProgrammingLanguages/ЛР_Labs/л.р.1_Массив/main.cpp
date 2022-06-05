#include "Header.h"

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Размер 1-ого массива: " << endl;
    int n;
    cin >> n;
    Array arr1(n);
    cout << "Размер 2-ого массива: " << endl;
    cin >> n;
    Array arr2(n);
    cout << "Введите элементы 1-ого массива: " << endl;
    arr1.add();
    cout << "Введите элементы 2-ого массива: " << endl;
    arr2.add();
    system("CLS");
    cout << "Исходные массивы: " << endl;
    arr1.show();
    arr2.show();
    Array MyArray;
    MyArray = arr1.unification(arr2);
    cout << "Результат объединения:" << endl;
    MyArray.show();
    return 0;
}