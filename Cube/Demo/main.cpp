#include <iostream>
#include "../Domain/Cube.h"

int main()
{
	double side;
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите сторону куба\n";
	std::cin >> side;
	Cube cube{ side };
	std::cout << "Создан куб: " << cube << "\n";
	std::cout << "Объем куба: " << cube.GetVolume() << "\n";
	std::cout << "Площадь поверхности куба: " << cube.GetSurfaceArea() << std::endl;
}