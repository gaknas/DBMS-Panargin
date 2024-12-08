#include "RNode.h"

bool RNode::operator==(RNode& other)
{
	return ((this->key == other.key) &&
		(this->color == other.color) &&
		(this->parent == other.parent) &&
		(this->left == other.left) &&
		(this->right == other.right));
}

RNode::RNode() : parent{ nullptr }, left{ nullptr }, right{ nullptr }, key{ 0 }, color{ node_colors::RED } {}

RNode::RNode(int key) : parent{ nullptr }, left{ nullptr }, right{ nullptr }, key{ key }, color{ node_colors::RED } {}

RNode::RNode(const RNode* other) : parent{ nullptr }, left{ nullptr }, right{ nullptr }, key{ other->key }, color{ other->color } {}