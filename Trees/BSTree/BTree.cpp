#include "BTree.h"
BTree::BTree()
{
	this->root = nullptr;
}

BTree::BTree(int root)
{
	this->root = new BNode{ root };
}

std::string BTree::ToString()
{
	if (this->root == nullptr)
	{
		return std::string();;
	}
	return this->recursive_print(this->root);
}

std::string BTree::recursive_print(BNode* n)
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

void BTree::insert_item(int key)
{
	if (this->root == nullptr)
	{
		this->root = new BNode{ key };
	}
	else
	{
		this->recursive_insert(this->root, key);
	}
}

BNode* BTree::recursive_insert(BNode* n, int key)
{
	if (n->key == key)
	{
		throw std::invalid_argument("В дереве не может быть двух узлов с одинаковым значением");
	}
	if ((n->key > key) && (n->left == nullptr))
	{
		n->left = new BNode{ key };
		n->left->parent = n;
		return n->left;
	}
	if ((n->key > key) && (n->left != nullptr))
	{
		return this->recursive_insert(n->left, key);
	}
	if ((n->key < key) && (n->right == nullptr))
	{
		n->right = new BNode{ key };
		n->right->parent = n;
		return n->right;
	}
	if ((n->key < key) && (n->right != nullptr))
	{
		return this->recursive_insert(n->right, key);
	}
}

BNode* BTree::find_item(int key)
{
	if (this->root == nullptr)
	{
		throw std::logic_error("Дерево пустое");
	}
	else
	{
		return BTree::recursive_find(this->root, key);
	}
}

BNode* BTree::recursive_find(BNode* n, int key)
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

BNode* BTree::find_successor(BNode* n)
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

void BTree::delete_item(int key)
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
	else if (this->root->key == key)
	{
		if ((this->root->left != nullptr) && (this->root->right == nullptr))
		{
			BNode* temp = this->root->left;
			temp->parent = nullptr;
			delete this->root;
			this->root = temp;
		}
		else if ((this->root->left == nullptr) && (this->root->right != nullptr))
		{
			BNode* temp = this->root->right;
			temp->parent = nullptr;
			delete this->root;
			this->root = temp;
		}
		else
		{
			if (this->root->right->left == nullptr)
			{
				BNode* temp = this->root->right;
				temp->parent = nullptr;
				temp->left = this->root->left;
				delete this->root;
				this->root = temp;
			}
			else
			{
				BNode* successor = this->find_successor(this->root->right);
				BNode* temp = new BNode(successor);
				this->delete_item(successor->key);
				temp->left = this->root->left;
				temp->right = this->root->right;
				temp->parent = nullptr;
				delete this->root;
				this->root = temp;
			}
		}
	}
	else
	{
		BNode* deleted_item = this->find_item(key);
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
					BNode* successor = this->find_successor(deleted_item->right);
					BNode* temp = new BNode(successor);
					this->delete_item(successor->key);
					temp->left = deleted_item->left;
					temp->right = deleted_item->right;
					temp->parent = deleted_item->parent;
					deleted_item->parent->left = temp;
					delete deleted_item;
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
					BNode* successor = this->find_successor(deleted_item->right);
					BNode* temp = new BNode(successor);
					this->delete_item(successor->key);
					temp->left = deleted_item->left;
					temp->right = deleted_item->right;
					temp->parent = deleted_item->parent;
					deleted_item->parent->right = temp;
					delete deleted_item;
				}
			}
		}
	}
}

BTree::~BTree()
{
	if (this->root != nullptr)
	{
		this->recursive_delete(root);
	}
}

void BTree::recursive_delete(BNode* n)
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