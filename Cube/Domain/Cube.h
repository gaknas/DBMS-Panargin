#pragma once
#include <sstream>

/*
	@brief Класс куба
*/
class Cube
{
private:
	//Ребро куба
	double side;
public:
	/*
	@brief Рассчитывает объем куба
	@return объем
	*/
	double GetVolume() const;
	/*
	@brief Рассчитывает площадь поверхности куба
	@return площадь поверхности
	*/
	double GetSurfaceArea() const;
	/*
	@brief Инициализирует новый объект класса Cube
	@param side Ребро куба
	*/
	Cube(const double side);
	/*
	@brief Реализует функцию преобразования объекта в строку
	@return Строковое представление объекта
	*/
	std::string ToString() const;

	friend std::ostream& operator<<(std::ostream& stream, const Cube& cube);
};