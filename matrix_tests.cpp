#include <Matrix3x3.h>

#include <iostream>

int main()
{
    Matrix3x3 m = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    Matrix3x3 m2 = m.Transpose();

    std::cout << m << std::endl;
    std::cout << m2 << std::endl;

    return 0;
}