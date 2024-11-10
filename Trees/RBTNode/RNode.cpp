#include "RNode.h"

RNode::RNode()
{
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->key = 0;
	this->color = node_colors::RED;
}

RNode::RNode(int key) : RNode()
{
	this->key = key;
}

RNode::RNode(const RNode* other) : RNode()
{
	this->key = other->key;
	this->color = other->color;
}

RNode::~RNode()
{
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}