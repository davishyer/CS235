#include "BSTInterface.h"
#include "Node.h"
#include <cstddef>
#include <iostream>

using namespace std;

class BST : public BSTInterface
{
private:
	Node* root;

	bool contains(int check, Node* head)
	{
		if(head != NULL)
		{
			if(head->data == check)
			{
				return true;
			}
			else if(head->data > check)
			{
				if(contains(check, head->lChild))
				{
					return true;
				}
			}
			else if(head->data < check)
			{
				if(contains(check, head->rChild))
				{
					return true;
				}
			}
		}
		return false;
	}

	Node* recAdd(int x, Node* curr)
	{
		if(curr == NULL)
		{
			return new Node(x);
		}
		else if(curr->data < x)
		{
			curr->rChild = recAdd(x, curr->rChild);
			return curr;
		}
		else if(curr->data > x)
		{
			curr->lChild = recAdd(x, curr->lChild);
			return curr;
		}
		return NULL;
	}

	Node* recRem(int x, Node* curr)
	{
		if(curr->data > x)
		{
			curr->lChild = recRem(x, curr->lChild);
			return curr;
		}
		else if(curr->data < x)
		{
			curr->rChild = recRem(x, curr->rChild);
			return curr;
		}
		else if(curr->data == x)
		{
			if(curr->lChild != NULL)
			{
				curr->lChild = iOP(curr->lChild, curr);
				return curr;
			}
			else
			{
				Node* temp = curr->rChild;
				delete curr;
				return temp;
			}
		}
		return NULL;
	}

	Node* iOP(Node* curr, Node* toRemove)
	{
		if(curr->rChild != NULL)
		{
			curr->rChild = iOP(curr->rChild, toRemove);
			return curr;
		}
		else
		{
			toRemove->data = curr->data;
			Node* temp = curr->lChild;
			delete curr;
			return temp;
		}
		return NULL;
	}

public:
	BST()
	{
		root = NULL;
	}
	~BST()
	{
		clear();
	}

	/*
	 * Returns the root node for this tree
	 *
	 * @return the root node for this tree.
	 */
	NodeInterface * getRootNode()
	{
		return root;
	}
	/*
	 * Attempts to add the given int to the BST tree
	 *
	 * @return true if added
	 * @return false if unsuccessful (i.e. the int is already in tree)
	 */
	bool add(int data)
	{
		if(!contains(data, root))
		{
			root = recAdd(data, root);
			return true;
		}
		return false;
	}

	/*
	 * Attempts to remove the given int from the BST tree
	 *
	 * @return true if successfully removed
	 * @return false if remove is unsuccessful(i.e. the int is not in the tree)
	 */
	bool remove(int data)
	{
		if(contains(data, root))
		{
			root = recRem(data, root);
			return true;
		}
		return false;
	}
	/*
	 * Removes all nodes from the tree, resulting in an empty tree.
	 */
	void clear()
	{
		while(root != NULL)
		{
			remove(root->data);
		}
	}
};
