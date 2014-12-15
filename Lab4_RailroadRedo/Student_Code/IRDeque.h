#pragma once
#include "LinkedList.h"

using namespace std;

class IRDeque
{
	private:
		LinkedList<int> D;
	public:
		IRDeque()
		{

		}
		~IRDeque()
		{

		}

		void push(int i)
		{
			D.insertHead(i);
		}

		void popLeft()
		{
			D.remove(D.at(0));
		}

		void popRight()
		{
			D.remove(D.at(D.size() - 1));
		}

		int size()
		{
			return D.size();
		}

		int topLeft()
		{
			if(size() == 0)
			{
				return -1;
			}
			return D.at(0);
		}

		int topRight()
		{
			if(size() == 0)
			{
				return -1;
			}
			return D.at(D.size() - 1);
		}

		bool unique(int i)
		{
			if(D.contains(i))
			{
				return false;
			}
			return true;
		}
};
