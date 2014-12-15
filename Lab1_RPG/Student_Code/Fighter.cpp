#include "Fighter.h"


Fighter::Fighter(string name, int maxhp, int st, int sp, int mag)
{
	Name = name;
	Maxhp = maxhp;
	Strength = st;
	Speed = sp;
	Magic = mag;
}


Fighter::~Fighter(void)
{
}

string Fighter :: getName()
{
	return Name;
}

int Fighter :: getMaximumHP()
{
	return Maxhp;
}

int Fighter :: getCurrentHP()
{
	return Currenthp;
}

int Fighter :: getStrength()
{
	return Strength;
}

int Fighter :: getSpeed()
{
	return Speed;
}

int Fighter :: getMagic()
{
	return Magic;
}

void Fighter :: takeDamage(int damage)
{
	damage = damage - (Speed / 4);
	if(damage < 1)
	{
		damage = 1;
	}
	Currenthp -= damage;
}

void Fighter :: regenerate()
{
	int sixth = Strength / 6;
	if(sixth > 0)
	{
		Currenthp += sixth;
		if(Currenthp > Maxhp)
		{
			Currenthp = Maxhp;
		}
	}
	else
	{
		Currenthp++;
		if(Currenthp > Maxhp)
		{
			Currenthp = Maxhp;
		}
	}

}


void Fighter :: reset()
{
	Currenthp = Maxhp;
}