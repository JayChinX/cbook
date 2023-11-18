
#include <cassert>
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "books.h"

#ifdef USE_MYMATH
#include <mathfunctions.h>
#else
#include <cmath>
#endif

int main(int, char **)
{
    double inputValue = 5.0;
#ifdef USE_MYMATH
    double outputValue = mySquare(inputValue);
    std::cout << "mySquare func called!" << std::endl;
#else
    double outputValue = pow(inputValue, 2);
    std::cout << "pow func called!" << std::endl;
#endif
    std::cout << "result: " << outputValue << std::endl;
    std::cout << "result: " << __cplusplus << std::endl;
    start();
    printf("This code running.\n");
    return 0;
}
