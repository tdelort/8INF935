#include <iostream>

#include "Vector3D.h"

int main()
{
	// Test constructor
	Vector3D v0;
	std::cout << v0 << std::endl; // 0; 0; 0
	Vector3D v1(1, 2, 3);
	std::cout << v0 + v1 << std::endl; // 1; 2; 3
	std::cout << v0 - v1 << std::endl; // -1; -2; -3
	std::cout << v1 + 1 << std::endl; // 2 3 4
	std::cout << v1 - 1 << std::endl; // 0 1 2
	std::cout << v1 * 2 << std::endl; // 2 4 6
	std::cout << 2 * v1 << std::endl; // 2 4 6
	std::cout << v1 / 2 << std::endl; // 0.5 1 1.5
	std::cout << (v1 == Vector3D(0, 1, 2) + 1 ? "true" : "false") << std::endl;
	std::cout << Vector3D(3, 0, 0).dot(Vector3D(2, 6, 0)) << std::endl; //6
	std::cout << Vector3D(1, 2, 3).cross(Vector3D(4, 5, 6)) << std::endl; // 2*6 - 3*5; 3*4 - 1*6; 1*5 - 2*4 = -3; 6; -3
	std::cout << Vector3D(3, 4, 0).norm() << std::endl; //5
	std::cout << Vector3D(3, 4, 0).normalize().norm() << std::endl; //1

	return EXIT_SUCCESS;
}

