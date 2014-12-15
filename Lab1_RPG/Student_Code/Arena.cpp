#include "Arena.h"


Arena::Arena(void)
{
}


Arena::~Arena(void)
{
}

bool Arena::addFighter(string info)
{
	stringstream ss(info);
	string name;
	string type;
	int maxhp;
	int st;
	int sp;
	int mag;
	bool pass = true;
	bool add = true;
	if(ss >> name >> type >> maxhp >> st >> sp >> mag)
	{
		if(type != "R" && type != "C" && type != "A")
		{
			return false;
		}
	
		if(maxhp < 1|| st < 1 || sp < 1 || mag < 1)
		{
			return false;
		}

		if(!ss.eof()){
			return false;
		}

		if(pass == true)
		{
			if(Colosseum.empty())
			{
				add = true;
			}

			else
			{
				for(int i = 0; i < Colosseum.size(); i++)
				{
					if(name == Colosseum[i]->getName())
					{
						add = false;
					}
				}
			}

			if(add == true)
			{
				if(type == "C")
				{
					FighterInterface* c = new Cleric(name, maxhp, st, sp, mag);
					Colosseum.push_back(c);
				}
				else if(type == "A")
				{
					FighterInterface* a = new Archer(name, maxhp, st, sp, mag);
					Colosseum.push_back(a);
				}
				else if(type == "R")
				{
					FighterInterface* r = new Robot(name, maxhp, st, sp, mag);
					Colosseum.push_back(r);
				}
			}
		}
	}
	else
	{
		return false;
	}
	return add;
}

bool Arena::removeFighter(string name)
{
	bool found = false;
	if(Colosseum.empty())
	{
		found = false;
	}
	else
	{
		for(int i = 0; i < Colosseum.size(); i++)
		{
			if(name == Colosseum[i]->getName())
			{
				found = true;
				Colosseum.erase(Colosseum.begin() + i);
				return found;
			}
		}
	}

	return found;
}

FighterInterface* Arena::getFighter(string name)
{
	for(int i = 0; i < Colosseum.size(); i++)
	{
			if(name == Colosseum[i]->getName())
			{
				return Colosseum[i];
			}
	}
		return NULL;
}

int Arena::getSize()
{
	int size = Colosseum.size();
	return size;
}
