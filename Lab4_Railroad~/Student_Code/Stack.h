#pragma once
#include "Linked_List.h"
using namespace std;

class Stack
{
	private:
		LinkedList <int> S;

	public:
		bool stackPush(int car);
		int stackSize();
		bool stackPop();
		int stackTop();
		bool uniqueStack(int car);
};
