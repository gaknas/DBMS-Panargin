#pragma once
#include <string>
#include <sstream>
#include "../BSTNode/BNode.h"

///Класс дерева двоичного поиска
class BTree
{
private:
	///Корень дерева
	BNode* root;

	/*
	* @brief Функция, обходящая дерево для вывода в строку
	* @param n Узел, начиная с которого будет осуществляться обход дерева
	* @return Строковое представление дерева
	*/
	std::string recursive_print(BNode* n);
	/*
	* @brief Функция, вставляющая новый узел
	* @param n Узел, начиная с которого будет осуществляться обход дерева для вставки
	* @param key Значение нового узла
	* @return Указатель на созданный узел
	*/
	BNode* recursive_insert(BNode* n, int key);
	/*
	* @brief Функция, осуществляющая поиск узла
	* @param n Узел, начиная с которого будет осуществляться обход дерева для поиска
	* @param key Значение узла, который необходимо найти
	* @return Указатель на данный узел
	*/
	BNode* recursive_find(BNode* n, int key);
	/*
	* @brief Функция поиска преемника узла для операции удаления
	* @param n Узел, преемника которого необходимо найти
	* @return преемник узла
	*/
	BNode* find_successor(BNode* n);
	/*
	* @brief Функция, очищающая дерево
	* @param n Узел, начиная с которого будет осуществляться обход дерева для удаления
	*/
	void recursive_delete(BNode* n);

public:
	/// Конструктор по умолчанию, создает пустое дерево
	BTree();
	/*
	* @brief Создает объект с корнем
	* @param root Корень создаваемого дерева
	*/
	BTree(int root);
	/*
	* @brief Создает объект из инициализирующего массива
	* @param initializer_list инициализирующий массив
	*/
	BTree(std::initializer_list<int> list);
	/// Деструктор, освобождает память объекта
	~BTree();
	/*
	* @brief Конструктор копирования
	* @param other Копируемое дерево
	*/
	BTree(BTree* other);
	/*
	* @brief Переопределение оператора равенства
	* @param other Объект, к которому приравнивается данный
	* @return Сам объект для множественного равенства
	*/
	BTree* operator=(BTree* other);
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
	BNode* find_item(int item);
	/*
	* @brief Представляет элемент в виде строки
	* @return Строковое представление объекта
	*/
	std::string ToString();
};