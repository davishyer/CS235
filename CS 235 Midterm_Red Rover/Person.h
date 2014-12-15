/*
 * Davis Hyer
 * CS 235 Spring 2014 Midterm
 */
#include "LinkedList.h"

using namespace std;
class Person
{
private:
	LinkedList<string> person;
public:
	bool addNew(string name, int str, int spd)	//create new player
	{
		person.insertTail(name, str, spd);
		return true;
	}
	string getName(int index)			//name at index of player
	{
		return person.atName(index);
	}
	int getSpeed(string name)			//speed of certain player
	{
		return person.atSpd(name);
	}
	int getStrength(string name)		//strength of certain player
	{
		return person.atStr(name);
	}
	int getSize()						//size of the team/roster
	{
		return person.size();
	}
	void erase(string name)				//remove a certain player
	{
		person.remove(name);
	}
	void empty()						//clear the linked list
	{
		person.clear();
	}
	bool tailCase(string name)			//are we running at the tail?
	{
		if(person.atName(person.size() - 1) == name)
		{
			return true;
		}
		return false;
	}
	int strRight(string name)			//strength of the player to the right
	{
		return person.rightStr(name);
	}
	int strLeft(string name)			//strength of the player to the left
	{
		return person.leftStr(name);
	}
	void taken(string name, string after, int str, int spd)	//player will switch teams
	{
		person.insertAfter(name, after, str, spd);
	}
	string next(string name)			//returns the name of the player next to the current
	{
		return person.nextName(name);
	}
	string prev(string name)			//returns the name of the player previous to the current
	{
		return person.prevName(name);
	}
	bool nameExists(string name)		//checks if the given name exists
	{
		if(person.exists(name))
		{
			return true;
		}
		return false;
	}
};
