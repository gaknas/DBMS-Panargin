#pragma once
#include <string>
#include <initializer_list>

enum node_colors { RED, BLACK };

struct node 
{
	struct node* parent, * left, * right;
	enum node_colors color;
	int key;
};

//Класс красно-черного дерева
class RBTree
{
private:
	//Корень дерева
	struct node* root;
	/*
	* @brief Функция поиска дедушки узла
	* @param n Узел, у которого ищется дедушка
	* @return Указатель на дедушку узла
	*/
	struct node* grandparent(struct node* n);
	/*
	* @brief Функция поиска дяди узла
	* @param n Узел, у которого ищется дядя
	* @return Указатель на дядю узла
	*/
	struct node* uncle(struct node* n);
	/*
	* @brief Функция поиска брата узла
	* @param n Узел, у которого ищется брат
	* @return Указатель на брата узла
	*/
	struct node* sibling(struct node* n);
	/*
	* @brief Функция, осуществляющая левый поворот
	* @param n Узел, относительно которого проводится поворот
	*/
	void rotate_left(struct node* n);
	/*
	* @brief Функция, осуществляющая правый поворот
	* @param n Узел, относительно которого проводится поворот
	*/
	void rotate_right(struct node* n);
	/*
	* @brief Вставка, случай 1: N - корень
	* @param n Вставляемый узел
	*/
	void insert_case1(struct node* n);
	/*
	* @brief Вставка, случай 2: P - чёрный
	* @param n Вставляемый узел
	*/
	void insert_case2(struct node* n);
	/*
	* @brief Вставка, случай 3: U - красный
	* @param n Вставляемый узел
	*/
	void insert_case3(struct node* n);
	/*
	* @brief Вставка, случай 4: N - правый потомок P, P - левый потомок G
	* @param n Вставляемый узел
	*/
	void insert_case4(struct node* n);
	/*
	* @brief Вставка, случай 5: N - левый потомок P, P - левый потомок G
	* @param n Вставляемый узел
	*/
	void insert_case5(struct node* n);
	/*
	* @brief Меняет местами узел с его потомком
	* @param n Узел, которой будет заменятся
	* @param child Потомок, который будет заменять узел
	*/
	void replace_node(struct node* n, struct node* child);
	/*
	* @brief Удаляет одного потомка узла
	* @param n Узел, у которого необходимо удалить потомка
	*/
	void delete_one_child(struct node* n);
	/*
	* @brief Удаление, случай 1: N - новый корень
	* @param n Удаляемый узел
	*/
	void delete_case1(struct node* n);
	/*
	* @brief Удаление, случай 2: S - красный
	* @param n Удаляемый узел
	*/
	void delete_case2(struct node* n);
	/*
	* @brief Удаление, случай 3: P, S и дети S - черные
	* @param n Удаляемый узел
	*/
	void delete_case3(struct node* n);
	/*
	* @brief Удаление, случай 4: S и его дети черные, но P - красный
	* @param n Удаляемый узел
	*/
	void delete_case4(struct node* n);
	/*
	* @brief Удаление, случай 5: S - черный, левый потомок S - красный, правый потомок S - черный, N является левым потомком своего отца
	* @param n Удаляемый узел
	*/
	void delete_case5(struct node* n);
	/*
	* @brief Удаление, случай 6: S - черный, правый потомок S - красный, N является левым потомком своего отца
	* @param n Удаляемый узел
	*/
	void delete_case6(struct node* n);
public:
	// Конструктор по умолчанию, создает пустое дерево
	RBTree();
	/*
	* @brief Создает объект с корнем
	* @param root Корень создаваемого дерева
	*/
	RBTree(int root);
	/*
	* @brief Создает объект из инициализирующего массива
	* @param initializer_list инициализирующий массив
	*/
	RBTree(std::initializer_list<int> list);
	// Деструктор, освобождает память объекта
	~RBTree();
	/*
	* @brief Конструктор копирования
	* @param other Копируемое дерево
	*/
	RBTree(RBTree* other);
	/*
	* @brief Переопределение оператора равенства
	* @param other Объект, к которому приравнивается данный
	* @return Сам объект для множественного равенства
	*/
	RBTree* operator=(RBTree* other);
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
	struct node* find_item(int item);
	/*
	* @brief Представляет элемент в виде строки
	* @return Строковое представление объекта
	*/
	std::string ToString();
};