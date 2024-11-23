#include <iostream>
#include "../RBTree/RTree.h"
#include "../BSTree/BTree.h"

int main()
{
	RTree rbt(6);
	rbt.insert_item(7);
	rbt.insert_item(8);
	rbt.insert_item(2);
	rbt.insert_item(1);
	rbt.insert_item(4);
	rbt.insert_item(3);
	rbt.insert_item(5);
	RTree rbt2{ 4, 2, 7, 1 };
	RTree rbt3(rbt2);
	rbt = std::move(rbt2);
	std::cout << rbt;
	std::cout << rbt3;
	rbt3.delete_item(1);
	std::cout << (rbt == rbt3);
	return 0;
}