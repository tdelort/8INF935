#include <Matrix3x3.h>
#include <Matrix3x4.h>
#include <Vector3D.h>

#include <iostream>

int main()
{
    Matrix3x3 m1 = {
        { -6.0 / 13.0, -5.0 / 13.0,  2.0 / 13.0 },
        { -5.0 / 13.0, -15.0 / 13.0, -7.0 / 13.0 },
        {  2.0 / 13.0, -7.0 / 13.0, -5.0 / 13.0 }
    };

    Vector3D v1(1.0, 2.0, 3.0);

    std::cout << "m1 * v1 = " << m1 * v1 << std::endl;

    Matrix3x4 m = {
        { 2.0,-3.0, 5.0, 1.0},
        {-3.0, 2.0,-4.0, 2.0},
        { 5.0,-4.0, 5.0, 3.0}
    };

    Matrix3x4 mInv = m.Inverse();

    std::cout << "m: " << std::endl;
    std::cout << m << std::endl;
    std::cout << "mInv: " << std::endl;
    std::cout << mInv << std::endl;
    std::cout << "m * mInv: " << std::endl;
    std::cout << m * mInv << std::endl;

    return 0;
}