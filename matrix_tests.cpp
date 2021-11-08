#include <Matrix3x3.h>

#include <iostream>

int main()
{
    Matrix3x3 m = {
        {1.0, 2.0, 3.0},
        {1.0, 2.0, 3.0},
        {1.0, 2.0, 3.0}
    };

    Matrix3x3 m2 = {
        {2.0f, -6.0f, 4.0f},
        {-2.0f, 3.0f, -4.0f},
        {0.0f, -3.3f, 9.0f}
    };

    std::cout << m << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m * m2 << std::endl;

    return 0;
}