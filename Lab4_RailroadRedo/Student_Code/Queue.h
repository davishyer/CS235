#pragma once
#include "LinkedList.h"

using namespace std;

class Queue
{
	private:
		LinkedList<int> Q;
	public:
		Queue()
		{

		}
		~Queue()
		{

		}

		void push(int i)
		{
			Q.insertHead(i);
		}

		void pop()
		{
			Q.remove(Q.at(Q.size() - 1));
		}

		int size()
		{
			return Q.size();
		}

		int top()
		{
			if(size() == 0)
			{
				return -1;
			}
			return Q.at(Q.size() - 1);
		}

		bool unique(int i)
		{
			if(Q.contains(i))
			{
				return false;
			}
			return true;
		}
};
