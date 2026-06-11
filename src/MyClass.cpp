// #include <iostream>
#include "MyClass.h" // Подключаем объявление класса

// Конструктор
MyClass::MyClass(int val) {
    data = val;
}

// Метод
void MyClass::printData() {
    // std::cout << "Data: " << data << std::endl;
    // return MyClass.data;
}

int MyClass::multi2() {
    return data * 2;
}