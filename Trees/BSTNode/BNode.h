#pragma once
struct BNode
{
	BNode* parent, * left, * right;
	int key;
	BNode();
	BNode(int key);
	BNode(const BNode* other);
};