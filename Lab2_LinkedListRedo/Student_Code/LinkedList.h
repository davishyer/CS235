#include <string>
#include "LinkedListInterface.h"
#include "Node.h"

using namespace std;

template<class T>
class LinkedList : public LinkedListInterface<T>
{
private:
	Node<T>* head;
	int number;
	bool contains(T value)
	{
		Node<T>* curr = head;
		while(curr != NULL)
		{
			if(curr->data == value)
			{
				return true;
			}
			curr = curr->next;
		}
		return false;
	}



public:

	LinkedList()
	{
		head = NULL;
		number = 0;
	}
	~LinkedList()
	{
		clear();
	}

	/*
		insertHead

		A node with the given value should be inserted at the beginning of the list.

		Do not allow duplicate values in the list.
	 */
	void insertHead(T value)
	{
		if(!contains(value))
		{
			Node<T>* temp = new Node<T>(value);
			temp->next = head;
			head = temp;
			number++;
		}
	}

	/*
		insertTail

		A node with the given value should be inserted at the end of the list.

		Do not allow duplicate values in the list.
	 */
	void insertTail(T value)
	{
		if(head == NULL)
		{
			insertHead(value);
			return;
		}
		if(!contains(value))
		{
			Node<T>* curr = head;
			while(curr->next != NULL)
			{
				curr = curr->next;
			}
			Node<T>* temp = new Node<T>(value);
			curr->next = temp;
			number++;
		}
	}

	/*
		insertAfter

		A node with the given value should be inserted immediately after the
		node whose value is equal to insertionNode.

		A node should only be added if the node whose value is equal to
		insertionNode is in the list. Do not allow duplicate values in the list.
	 */
	void insertAfter(T value, T insertionNode)
	{
		if(!contains(value))
		{
			if(contains(insertionNode))
			{
				Node<T>* curr = head;
				while(curr->data != insertionNode)
				{
					curr = curr->next;
				}
				Node<T>* temp = new Node<T>(value);
				temp->next = curr->next;
				curr->next = temp;
				number++;
			}
		}
	}

	/*
		remove

		The node with the given value should be removed from the list.

		The list may or may not include a node with the given value.
	 */
	void remove(T value)
	{
		if(contains(value))
		{
			Node<T>* curr = head;
			if(head->data == value)
			{
				head = head->next;
				delete curr;
				number--;
				return;
			}
			while(curr->next->data != value)
			{
				curr = curr->next;
			}
			Node<T>* temp = curr->next;
			curr->next = temp->next;
			delete temp;
			number--;
		}
	}

	/*
		clear

		Remove all nodes from the list.
	 */
	void clear()
	{
		while(head != NULL)
		{
			remove(head->data);
		}
	}

	/*
		at

		Returns the value of the node at the given index. The list begins at
		index 0.

		If the given index is out of range of the list, return NULL;
	 */
	T at(int index)
	{
		if(index >= 0 && index < number)
		{
			int counter = 0;
			Node<T>* curr = head;
			while(counter != index)
			{
				curr = curr->next;
				counter++;
			}
			return curr->data;
		}
		return NULL;
	}

	/*
		size

		Returns the number of nodes in the list.
	 */
	int size()
	{
		return number;
	}

};
