#include <iostream>
#include <vector>

using std::cout;
using std::vector;

void PointerTest(int *a)
{
    cout << "This is the memory address of pointer: " << a << std::endl;
    cout << "This is the int value of pointer: " << *a << std::endl;
    // accessing the value inside the memory location held by variable a
    *a = 6;
}

void VectorPointerTest(vector<int> *v)
{
    cout << "This is the memory address: "<< v << std::endl;
    cout << "Printing out contents of vector of size: " << (*v).size() << "\n";
    for (auto i : *v){
        cout << i << std::endl;
    }
    // (*v)[1] = 30;
    vector<int> v2{5,6,7,8,9,10};
    v = &v2;
    cout << "Variable v now points to: " << v << std::endl;
}

int main()
{
    int num = 2;
    int *ptr_to_num = &num; //accessing memory address with the amp
    //cout << "Memory reference of num: " << &num << std::endl;
    //PointerTest(ptr_to_num);
    //cout << "The value of num now is: " << num << std::endl;
    vector<int> numList {1,2,3};
    VectorPointerTest(&numList);
    int *empty_ptr;
    cout << "Vector after calling function:\n";
    for (auto i : numList) {
        cout << i << std::endl;
    }
}