#include "Cube.h"
#include <stdexcept>

Cube::Cube(const double side)
{
	if (side < 0)
	{
		throw std::out_of_range("������� ���� �� ����� ���� �������������");
	}
	this->side = side;
}

std::string Cube::ToString() const
{
	std::stringstream buffer{};
	buffer << "���{�������: " << this->side << "}";
	return buffer.str();
}

double Cube::GetVolume() const
{
	return this->side * this->side * this->side;
}

double Cube::GetSurfaceArea() const
{
	return 6 * this->side * this->side;
}

std::ostream& operator<<(std::ostream& stream, const Cube& cube)
{
	return stream << cube.ToString();
}
