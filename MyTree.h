#pragma once

template <typename T> 
class Tree final
{
private:
	T root;
	Tree* left;
	Tree* right;
public:
	Tree(const T& value)
		:
		root(value),
		left(nullptr),
		right(nullptr) {}
	~Tree() 
	{
		delete left; delete right;
	}
public:

	bool is_find(const T& value)
	{
		return find(value);
	}

	void insert(const T& value)
	{
		if (value < this->root)
		{
			if (this->left == nullptr)
			{
				this->left = new Tree(value);
			}
			else {
				left->insert(value);
			}
		}
		else if (value > root)
		{
			if (this->right == nullptr)
			{
				this->right = new Tree(value);
			}
			else
			{
				right->insert(value);
			}
		}
		else if (value == root)
			return;
	}
	Tree* find(const T& value, Tree* parent = nullptr)
	{
		if (this->root == value)
		{
			return this;
		}
		if (this->left != nullptr && this->left->root == value)
		{
			parent = this;
			return this->left;
		}
		if (this->right != nullptr && this->right->root == value) 
		{
			parent = this;
			return this->right;
		}
		if (this->left != nullptr)
			this->left->find(value);
		if (this->right != nullptr)
			this->right->find(value);
		return nullptr;
	}
	void erase(const T& value)
	{
		Tree* parent(0);
		Tree* element = find(value, parent);
		if (element == nullptr)
			return;
		else if (element->right == nullptr && element->left == nullptr)
		{
			delete element;
			element = nullptr;
			parent = nullptr;
			return;
		}
		else if ((element->right != nullptr && element->left == nullptr) || (element->right == nullptr && element->left != nullptr))
		{
			eraseNodeWithOneChild(parent, element);
			parent = nullptr;
			element = nullptr;
			return;
		}
		else
		{
			eraseNodeWithTwoChild(element);
		}

	}
private:
	Tree* findMinElement(Tree* element, Tree* parent = nullptr)
	{
		if (element->left->left == nullptr) {
			parent = element;
			return element->left;
		}
		findMinElement(element->left);
	}

	void eraseNodeWithTwoChild(Tree* element)
	{
		Tree* parent(nullptr);
		Tree* min_element;
		if (element->right->left == nullptr) {
			min_element = element->right->right;
			delete element->right;
			element->right = min_element;
			min_element = nullptr;
			return;
		}
		else
			min_element = findMinElement(element->right, parent);
		if (min_element->right == nullptr)
		{
			element->root = min_element->root;
			delete min_element;
			min_element = nullptr;
			return;
		}
		element->root = min_element->root;
		parent->left = min_element->right;
		delete min_element;
		min_element = nullptr;
	}
	void eraseNodeWithOneChild(Tree* parent, Tree* element)
	{
		if (element->left != nullptr) {
			if (parent->left == element)
			{
				parent->left = element->left;
			}
			else if (parent->right == element)
			{
				parent->right = element->left;
			}
		}
		else if (element->right != nullptr)
		{
			if (parent->left == element)
			{
				parent->left = element->right;
			}
			else if (parent->right == element)
			{
				parent->right = element->right;			
			}
		}
		delete element;
	}
};
