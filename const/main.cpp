#include <iostream>
using namespace std;

int main()
{
    //常量引用
    //const char* 可以承载 “hello” 这种常量的（字符串常量指向的是常量区）
    //而char* 理论上不允许赋值为字符串字面量，只能赋值为一个可修改的字符串指针
    const char* a = "hello"; //right 
    char* b = "hello"; // wrong
    
    //像“hello”，5，这种字面量都是常量，他们是不可以修改的，所以不能做非const类型的引用传递
    tans(5); //wrong
    tans1(5); //right

}

void tans(int& x) {
    cout << x << endl;
}

void tans1(const int& x) {
    cout << x << endl;
}

