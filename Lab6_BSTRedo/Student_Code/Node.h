#include "NodeInterface.h"
#include <cstddef>

class Node : public NodeInterface
{
public:
	int data;
	Node* lChild;
	Node* rChild;

	Node()
	{
		data = -1;
		lChild = NULL;
		rChild = NULL;
	}
	Node(int dataIn)
	{
		data = dataIn;
		lChild = NULL;
		rChild = NULL;
	}
	~Node() {}

	/*
	 * Returns the data that is stored in this node
	 *
	 * @return the data that is stored in this node.
	 */
	int getData()
	{
		return data;
	}

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return the left child of this node or null if it doesn't have one.
	 */
	NodeInterface * getLeftChild()
	{
		return lChild;
	}

	/*
	 * Returns the right child of this node or null if it doesn't have one.
	 *
	 * @return the right child of this node or null if it doesn't have one.
	 */
	NodeInterface * getRightChild()
	{
		return rChild;
	}

};
