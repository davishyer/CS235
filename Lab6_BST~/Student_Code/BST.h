#pragma once

#include "BSTInterface.h"
#include "Node.h"

using namespace std;

class BST : public BSTInterface
{
private:
	Node* head;
	Node* removed;
	Node* previous;
	Node* replace;
	Node* rprevious;
	int start;
	int first;
	Node* curr;

	void empty(Node* n)
	{
		while(head != NULL)
		{
			remove(head->item);
		}
	}

	bool findRemove(int search)
	{
		if(head == NULL)
		{
			return false;
		}
		if(first == 0)
		{
			removed = head;
			previous = NULL;
			first = 1;
		}
		if(removed->item == search)
		{
			first = 0;
			return true;
		}
		if(search > removed->item)
		{
			previous = removed;
			if(removed->RChild == NULL)
			{
				return false;
			}
			removed = removed->RChild;
			if(findRemove(search))
			{
				return true;
			}
			return false;
		}
		if(search < removed->item)
		{
			previous = removed;
			if(removed->LChild == NULL)
			{
				return false;
			}
			removed = removed->LChild;
			if(findRemove(search))
			{
				return true;
			}
			return false;
		}

		return false;
	}

	void findReplace()
	{
		if(replace->RChild != NULL)
		{
			rprevious = replace;
			replace = replace->RChild;
			findReplace();
		}
		return;
	}

public:
	BST()
	{
		head = NULL;
		removed = NULL;
		previous = NULL;
		replace = NULL;
		rprevious = NULL;
		curr = NULL;
		start = 0;
		first = 0;
	}
	virtual ~BST() {}

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	 * Returns the root node for this tree
	 *
	 * @return the root node for this tree.
	 */
	Node* getRootNode()
	{
		if(head != NULL)
		{
			return head;
		}
		return NULL;
	}

	/*
	 * Attempts to add the given int to the BST tree
	 *
	 * @return true if added
	 * @return false if unsuccessful (i.e. the int is already in tree)
	 */
	bool add(int data)
	{
		if(head == NULL)
		{
			Node* n = new Node(data);
			head = n;
			return true;
		}
		if(start == 0)
		{
			curr = head;
			start = 1;
		}
		if(data == curr->item)
		{
			start = 0;
			return false;
		}
		if(data > curr->item)
		{
			if(curr->RChild != NULL)
			{
				curr = curr->RChild;
				if(add(data))
				{
					return true;
				}
				return false;
			}
			else
			{
				Node* n = new Node(data);
				curr->RChild = n;
				n->RChild = NULL;
				n->LChild = NULL;
				start = 0;
				return true;
			}
		}
		else if(data < curr->item)
		{
			if(curr->LChild != NULL)
			{
				curr = curr->LChild;
				if(add(data))
				{
					return true;
				}
				return false;
			}
			else
			{
				Node* n = new Node(data);
				curr->LChild = n;
				start = 0;
				return true;
			}
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
		if(findRemove(data))
		{
			if(removed->LChild == NULL && removed->RChild == NULL)
			{
				if(previous != NULL)
				{
					if(previous->LChild != NULL && previous->LChild->item == data)
					{
						previous->LChild = NULL;
						delete removed;
						return true;
					}
					else
					{
						previous->RChild = NULL;
						delete removed;
						return true;
					}
				}
				head = NULL;
				delete removed;
				return true;
			}

			if(removed->LChild == NULL)
			{
				if(previous != NULL)
				{
					//check which child null check
					if(previous->LChild != NULL && previous->LChild->item == data)
					{
						previous->LChild = removed->RChild;
						removed->LChild = NULL;
						removed->RChild = NULL;
						delete removed;
						return true;
					}
					previous->RChild = removed->RChild;
					removed->LChild = NULL;
					removed->RChild = NULL;
					delete removed;
					return true;
				}
				head = removed->RChild;
				delete removed;
				return true;
			}

			replace = removed->LChild;
			rprevious = NULL;
			findReplace();
			if(rprevious == NULL)
			{
				removed->item = replace->item;
				removed->LChild = replace->LChild;
				delete replace;
				return true;
			}
			if(replace->LChild != NULL)
			{
				rprevious->RChild = replace->LChild;
				removed->item = replace->item;
				replace->LChild = NULL;
				replace->RChild = NULL;
				delete replace;
				return true;
			}
			else
			{
				rprevious->RChild = NULL;
				removed->item = replace->item;
				replace->LChild = NULL;
				replace->RChild = NULL;
				delete replace;
				return true;
			}
		}

		return false;
	}

	/*
	 * Removes all nodes from the tree, resulting in an empty tree.
	 */
	void clear()
	{
		if(head == NULL)
		{
			return;
		}
		while(head != NULL)
		{
			remove(head->item);
		}
		return;
	}
};
