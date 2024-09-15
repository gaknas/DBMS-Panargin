#pragma once
#include <sstream>

/*
	@brief ����� ����
*/
class Cube
{
private:
	//����� ����
	double side;
public:
	/*
	@brief ������������ ����� ����
	@return �����
	*/
	double GetVolume() const;
	/*
	@brief ������������ ������� ����������� ����
	@return ������� �����������
	*/
	double GetSurfaceArea() const;
	/*
	@brief �������������� ����� ������ ������ Cube
	@param side ����� ����
	*/
	Cube(const double side);
	/*
	@brief ��������� ������� �������������� ������� � ������
	@return ��������� ������������� �������
	*/
	std::string ToString() const;

	friend std::ostream& operator<<(std::ostream& stream, const Cube& cube);
};