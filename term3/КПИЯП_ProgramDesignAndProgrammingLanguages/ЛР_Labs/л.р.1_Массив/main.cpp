#include "Header.h"

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "������ 1-��� �������: " << endl;
    int n;
    cin >> n;
    Array arr1(n);
    cout << "������ 2-��� �������: " << endl;
    cin >> n;
    Array arr2(n);
    cout << "������� �������� 1-��� �������: " << endl;
    arr1.add();
    cout << "������� �������� 2-��� �������: " << endl;
    arr2.add();
    system("CLS");
    cout << "�������� �������: " << endl;
    arr1.show();
    arr2.show();
    Array MyArray;
    MyArray = arr1.unification(arr2);
    cout << "��������� �����������:" << endl;
    MyArray.show();
    return 0;
}