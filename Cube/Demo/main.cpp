#include <iostream>
#include "../Domain/Cube.h"

int main()
{
	double side;
	setlocale(LC_ALL, "Russian");
	std::cout << "������� ������� ����\n";
	std::cin >> side;
	Cube cube{ side };
	std::cout << "������ ���: " << cube << "\n";
	std::cout << "����� ����: " << cube.GetVolume() << "\n";
	std::cout << "������� ����������� ����: " << cube.GetSurfaceArea() << std::endl;
}