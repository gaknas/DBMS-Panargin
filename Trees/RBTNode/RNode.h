#pragma once

enum class node_colors { RED, BLACK };

struct RNode
{
	RNode* parent, * left, * right;
	node_colors color;
	int key;
	bool operator==(RNode& other);
	RNode();
	RNode(int key);
	RNode(const RNode* other);
};