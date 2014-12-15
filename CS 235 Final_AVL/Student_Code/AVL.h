//Davis Hyer
//CS 235 Spring Final 2014

#pragma once

#include "NodeInterface.h"
#include "Node.h"
#include "AVLInterface.h"
#include <iostream>

using namespace std;

class AVL : public AVLInterface
{
private:
	Node* head;
	Node* curr;
	Node* check;
	Node* look;
	Node* temp;
	int first;
	int firs;
	Node* removed;
	Node* previous;
	Node* replace;
	Node* rprevious;
	int start;


	void balance(Node* rotate)
	{
		if(rotate == NULL)
		{
			return;
		}
		if(rotate->LChild == NULL)
		{
			if(rotate->RChild == NULL)				//LEAF NODE
			{

			}
			else if(rotate->RChild->height > 0)
			{
				check = rotate;
				rotate = rotate->RChild;
				if(rotate->RChild != NULL)
				{
					//Right-Right
					if(rotate->LChild != NULL)
					{
						check->RChild = rotate->LChild;
						rotate->LChild->parent = check;
					}
					else
					{
						check->RChild = NULL;
					}
					if(check->item == head->item)
					{
						head = rotate;
						rotate->parent = NULL;
					}
					else
					{
						rotate->parent = check->parent;
						if(check->parent->RChild->item == check->item)
						{
							check->parent->RChild = rotate;
						}
						else
						{
							check->parent->LChild = rotate;
						}
					}
					rotate->LChild = check;
					check->parent = rotate;
					height(head);

				}
				else
				{
					//Right-Left
					rotate->LChild->RChild = rotate;
					rotate->parent = rotate->LChild;
					rotate->LChild->LChild = check;
					if(check->parent != NULL)
					{
						rotate->LChild->parent = check->parent;
						if(check->parent->LChild->item == check->item)
						{
							check->parent->LChild = rotate->LChild;
						}
						else
						{
							check->parent->RChild = rotate->LChild;
						}
					}
					else
					{
						rotate->LChild->parent = NULL;
						head = rotate->LChild;
					}
					check->parent = rotate->LChild;
					check->RChild = NULL;
					rotate->LChild = NULL;
					height(head);
				}
			}
		}
		else if(rotate->RChild == NULL)
		{
			if(rotate->LChild->height > 0)
			{
				check = rotate;
				rotate = rotate->LChild;
				if(rotate->LChild != NULL)
				{
					//Left-Left
					if(rotate->RChild != NULL)
					{
						check->LChild = rotate->RChild;
						rotate->RChild->parent = check;
					}
					else
					{
						check->LChild = NULL;
					}
					if(check->item == head->item)
					{
						head = rotate;
						rotate->parent = NULL;
					}
					else
					{
						rotate->parent = check->parent;
						if(check->parent->RChild->item == check->item)
						{
							check->parent->RChild = rotate;
						}
						else
						{
							check->parent->LChild = rotate;
						}
					}
					rotate->RChild = check;
					check->parent = rotate;
					height(head);
				}
				else
				{
					//Left-Right
					rotate->RChild->LChild = rotate;
					rotate->parent = rotate->RChild;
					rotate->RChild->RChild = check;
					if(check->parent != NULL)
					{
						rotate->RChild->parent = check->parent;
						if(check->parent->LChild->item == check->item)
						{
							check->parent->LChild = rotate->RChild;
						}
						else
						{
							check->parent->RChild = rotate->RChild;
						}
					}
					else
					{
						rotate->RChild->parent = NULL;
						head = rotate->RChild;
					}
					check->parent = rotate->RChild;
					check->LChild = NULL;
					rotate->RChild = NULL;
					height(head);
				}
			}
		}
		else if((rotate->LChild->height + 1) < rotate->RChild->height)
		{
			check = rotate;
			rotate = rotate->RChild;

			check->RChild = rotate->LChild;
			rotate->LChild->parent = check;
			if(check->parent != NULL)
			{
				rotate->parent = check->parent;
				if(check->parent->RChild->item == check->item)
				{
					check->parent->RChild = rotate;
				}
				else
				{
					check->parent->LChild = rotate;
				}
			}
			else
			{
				rotate->parent = NULL;
				head = rotate;
			}
			rotate->LChild = check;
			check->parent = rotate;
			height(head);
		}
		else if((rotate->LChild->height - 1) > rotate->RChild->height)
		{
			check = rotate;
			rotate = rotate->LChild;
			check->LChild = rotate->RChild;
			rotate->RChild->parent = check;
			if(check->parent != NULL)
			{
				rotate->parent = check->parent;
				if(check->parent->RChild->item == check->item)
				{
					check->parent->RChild = rotate;
				}
				else
				{
					check->parent->LChild = rotate;
				}
			}
			else
			{
				rotate->parent = NULL;
				head = rotate;
			}
			rotate->RChild = check;
			check->parent = rotate;
			height(head);
		}

		if(rotate->parent == NULL)
		{
			return;
		}
		else
		{
			rotate = rotate->parent;
			balance(rotate);
		}
	}


int max(int x, int y)
{
	if(x >= y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

int height(Node* n)
{
	if(n->RChild == NULL)
	{
		if(n->LChild == NULL)
		{
			n->height = 0;
			return n->height;
		}
		n->height = (height(n->LChild) + 1);
		return n->height;
	}
	else if(n->LChild == NULL)
	{
		n->height = (height(n->RChild) + 1);
		return n->height;
	}
	else
	{
		n->height = ((max(height(n->LChild), height(n->RChild)) + 1));
		return n->height;
	}
	cout << "\n----------------------\nSHOULDN'T HAVE REACHED HERE IN HEIGHT\n----------------------\n";
	return 0;
}



	void rotateHeight(Node* n)
	{
		n->parent->height = n->height + 1;
	}

	void changeHeight(Node* n)
	{
		while(n->parent != NULL)
		{
			if((n->height + 1) > n->parent->height)
			{
				n->parent->height += 1;
			}
			n = n->parent;
		}
	}

	void empty()
	{
		if(head != NULL)
		{
			while(head != NULL)
			{
				remove(head->item);
			}
		}
	}

	bool findRemove(int search)
	{
		if(head == NULL)
		{
			return false;
		}
		if(firs == 0)
		{
			removed = head;
			previous = NULL;
			firs = 1;
		}
		if(removed->item == search)
		{
			firs = 0;
			return true;
		}
		if(search > removed->item)
		{
			previous = removed;
			if(removed->RChild == NULL)
			{
				firs = 0;
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
				firs = 0;
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
	AVL()
	{
		head = NULL;
		curr = NULL;
		removed = NULL;
		previous = NULL;
		replace = NULL;
		rprevious = NULL;
		check = NULL;
		look = NULL;
		start = 0;
		first = 0;
		firs = 0;
		temp = NULL;
	}
	~AVL()
	{
		empty();
	}

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	 * Returns the root node for this tree
	 *
	 * @return the root node for this tree.
	 */
	NodeInterface * getRootNode()
	{
		if(head != NULL)
		{
			return head;
		}
		return NULL;
	}

	/*
	 * Attempts to add the given int to the AVL tree
	 * Rebalances the tree if data is successfully added
	 *
	 * @return true if added
	 * @return false if unsuccessful (i.e. the int is already in tree)
	 */
	bool add(int data)
	{
		if(head == NULL)				//Add new head, no rebalance needed
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
		if(data == curr->item)			//already exists, no rebalance needed
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
			else						//adding new leaf node, rebalance needed!
			{
				Node* n = new Node(data);
				curr->RChild = n;
				n->parent = curr;
				start = 0;
				height(head);
				first = 0;
				balance(n);
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
			else						//adding new leaf node, rebalance needed!
			{
				Node* n = new Node(data);
				curr->LChild = n;
				n->parent = curr;
				start = 0;
				height(head);
				first = 0;
				balance(n);
				return true;
			}
		}
		return false;
	}

	/*
	 * Attempts to remove the given int from the AVL tree
	 * Rebalances the tree if data is successfully removed
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
						if(previous->RChild == NULL)
						{
							previous->height = 0;
						}
						height(head);
						balance(previous);
						delete removed;
						firs = 0;
						return true;
					}
					else
					{
						previous->RChild = NULL;
						if(previous->LChild == NULL)
						{
							previous->height = 0;
						}
						height(head);
						balance(previous);
						delete removed;
						firs = 0;
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
						removed->RChild->parent = previous;
						previous->LChild = removed->RChild;
						height(head);
						removed->LChild = NULL;
						removed->RChild = NULL;
						balance(previous);
						delete removed;
						firs = 0;
						return true;
					}
					removed->RChild->parent = previous;
					previous->RChild = removed->RChild;
					height(head);
					removed->LChild = NULL;
					removed->RChild = NULL;
					balance(previous);
					delete removed;
					firs = 0;
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
				height(head);
				balance(replace);
				delete replace;
				firs = 0;
				return true;
			}
			if(replace->LChild != NULL)
			{
				replace->LChild->parent = rprevious;
				rprevious->RChild = replace->LChild;
				removed->item = replace->item;
				height(head);
				replace->LChild = NULL;
				replace->RChild = NULL;
				balance(rprevious->RChild);
				delete replace;
				firs = 0;
				return true;
			}
			else
			{
				rprevious->RChild = NULL;
				if(rprevious->LChild == NULL)
				{
					rprevious->height = 0;
				}
				removed->item = replace->item;
				height(head);
				replace->LChild = NULL;
				replace->RChild = NULL;
				balance(rprevious);
				delete replace;
				firs = 0;
				return true;
			}
		}

		return false;
	}

	/*
	 * ROTATIONS:
	 * 			LEFT
	 *
	 * 				IDENTIFY NODES TO ROTATE
	 *
	 * 				ROT.RIGHT=CUR.LEFT
	 * 				CUR.LEFT=ROT
	 * 				CUR=ROT
	 *
	 *
	 *
	 *
	 * 			RIGHT
	 *
	 *
	 *
	 */
};
