#include "BNode.h"

BNode::BNode()
{
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->key = 0;
}

BNode::BNode(int key)
{
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->key = key;
}

BNode::BNode(const BNode* other)
{
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->key = other->key;
}