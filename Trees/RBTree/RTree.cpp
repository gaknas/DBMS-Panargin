#include "RTree.h"

RTree::RTree() : root{ nullptr } {}

RTree::RTree(int root) : RTree::RTree()
{
	this->root = new RNode{ root };
	this->insert_case1(this->root);
}

RTree::RTree(std::initializer_list<int> list) : RTree::RTree()
{
	for (int it : list)
	{
		this->insert_item(it);
	}
}

RTree::RTree(const RTree& other) : RTree::RTree()
{
	this->root = new RNode(other.root);
	this->recursive_copy(this->root, other.root, nullptr);
}

RTree::RTree(RTree&& other) noexcept : RTree::RTree()
{
	this->root = other.root;
	other.root = nullptr;
}

RTree& RTree::operator=(const RTree& other)
{
	if (other == *this)
		return *this;
	RTree temp(other);
	std::swap(temp.root, this->root);
	return *this;
}

RTree& RTree::operator=(RTree&& other) noexcept
{
	if (other == *this)
		return *this;
	std::swap(this->root, other.root);
	return *this;
}

bool RTree::operator==(const RTree& other) const
{
	return recursive_compare(this->root, other.root);
}

bool RTree::recursive_compare(RNode* current, RNode* other) const
{
	if (current == nullptr && other == nullptr)
		return true;
	else if ((current == nullptr && other != nullptr) || (current != nullptr && other == nullptr))
		return false;
	else
		return ((current->key == other->key) && (current->color == other->color) && this->recursive_compare(current->left, other->left) && this->recursive_compare(current->right, other->right));
}

RNode* RTree::grandparent(RNode* n)
{
	if (n != nullptr && n->parent != nullptr) return n->parent->parent;
	return nullptr;
	
}

RNode* RTree::uncle(RNode* n)
{
	RNode* g = grandparent(n);
	if (g == nullptr)
		return nullptr;
	if (n->parent == g->left)
		return g->right;
	return g->left;
}

RNode* RTree::sibling(RNode* n)
{
	if (n == n->parent->left)
		return n->parent->right;
	return n->parent->left;
}

void RTree::rotate_left(RNode* n)
{
	RNode* pivot = n->right;
	pivot->parent = n->parent;
	if (n->parent != nullptr)
	{
		if (n->parent->left == n)
			n->parent->left = pivot;
		else
			n->parent->right = pivot;
	}
	else
		this->root = pivot;

	n->right = pivot->left;
	if (pivot->left != nullptr)
		pivot->left->parent = n;
	
	n->parent = pivot;
	pivot->left = n;
}

void RTree::rotate_right(RNode* n)
{
	RNode* pivot = n->left;
	pivot->parent = n->parent;
	if (n->parent != nullptr)
	{
		if (n->parent->left == n)
			n->parent->left = pivot;
		else
			n->parent->right = pivot;
	}
	else
		this->root = pivot;

	n->left = pivot->right;
	if (pivot->right != nullptr)
		pivot->right->parent = n;

	n->parent = pivot;
	pivot->right = n;
}

std::string RTree::ToString(bool debug) const
{
	if (this->root == nullptr)
	{
		return std::string();
	}
	if (debug)
		return this->TestPrint(this->root);
	return this->recursive_print(this->root);
}

std::string converter(bool arg)
{
	return arg ? "VALID" : "INVALID";
}

std::ostream& operator << (std::ostream& os, RTree& rbt)
{
	return os << converter(check_tree(rbt)) << " three; height: " << rbt.GetHeight() << '\n' << rbt.ToString() << '\n';
}

std::string RTree::recursive_print(RNode* n) const
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

RNode* RTree::recursive_copy(RNode* current, RNode* other, RNode* parent)
{
	current->parent = parent;
	if (other->left != nullptr)
		current->left = recursive_copy(new RNode(other->left), other->left, current);
	if (other->right != nullptr)
		current->right = recursive_copy(new RNode(other->right), other->right, current);
	return current;
}

void RTree::insert_item(int key)
{
	if (this->root == nullptr)
	{
		this->root = new RNode{ key };
		this->root->color = node_colors::BLACK;
	}
	else
	{
		RNode* tmp = this->recursive_insert(this->root, key);
		this->insert_case2(tmp);
	}
}

void RTree::insert_case1(RNode* n)
{
	if (n->parent == nullptr)
		n->color = node_colors::BLACK;
	else
		insert_case2(n);
}

void RTree::insert_case2(RNode* n)
{
	if (n->parent->color == node_colors::BLACK)
		return;
	else
		insert_case3(n);
}

void RTree::insert_case3(RNode* n)
{
	RNode* u = uncle(n), * g;
	if ((u != nullptr) && (u->color == node_colors::RED))
	{
		n->parent->color = node_colors::BLACK;
		u->color = node_colors::BLACK;
		g = grandparent(n);
		g->color = node_colors::RED;
		insert_case1(g);
	}
	else {
		insert_case4(n);
	}
}

void RTree::insert_case4(RNode* n)
{
	RNode* g = grandparent(n);
	if ((n == n->parent->right) && (n->parent == g->left)) {
		rotate_left(n->parent);
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent == g->right)) {
		rotate_right(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

void RTree::insert_case5(RNode* n)
{
	RNode* g = grandparent(n);
	n->parent->color = node_colors::BLACK;
	g->color = node_colors::RED;
	if ((n == n->parent->left) && (n->parent == g->left)) {
		rotate_right(g);
	}
	else {
		rotate_left(g);
	}
}

RNode* RTree::recursive_insert(RNode* n, int key)
{
	if (n->key == key)
	{
		throw std::invalid_argument("В дереве не может быть двух узлов с одинаковым значением");
	}
	if ((n->key > key) && (n->left == nullptr))
	{
		n->left = new RNode{ key };
		n->left->parent = n;
		return n->left;
	}
	if ((n->key > key) && (n->left != nullptr))
	{
		return this->recursive_insert(n->left, key);
	}
	if ((n->key < key) && (n->right == nullptr))
	{
		n->right = new RNode{ key };
		n->right->parent = n;
		return n->right;
	}
	if ((n->key < key) && (n->right != nullptr))
	{
		return this->recursive_insert(n->right, key);
	}
}

RNode* RTree::find_item(int key)
{
	if (this->root == nullptr)
	{
		throw std::logic_error("Дерево пустое");
	}
	return RTree::recursive_find(this->root, key);
}

RNode* RTree::recursive_find(RNode* n, int key)
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
	throw std::invalid_argument("Нет элемента с таким значением");
}

RNode* RTree::find_successor(RNode* n)
{
	if (n->left == nullptr)
	{
		return n;
	}
	return this->find_successor(n->left);
}

void RTree::delete_item(int key)
{
	if (this->root == nullptr)
	{
		throw std::logic_error("Дерево пустое");
	}
	if ((this->root->left == nullptr) && (this->root->right == nullptr) && (this->root->key == key))
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
			RNode* temp = this->root->left;
			temp->parent = nullptr;
			delete this->root;
			this->root = temp;
			this->root->color = node_colors::BLACK;
		}
		else if ((this->root->left == nullptr) && (this->root->right != nullptr))
		{
			RNode* temp = this->root->right;
			temp->parent = nullptr;
			delete this->root;
			this->root = temp;
			this->root->color = node_colors::BLACK;
		}
		else
		{
			if (this->root->right->left == nullptr)
			{
				int temp = this->root->key;
				this->root->key = this->root->right->key;
				this->root->right->key = temp;
				delete_one_child(this->root->right);
			}
			else
			{
				RNode* successor = this->find_successor(this->root->right);
				int temp = this->root->key;
				this->root->key = successor->key;
				successor->key = temp;
				delete_one_child(successor);
			}
		}
	}
	else
	{
		RNode* deleted_item = this->find_item(key);
		if ((deleted_item->left == nullptr) && (deleted_item->right == nullptr))
		{
			if (deleted_item->color == node_colors::RED)
			{
				if (deleted_item == deleted_item->parent->left)
				{
					deleted_item->parent->left = nullptr;
					delete deleted_item;
				}
				else {
					deleted_item->parent->right = nullptr;
					delete deleted_item;
				}
			}
			else
				delete_one_child(deleted_item);
		}
		else if (((deleted_item->left != nullptr) && (deleted_item->right == nullptr)) || ((deleted_item->left == nullptr) && (deleted_item->right != nullptr)))
		{
			delete_one_child(deleted_item);
		}
		else
		{
			RNode* successor = this->find_successor(deleted_item->right);
			int temp = deleted_item->key;
			deleted_item->key = successor->key;
			successor->key = temp;
			delete_one_child(successor);
		}
	}
}

void RTree::replace_node(RNode* n, RNode* child) {
	child->parent = n->parent;
	if (n == n->parent->left) {
		n->parent->left = child;
	}
	else {
		n->parent->right = child;
	}
}

void RTree::delete_one_child(struct RNode* n)
{
	/*
	 * Условие: n имеет не более одного ненулевого потомка.
	 */
	if (n->color == node_colors::RED)
	{
		if (n == n->parent->left)
		{
			n->parent->left = nullptr;
		}
		else {
			n->parent->right = nullptr;
		}
	}
	else {
		struct RNode* child = (n->right == nullptr) ? n->left : n->right;
		if (child == nullptr)
		{
			delete_case1(n);
		}
		else
		{
			this->replace_node(n, child);
			if (n->color == node_colors::BLACK) {
				if (child->color == node_colors::RED)
					child->color = node_colors::BLACK;
				else
					this->delete_case1(child);
			}
		}
	}
	if (n == n->parent->left)
		n->parent->left = nullptr;
	else if (n == n->parent->right)
		n->parent->right = nullptr;
	delete n;
}

void RTree::delete_case1(RNode* n)
{
	if (n->parent != nullptr)
		this->delete_case2(n);
}

void RTree::delete_case2(RNode* n)
{
	RNode* s = this->sibling(n);

	if (s->color == node_colors::RED)
	{
		n->parent->color = node_colors::RED;
		s->color = node_colors::BLACK;
		if (n == n->parent->left)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
	}
	delete_case3(n);
}

void RTree::delete_case3(RNode* n)
{
	RNode* s = this->sibling(n);
	if (
		(n->parent->color == node_colors::BLACK) &&
		(s->color == node_colors::BLACK) &&
		(s->left == nullptr || (s->left->color == node_colors::BLACK)) &&
		(s->right == nullptr || (s->right->color == node_colors::BLACK))
		)
	{
		s->color = node_colors::RED;
		delete_case1(n->parent);
	}
	else
		delete_case4(n);
}

void RTree::delete_case4(RNode* n)
{
	RNode* s = this->sibling(n);
	if (
		(n->parent->color == node_colors::RED) &&
		(s->color == node_colors::BLACK) &&
		(s->left == nullptr || (s->left->color == node_colors::BLACK)) &&
		(s->right == nullptr || (s->right->color == node_colors::BLACK))
		)
	{
		s->color = node_colors::RED;
		n->parent->color = node_colors::BLACK;
	}
	else
		delete_case5(n);
}

void RTree::delete_case5(RNode* n)
{
	RNode* s = this->sibling(n);
	if (s->color == node_colors::BLACK) {
		if (
			(n == n->parent->left) &&
			(s->right == nullptr || (s->right->color == node_colors::BLACK)) &&
			(s->left != nullptr && (s->left->color == node_colors::RED))
			)
		{
			s->color = node_colors::RED;
			s->left->color = node_colors::BLACK;
			rotate_right(s);
		}
		else if (
			(n == n->parent->right) &&
			(s->left == nullptr || (s->left->color == node_colors::BLACK)) &&
			(s->right != nullptr && (s->right->color == node_colors::RED))
			)
		{
			s->color = node_colors::RED;
			s->right->color = node_colors::BLACK;
			rotate_left(s);
		}
	}
	delete_case6(n);
}

void RTree::delete_case6(RNode* n)
{
	RNode* s = this->sibling(n);
	s->color = n->parent->color;
	n->parent->color = node_colors::BLACK;

	if (n == n->parent->left) {
		s->right->color = node_colors::BLACK;
		rotate_left(n->parent);
	}
	else {
		s->left->color = node_colors::BLACK;
		rotate_right(n->parent);
	}
}

RTree::~RTree()
{
	if (this->root != nullptr)
	{
		this->recursive_delete(root);
	}
}

void RTree::recursive_delete(RNode* n)
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

std::string RTree::TestPrint(RNode* n) const
{
	std::stringstream buffer;
	buffer << n->key;
	if (n->color == node_colors::BLACK)
		buffer << "B";
	else
		buffer << "R";
	if (!(n->left == nullptr))
	{
		buffer << " LEFT ";
		buffer << TestPrint(n->left);
	}
	else
	{
		buffer << " LEFT_LIST ";
	}
	if (!(n->right == nullptr))
	{
		buffer << " RIGH ";
		buffer << TestPrint(n->right);
	}
	else
	{
		buffer << " RIGH_LIST ";
	}
	return buffer.str();
}

int RTree::calculate_height(RNode* n)
{
	int lh = 0, rh = 0;
	if (n->left != nullptr)
	{
		lh = calculate_height(n->left);
	}
	if (n->right != nullptr)
	{
		rh = calculate_height(n->right);
	}
	return std::max(lh, rh) + 1;
}

bool check_tree(RTree& rbt)
{
	RNode* root = rbt.root;
	bool c1 = check_case1(root);
	bool c2 = check_case2(root);
	bool c3 = check_case3(root);
	return c1 && c2 && c3;
}

bool check_case1(RNode* root)
{
	return root->color == node_colors::BLACK;
}

bool check_case2(RNode* n)
{
	node_colors rc, lc;
	bool ns, ls, rs;
	if (n->left == nullptr)
	{
		lc = node_colors::BLACK;
		ls = true;
	}
	else
	{
		lc = n->left->color;
		ls = check_case2(n->left);
	}
	if (n->right == nullptr)
	{
		rc = node_colors::BLACK;
		rs = true;
	}
	else
	{
		rc = n->right->color;
		rs = check_case2(n->right);
	}
	if (n->color == node_colors::BLACK)
	{
		ns = true;
	}
	else
	{
		ns = (lc == node_colors::BLACK && rc == node_colors::BLACK);
	}
	return ns && ls && rs;
}

bool check_case3(RNode* n)
{
	if (n == nullptr)
		return true;
	bool ns = (calculate_black_height(n->left) == calculate_black_height(n->right));
	bool ls = check_case3(n->left);
	bool rs = check_case3(n->right);
	return ns && ls && rs;
}

int calculate_black_height(RNode* n)
{
	if (n == nullptr)
		return 1;
	int lbh = calculate_black_height(n->left);
	int rbh = calculate_black_height(n->right);
	if (n->color == node_colors::BLACK)
		return (1 + std::max(lbh, rbh));
	return std::max(lbh, rbh);
}