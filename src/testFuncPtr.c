// Code that tests function Pointers 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int add2int(int x, int y)
{
    printf("x + y = ");
    return x + y;
}

int sub2int(int x, int y)
{
    printf("x - y = ");
    return x - y;
}

int mul2int(int x, int y)
{
    printf("x * y = ");
    return x * y;
}

int div2int(int x, int y)
{
    printf("x / y = ");
    return x / y;
}

int api(int x, int y, int (*fptr)(int, int))
{
    return (*fptr)(x, y);
}

int main()
{
    int x = 1024, y = 32, i;
    printf("x = %d,\ty = %d\n", x, y);

    // 四則運算 with array of function pointers
    int (*fptr[4])(int , int) = {add2int, sub2int, mul2int, div2int};
    for(i = 0; i < 4; i++)
    {
        printf("%d\n", (*fptr[i])(x, y));
    }
    // 四則運算 with function api() 
    for(i = 0; i < 4; i++)
    {
        printf("%d\n", api(x, y, fptr[i]));
    }
    return 0;
}