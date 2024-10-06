#include <string>
#include <sstream>
#include "RBTree.h"

RBTree::RBTree()
{
	this->root = nullptr;
}

RBTree::RBTree(int root)
{
	this->root = new node{ root };
}

std::string RBTree::ToString()
{
	if (this->root == nullptr)
	{
		return "";
	}
	return this->recursive_print(this->root);
}

std::string RBTree::recursive_print(node* n)
{
	std::stringstream buffer;
	if (!(n->left == nullptr))
	{
		buffer << recursive_print(n->left);
	}
	buffer << n->key;
	buffer << " ";
	if (!(n->right == nullptr))
	{
		buffer << recursive_print(n->right);
	}
	return buffer.str();
}

void RBTree::insert_item(int key)
{
	if (this->root == nullptr)
	{
		this->root = new node{ key };
	}
	else
	{
		this->recursive_insert(this->root, key);
	}
}

node* RBTree::recursive_insert(node* n, int key)
{
	if (n->key == key)
	{
		throw std::invalid_argument("В дереве не может быть двух узлов с одинаковым значением");
	}
	if ((n->key > key) && (n->left == nullptr))
	{
		n->left = new node{ key };
		n->left->parent = n;
		return n->left;
	}
	if ((n->key > key) && (n->left != nullptr))
	{
		return this->recursive_insert(n->left, key);
	}
	if ((n->key < key) && (n->right == nullptr))
	{
		n->right = new node{ key };
		n->right->parent = n;
		return n->right;
	}
	if ((n->key < key) && (n->right != nullptr))
	{
		return this->recursive_insert(n->right, key);
	}
}

node* RBTree::find_item(int key)
{
	if (this->root == nullptr)
	{
		throw std::logic_error("Дерево пустое");
	}
	else
	{
		return RBTree::recursive_find(this->root, key);
	}
}

node* RBTree::recursive_find(node* n, int key)
{
	if (n->key == key)
	{
		return n;
	}
	else if ((n->key > key) && (n->left != nullptr))
	{
		return this->recursive_find(n->left, key);
	}
	else if ((n->key < key) && (n->right != nullptr))
	{
		return this->recursive_find(n->right, key);
	}
	else
	{
		throw std::invalid_argument("Нет элемента с таким значением");
	}
}

node* RBTree::find_successor(node* n)
{
	if (n->left == nullptr)
	{
		return n;
	}
	else
	{
		return this->find_successor(n->left);
	}
}

void RBTree::delete_item(int key)
{
	if (this->root == nullptr)
	{
		throw std::logic_error("Дерево пустое");
	}
	else if ((this->root->left == nullptr) && (this->root->right == nullptr) && (this->root->key == key))
	{
		delete this->root;
		this->root = nullptr;
	}
	else if ((this->root->left == nullptr) && (this->root->right == nullptr) && (this->root->key != key))
	{
		throw std::invalid_argument("Нет элемента с таким значением");
	}
	else
	{
		node* deleted_item = this->find_item(key);
		if ((deleted_item->left == nullptr) && (deleted_item->right == nullptr))
		{
			if (deleted_item->parent->left == deleted_item)
			{
				deleted_item->parent->left = nullptr;
				delete deleted_item;
			}
			else
			{
				deleted_item->parent->right = nullptr;
				delete deleted_item;
			}
		}
		else if ((deleted_item->left != nullptr) && (deleted_item->right == nullptr))
		{
			if (deleted_item->parent->left == deleted_item)
			{
				deleted_item->parent->left = deleted_item->left;
				deleted_item->left->parent = deleted_item->parent;
				delete deleted_item;
			}
			else
			{
				deleted_item->parent->right = deleted_item->left;
				deleted_item->left->parent = deleted_item->parent;
				delete deleted_item;
			}
		}
		else if ((deleted_item->left == nullptr) && (deleted_item->right != nullptr))
		{
			if (deleted_item->parent->left == deleted_item)
			{
				deleted_item->parent->left = deleted_item->right;
				deleted_item->right->parent = deleted_item->parent;
				delete deleted_item;
			}
			else
			{
				deleted_item->parent->right = deleted_item->right;
				deleted_item->right->parent = deleted_item->parent;
				delete deleted_item;
			}
		}
		else
		{
			if (deleted_item->parent->left == deleted_item)
			{
				if (deleted_item->right->left == nullptr)
				{
					deleted_item->parent->left = deleted_item->right;
					deleted_item->right->parent = deleted_item->parent;
					delete deleted_item;
				}
				else
				{
					node* successor = this->find_successor(deleted_item->right);
					int temp = successor->key;
					this->delete_item(successor->key);
					deleted_item->key = temp;
				}
			}
			else
			{
				if (deleted_item->right->left == nullptr)
				{
					deleted_item->parent->right = deleted_item->right;
					deleted_item->right->parent = deleted_item->parent;
					delete deleted_item;
				}
				else
				{
					node* successor = this->find_successor(deleted_item->right);
					int temp = successor->key;
					this->delete_item(successor->key);
					deleted_item->key = temp;
				}
			}
		}
	}
}

RBTree::~RBTree()
{
	if (this->root != nullptr)
	{
		this->recursive_delete(root);
	}
}

void RBTree::recursive_delete(node* n)
{
	if (n->left != nullptr)
	{
		this->recursive_delete(n->left);
	}
	if (n->right != nullptr)
	{
		this->recursive_delete(n->right);
	}
	delete n;
}