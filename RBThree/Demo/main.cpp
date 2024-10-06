#include <iostream>
#include "../RBThree/RBTree.h"

int main()
{
	RBTree rbt(6);
	rbt.insert_item(7);
	rbt.insert_item(8);
	rbt.insert_item(2);
	rbt.insert_item(1);
	rbt.insert_item(4);
	rbt.insert_item(3);
	rbt.insert_item(5);
	std::cout << rbt.ToString() << "\n";
	rbt.delete_item(2);
	std::cout << rbt.ToString();
	return 0;
}