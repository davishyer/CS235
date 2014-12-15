#include "Deque.h"

bool Deque::addLeft(int car)
{
	De.insertHead(car);
	return true;
}

bool Deque::addRight(int car)
{
	De.insertTail(car);
	return true;
}

bool Deque::removeLeft()
{
	if(De.size() != 0)
	{
		De.remove(D.at(0));
		return true;
	}
	return false;
}

bool Deque::removeRight()
{
	if(De.size() != 0)
	{
		De.remove(De.at(De.size() - 1));
		return true;
	}
	return false;
}

int Deque::showLeft()
{
	if(De.size() == 0)
	{
		return -1;
	}
	return De.at(0);
}

int Deque::showRight()
{
	if(De.size() == 0)
	{
		return -1;
	}
	return De.at(De.size() - 1);
}

int Deque::dequeSize()
{
	return De.size();
}

bool Deque::uniqueDeque(int car)
{
	if(De.size() == 0)
	{
		return true;
	}
	for(unsigned i = 0; i < De.size() - 1; i++)
	{
		if(De.at(i) == car)
		{
			return false;
		}
	}
	return true;
}
