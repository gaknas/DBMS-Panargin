#pragma once
#include <initializer_list>
#include <string>
#include <sstream>
#include "../RBTNode/RNode.h"

class RTree
{
private:
	///Корень дерева
	RNode* root;
	/*
	* @brief Функция, обходящая дерево для вывода в строку
	* @param n Узел, начиная с которого будет осуществляться обход дерева
	* @return Строковое представление дерева
	*/
	std::string recursive_print(RNode* n);
	/*
	* @brief Функция, вставляющая новый узел
	* @param n Узел, начиная с которого будет осуществляться обход дерева для вставки
	* @param key Значение нового узла
	* @return Указатель на созданный узел
	*/
	RNode* recursive_insert(RNode* n, int key);
	/*
	* @brief Функция, осуществляющая поиск узла
	* @param n Узел, начиная с которого будет осуществляться обход дерева для поиска
	* @param key Значение узла, который необходимо найти
	* @return Указатель на данный узел
	*/
	RNode* recursive_find(RNode* n, int key);
	/*
	* @brief Функция поиска преемника узла для операции удаления
	* @param n Узел, преемника которого необходимо найти
	* @return преемник узла
	*/
	RNode* find_successor(RNode* n);
	/*
	* @brief Функция, очищающая дерево
	* @param n Узел, начиная с которого будет осуществляться обход дерева для удаления
	*/
	void recursive_delete(RNode* n);
	/*
	* @brief Функция поиска дедушки узла
	* @param n Узел, у которого ищется дедушка
	* @return Указатель на дедушку узла
	*/
	RNode* grandparent(RNode* n);
	/*
	* @brief Функция поиска дяди узла
	* @param n Узел, у которого ищется дядя
	* @return Указатель на дядю узла
	*/
	RNode* uncle(RNode* n);
	/*
	* @brief Функция поиска брата узла
	* @param n Узел, у которого ищется брат
	* @return Указатель на брата узла
	*/
	RNode* sibling(RNode* n);
	/*
	* @brief Функция, осуществляющая левый поворот
	* @param n Узел, относительно которого проводится поворот
	*/
	void rotate_left(RNode* n);
	/*
	* @brief Функция, осуществляющая правый поворот
	* @param n Узел, относительно которого проводится поворот
	*/
	void rotate_right(RNode* n);
	/*
	* @brief Вставка, случай 1: N - корень
	* @param n Вставляемый узел
	*/
	void insert_case1(RNode* n);
	/*
	* @brief Вставка, случай 2: P - чёрный
	* @param n Вставляемый узел
	*/
	void insert_case2(RNode* n);
	/*
	* @brief Вставка, случай 3: U - красный
	* @param n Вставляемый узел
	*/
	void insert_case3(RNode* n);
	/*
	* @brief Вставка, случай 4: N - правый потомок P, P - левый потомок G
	* @param n Вставляемый узел
	*/
	void insert_case4(RNode* n);
	/*
	* @brief Вставка, случай 5: N - левый потомок P, P - левый потомок G
	* @param n Вставляемый узел
	*/
	void insert_case5(RNode* n);
	/*
	* @brief Меняет местами узел с его потомком
	* @param n Узел, которой будет заменятся
	* @param child Потомок, который будет заменять узел
	*/
	void replace_node(RNode* n, RNode* child);
	/*
	* @brief Удаляет одного потомка узла
	* @param n Узел, у которого необходимо удалить потомка
	*/
	void delete_one_child(RNode* n);
	/*
	* @brief Удаление, случай 1: N - новый корень
	* @param n Удаляемый узел
	*/
	void delete_case1(RNode* n);
	/*
	* @brief Удаление, случай 2: S - красный
	* @param n Удаляемый узел
	*/
	void delete_case2(RNode* n);
	/*
	* @brief Удаление, случай 3: P, S и дети S - черные
	* @param n Удаляемый узел
	*/
	void delete_case3(RNode* n);
	/*
	* @brief Удаление, случай 4: S и его дети черные, но P - красный
	* @param n Удаляемый узел
	*/
	void delete_case4(RNode* n);
	/*
	* @brief Удаление, случай 5: S - черный, левый потомок S - красный, правый потомок S - черный, N является левым потомком своего отца
	* @param n Удаляемый узел
	*/
	void delete_case5(RNode* n);
	/*
	* @brief Удаление, случай 6: S - черный, правый потомок S - красный, N является левым потомком своего отца
	* @param n Удаляемый узел
	*/
	void delete_case6(RNode* n);

	int calculate_height(RNode* n);
public:
	/// Конструктор по умолчанию, создает пустое дерево
	RTree();
	/*
	* @brief Создает объект с корнем
	* @param root Корень создаваемого дерева
	*/
	RTree(int root);
	/*
	* @brief Создает объект из инициализирующего массива
	* @param initializer_list инициализирующий массив
	*/
	RTree(std::initializer_list<int> list);
	/// Деструктор, освобождает память объекта
	~RTree();
	/*
	* @brief Конструктор копирования
	* @param other Копируемое дерево
	*/
	RTree(RTree* other);
	/*
	* @brief Переопределение оператора равенства
	* @param other Объект, к которому приравнивается данный
	* @return Сам объект для множественного равенства
	*/
	RTree* operator=(RTree* other);
	/*
	* @brief Вставка элемента в дерево
	* @param item Вставляемый элемент
	*/
	void insert_item(int item);
	/*
	* @brief Удаление элемента из дерева
	* @param item Удаляемый элемент
	*/
	void delete_item(int item);
	/*
	* @brief Находит необходимый узел дерева
	* @param item Элемент, который необходимо найти
	* @return Указатель на искомый узел дерева
	*/
	RNode* find_item(int item);
	/*
	* @brief Представляет элемент в виде строки
	* @return Строковое представление объекта
	*/
	std::string ToString(bool debug=false);

	friend bool check_three(RTree& rbt);
	std::string TestPrint(RNode* n);
	int GetHeight() {
		return this->calculate_height(this->root);
	}
};

bool check_three(RTree& rbt);
bool check_case1(RNode* root);
bool check_case2(RNode* n);
bool check_case3(RNode* n);
int calculate_black_height(RNode* n);