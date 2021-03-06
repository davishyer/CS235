#pragma once
#include "Linked_List.h"
//using namespace std;

class Deque
{
	private:
		LinkedList<int> De;
		
	public:
		bool addLeft(int car);
		bool addRight(int car);
		bool removeLeft();
		bool removeRight();
		int showLeft();
		int showRight();
		int dequeSize();
		bool uniqueDeque(int car);
};
