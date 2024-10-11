#include <iostream>
#include <stdio.h>
//#include <malloc.h>

int main( int argc, char* argv[] )
{
    using namespace std; 
    if( argc != 2 )
	{
        cout << "Error no file\n";
        return 42; 
    }

    //FILE *input = fopen(argv[1], "rt");
    int v = sizeof(int);
    int* a = (int *)malloc(sizeof(int) * 5);
    printf("\n%i \n", *a);



    return 0;
}