#pragma once
#include<string>

using namespace std;

class Node :public NodeInterface
{

public:
	int item;
	int height;
	Node* RChild;
	Node* LChild;
	Node* parent;
	Node()
	{
		item = 0;
		height = 0;
		RChild = NULL;
		LChild = NULL;
		parent = NULL;
	}
	Node(int data)
	{
		item = data;
		height = 0;
		RChild = NULL;
		LChild = NULL;
		parent = NULL;
	}
	~Node() {}

	/*
	 * Returns the data that is stored in this node
	 *
	 * @return the data that is stored in this node.
	 */
	int getData()
	{
		return item;
	}

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return the left child of this node or null if it doesn't have one.
	 */
	NodeInterface * getLeftChild()
	{
		return LChild;
	}

	/*
	 * Returns the right child of this node or null if it doesn't have one.
	 *
	 * @return the right child of this node or null if it doesn't have one.
	 */
	NodeInterface * getRightChild()
	{
		return RChild;
	}

	/*
	 * Returns the height of this node. The height is the number of edges
	 * from this node to this nodes farthest child.
	 */
	int getHeight()
	{
		return height;
	}

};
