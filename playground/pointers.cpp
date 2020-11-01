#include <iostream>
#include <vector>

using std::vector;
using std::cout;


void PointerTest(int *a) {
    cout << "This is the memory address of pointer: " << a << std::endl;
    cout << "This is the int value of pointer: " << *a << std::endl;
    // accessing the value inside the memory location held by variable a
    *a = 6; 
}

int main() {
    int num = 2;
    int * ptr_to_num = &num; //accessing memory address with the amp
    cout << "Memory reference of num: " << &num << std::endl;
    PointerTest(ptr_to_num);
    cout << "The value of num now is: " << num << std::endl;
}