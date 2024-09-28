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

//����� ������-������� ������
class RBTree
{
private:
	//������ ������
	struct node* root;
	/*
	* @brief ������� ������ ������� ����
	* @param n ����, � �������� ������ �������
	* @return ��������� �� ������� ����
	*/
	struct node* grandparent(struct node* n);
	/*
	* @brief ������� ������ ���� ����
	* @param n ����, � �������� ������ ����
	* @return ��������� �� ���� ����
	*/
	struct node* uncle(struct node* n);
	/*
	* @brief ������� ������ ����� ����
	* @param n ����, � �������� ������ ����
	* @return ��������� �� ����� ����
	*/
	struct node* sibling(struct node* n);
	/*
	* @brief �������, �������������� ����� �������
	* @param n ����, ������������ �������� ���������� �������
	*/
	void rotate_left(struct node* n);
	/*
	* @brief �������, �������������� ������ �������
	* @param n ����, ������������ �������� ���������� �������
	*/
	void rotate_right(struct node* n);
	/*
	* @brief �������, ������ 1: N - ������
	* @param n ����������� ����
	*/
	void insert_case1(struct node* n);
	/*
	* @brief �������, ������ 2: P - ������
	* @param n ����������� ����
	*/
	void insert_case2(struct node* n);
	/*
	* @brief �������, ������ 3: U - �������
	* @param n ����������� ����
	*/
	void insert_case3(struct node* n);
	/*
	* @brief �������, ������ 4: N - ������ ������� P, P - ����� ������� G
	* @param n ����������� ����
	*/
	void insert_case4(struct node* n);
	/*
	* @brief �������, ������ 5: N - ����� ������� P, P - ����� ������� G
	* @param n ����������� ����
	*/
	void insert_case5(struct node* n);
	/*
	* @brief ������ ������� ���� � ��� ��������
	* @param n ����, ������� ����� ���������
	* @param child �������, ������� ����� �������� ����
	*/
	void replace_node(struct node* n, struct node* child);
	/*
	* @brief ������� ������ ������� ����
	* @param n ����, � �������� ���������� ������� �������
	*/
	void delete_one_child(struct node* n);
	/*
	* @brief ��������, ������ 1: N - ����� ������
	* @param n ��������� ����
	*/
	void delete_case1(struct node* n);
	/*
	* @brief ��������, ������ 2: S - �������
	* @param n ��������� ����
	*/
	void delete_case2(struct node* n);
	/*
	* @brief ��������, ������ 3: P, S � ���� S - ������
	* @param n ��������� ����
	*/
	void delete_case3(struct node* n);
	/*
	* @brief ��������, ������ 4: S � ��� ���� ������, �� P - �������
	* @param n ��������� ����
	*/
	void delete_case4(struct node* n);
	/*
	* @brief ��������, ������ 5: S - ������, ����� ������� S - �������, ������ ������� S - ������, N �������� ����� �������� ������ ����
	* @param n ��������� ����
	*/
	void delete_case5(struct node* n);
	/*
	* @brief ��������, ������ 6: S - ������, ������ ������� S - �������, N �������� ����� �������� ������ ����
	* @param n ��������� ����
	*/
	void delete_case6(struct node* n);
public:
	// ����������� �� ���������, ������� ������ ������
	RBTree();
	/*
	* @brief ������� ������ � ������
	* @param root ������ ������������ ������
	*/
	RBTree(int root);
	/*
	* @brief ������� ������ �� ����������������� �������
	* @param initializer_list ���������������� ������
	*/
	RBTree(std::initializer_list<int> list);
	// ����������, ����������� ������ �������
	~RBTree();
	/*
	* @brief ����������� �����������
	* @param other ���������� ������
	*/
	RBTree(RBTree* other);
	/*
	* @brief ��������������� ��������� ���������
	* @param other ������, � �������� �������������� ������
	* @return ��� ������ ��� �������������� ���������
	*/
	RBTree* operator=(RBTree* other);
	/*
	* @brief ������� �������� � ������
	* @param item ����������� �������
	*/
	void insert_item(int item);
	/*
	* @brief �������� �������� �� ������
	* @param item ��������� �������
	*/
	void delete_item(int item);
	/*
	* @brief ������� ����������� ���� ������
	* @param item �������, ������� ���������� �����
	* @return ��������� �� ������� ���� ������
	*/
	struct node* find_item(int item);
	/*
	* @brief ������������ ������� � ���� ������
	* @return ��������� ������������� �������
	*/
	std::string ToString();
};