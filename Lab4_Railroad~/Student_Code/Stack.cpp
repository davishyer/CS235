#include "Stack.h"

bool Stack::stackPush(int car)
{
	S.insertHead(car);
	return true;
}

int Stack::stackSize()
{
	return S.size();
}

bool Stack::stackPop()
{
	if(S.size() != 0)
	{
		S.remove(S.at(0));
		return true;
	}
	return false;
}

int Stack::stackTop()
{
	if(S.size() == 0)
	{
		return -1;
	}
	return S.at(0);
}

bool Stack::uniqueStack(int car)
{
	if(S.size() == 0)
	{
		return true;
	}
	for(unsigned i = 0; i < S.size() - 1; i++)
	{
		if(S.at(i) == car)
		{
			return false;
		}
	}
	return true;
}

