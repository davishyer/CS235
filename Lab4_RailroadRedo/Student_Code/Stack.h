#pragma once
#include "LinkedList.h"

using namespace std;

class Stack
{
	private:
		LinkedList<int> S;
	public:
		Stack()
		{

		}
		~Stack()
		{

		}

		void push(int i)
		{
			S.insertHead(i);
		}

		void pop()
		{
			S.remove(S.at(0));
		}

		int size()
		{
			return S.size();
		}

		int top()
		{
			if(size() == 0)
			{
				return -1;
			}
			return S.at(0);
		}

		bool unique(int i)
		{
			if(S.contains(i))
			{
				return false;
			}
			return true;
		}
};
