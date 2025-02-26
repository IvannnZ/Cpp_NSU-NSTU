#include <iostream>
#include <vector>

void test(std::vector<int> v)
{
    for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i)
    {
        const int a = *i;
        std::cout<<a;
    }
}

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

void alloc_test(){
    int *p = new int (42);
    std::cout<< "p:" << *p << std::endl;
}


void const_test(){
    int a = 5;
    const int const_a = 2;
    const int *ptr_const_a = &const_a;
    const int *ptr_a = &a;
    int *ptr;
    //ptr = ptr_const_a;

    //*ptr_a = 1;
    ptr_a = ptr_const_a;
    //*ptr_const_a = 5;
    ptr_const_a = ptr;

    ptr_a = &a;
    int *const const_ptr_a = &a;
    const int * const const_ptr_const_a = &const_a;
    //const_ptr_a = ptr;
    *const_ptr_a = 1;
    //const_ptr_const_a = ptr;
    //*const_ptr_const_a = 1;
}

int main()
{
//    int a;
//    std::cout << "a:" << a << std::endl;
//    int b[3] = {1};
//    std::cout << "b[0] b[1] b:" << b[0] << ' ' << b[1] << ' ' << b << std::endl;
//    int* c[3];
//    std::cout << "c[0] c:" << c[0] << ' ' << c << std::endl;
//    fun();
//
//    a = 42;
//    int* ptr = &a;
//    std::cout << ptr << std::endl;
//    ptr -= 5; //
//    std::cout << a << " " << *ptr << std::endl;
    alloc_test();
    return 0;
}
