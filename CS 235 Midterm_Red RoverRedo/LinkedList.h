/*
 * Davis Hyer
 * CS 235 Spring 2014 Midterm
 */
#pragma once
#include <string>
#include <iostream>

using namespace std;

template <class T>
class LinkedList
{

public:
	struct Node
	{
		string name;
		int str;
		int spd;
		Node* next;
		Node* previous;

		Node()
		{
			next = NULL;
			previous = NULL;
			name = NULL;
			str = 0;
			spd = 0;
		};
		~Node() {};
		Node(string NAME, int STR, int SPD)
		{
			name = NAME;
			str = STR;
			spd = SPD;
			next = NULL;
			previous = NULL;
		};
	};
	Node* head;
	Node* tail;
	int number;

	LinkedList(void)
	{
		head = NULL;
		tail = NULL;
		number = 0;
	};
	~LinkedList(void)
	{
		clear();
	};

	/*
		insertHead

		A node with the given value should be inserted at the beginning of the list.

		Do not allow duplicate values in the list.
	 */
	void insertHead(string value, int Str, int Spd)
	{
		if(number == 0)
		{
			head = new Node(value, Str, Spd);
			tail = head;
			number++;
			return;
		}

		Node* n = head;
		for(int i = 0; i < number; i++)				//Checking if it already exists
		{
			if(n->name == value) return;
			else if(n != NULL) n = n->next;
			else break;
		}

		Node* h = new Node(value, Str, Spd);		//Adding the new head
		h->next = head;
		head->previous = h;
		head = h;

		number++;

		return;
	}

	/*
		insertTail

		A node with the given value should be inserted at the end of the list.

		Do not allow duplicate values in the list.
	 */
	void insertTail(string value, int Str, int Spd)
	{
		Node* n = head;

		for(int i = 0; i < number; i++)				//Checking if it already exists
		{
			if(n->name == value) return;
			else if(n != NULL) n = n->next;
			else break;
		}

		Node* t = new Node(value, Str, Spd);						//Adding the new tail
		if(number == 0)
		{
			head = t;
			tail = t;
			number++;
			return;
		}

			tail->next = t;
			t->previous = tail;
			tail = t;
			tail->next = NULL;

			number++;
			return;
	}


	/*
		insertAfter

		A node with the given value should be inserted immediately after the
		node whose value is equal to insertionNode.

		A node should only be added if the node whose value is equal to
		insertionNode is in the list. Do not allow duplicate values in the list.
	 */
	void insertAfter(string value, string insertionNode, int Str, int Spd)
	{
		if(number == 0) return;

		Node* n = head;
		for(int i = 0; i < number; i++)				//Checking if it already exists
		{
			if(n->name == value) return;
			else if(n != NULL) n = n->next;
			else break;
		}

		Node* current = head;						//The new node is unique
		for(int i = 0; i < number; i++)
		{
			if(current->name == insertionNode)
			{
				if(current == tail)
				{
					insertTail(value, Str, Spd);
					return;
				}
				Node* m = new Node(value, Str, Spd);
				m->next = current->next;
				current->next->previous = m;
				current->next = m;
				m->previous = current;
				number++;
				return;
			}
			else if(current->next != NULL)
			{
				current = current->next;
			}
			else
			{
				return;								//InsertionNode not found
			}
		}

	}

	/*
		remove

		The node with the given value should be removed from the list.

		The list may or may not include a node with the given value.
	 */
	void remove(string value)
	{
		if(number == 0) return;
		Node* n = head;
		if(n == NULL)
		{
			return;
		}

		for(int i = 1; i <= number; i++)
		{
			if(n->name == value) break;
			else if(n->next != NULL) n = n->next;		//CHECK IF N IS IN SCOPE
			else return;
		}

		if(number == 1)
		{
			clear();
			return;
		}

		Node* current = head;
		while(current->next != NULL)
		{
			if(n == NULL)
			{
				cout << "ATTEMPT!!!" << endl;
			}

			if(value == head->name)
			{
				n = head;
				head = head->next;
				head->previous = NULL;
				delete n;
				number--;
				return;
			}

			if(current->next->name == value)
			{
				if(current->next == tail)
				{
					n = tail;
					tail = current;
					delete n;
					tail->next = NULL;
					number--;
					return;
				}

				current->next = n->next;
				n->next->previous = current;
				delete n;
				number--;
				return;
			}
			else
			{
				current = current->next;
			}
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
			Node* n = head;
			head = n->next;
			delete n;
			number--;
		}

		head = NULL;
		tail = NULL;
	}

	/*
		at

		Returns the value of the node at the given index. The list begins at
		index 0.

		If the given index is out of range of the list, return NULL;
	 */
	string atName(int index)
	{
		if(index < 0) return NULL;
		if(number == 0) return NULL;
		if(index + 1 > number) return NULL;
		Node* current = head;
		if(index == 0) return head->name;

		for(int i = 0; i < index; i++)
		{
			if(current->next != NULL) current = current->next;
			else return NULL;
		}

		return current->name;
	}

	int atStr(string name)
	{
		if(number == 0) return 0;

		Node* n = head;
		for(int i = 0; i < number; i++)				//Checking if it already exists
		{
			if(n->name == name) return n->str;
			else if(n != NULL) n = n->next;
			else break;
		}
		return 0;
	}

	int atSpd(string name)
	{
		if(number == 0) return 0;

		Node* n = head;
		for(int i = 0; i < number; i++)
		{
			if(n->name == name) return n->spd;
			else if(n != NULL) n = n->next;
			else break;
		}
		return 0;
	}

	int rightStr(string name)
	{
		Node* n = head;
		for(int i = 0; i < number; i++)
		{
			if(n->name == name) return n->next->str;
			else if(n != NULL) n = n->next;
			else break;
		}
		return 0;
	}

	int leftStr(string name)
	{
		Node* n = head;
		for(int i = 0; i < number; i++)
		{
			if(n->next->name == name) return n->str;
			else if(n != NULL) n = n->next;
			else break;
		}
		return 0;
	}

	string nextName(string name)
	{
		Node* n = head;
		for(int i = 0; i < number; i++)
		{
			if(n->name == name) return n->next->name;
			else if(n != NULL) n = n->next;
			else break;
		}
		return NULL;
	}

	string prevName(string name)
	{
		Node* n = head;
		for(int i = 0; i < number; i++)
		{
			if(n->next->name == name) return n->name;
			else if(n != NULL) n = n->next;
			else break;
		}
		return NULL;
	}

	bool exists(string name)
	{
		Node* n = head;
		for(int i = 0; i < number; i++)
		{
			if(n->name == name) return true;
			else if(n->next != NULL) n = n->next;
			else return false;
		}
		return false;
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
