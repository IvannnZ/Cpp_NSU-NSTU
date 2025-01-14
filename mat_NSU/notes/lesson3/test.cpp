#include <iostream>

void fun()
{
    std::cout << "in func\n";
    int a;
    std::cout << "a:" << a << std::endl;
    int b[3] = {1};
    std::cout << "b[0] b[1] b:" << b[0] << ' ' << 1[b] << ' ' << b << std::endl; //так тоже можно, и это раотает корректно, но не стоит так делать
    int* c[3];
    std::cout << "c[0] c:" << c[0] << ' ' << c << std::endl;
}

int main()
{
    int a;
    std::cout << "a:" << a << std::endl;
    int b[3] = {1};
    std::cout << "b[0] b[1] b:" << b[0] << ' ' << b[1] << ' ' << b << std::endl;
    int* c[3];
    std::cout << "c[0] c:" << c[0] << ' ' << c << std::endl;
    fun();

    a = 42;
    int* ptr = &a;
    std::cout << ptr << std::endl;
    ptr -= 5; //
    std::cout << a << " " << *ptr << std::endl;
    return 0;
}
