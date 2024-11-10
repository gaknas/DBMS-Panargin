#include <iostream>
#include "../RBTree/RTree.h"
#include "../BSTree/BTree.h"

std::string converter(bool arg)
{
	return arg ? "VALID" : "INVALID";
}

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
	std::cout << converter(check_three(rbt)) << " three; height: " << rbt.GetHeight() << '\n';
	std::cout << rbt.ToString() << "\n";
	rbt.delete_item(7);
	std::cout << converter(check_three(rbt)) << " three; height: " << rbt.GetHeight() << '\n';
	std::cout << rbt.ToString(true);
	return 0;
}