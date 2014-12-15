#include "Cleric.h"


Cleric::Cleric(string name, int maxhp, int st, int sp, int mag) : Fighter(name, maxhp, st, sp, mag)//add rest
{
	Mana = mag * 5;
	CurrentMana = Mana;
}

int Cleric::getDamage() 
{
	int damage = Magic;
	return damage;
}

Cleric::~Cleric(void)
{
}

void Cleric::regenerate()
{
	Fighter::regenerate();
	int fifth = Magic / 5;
	if(fifth > 1)
	{
		CurrentMana += fifth;
		if(CurrentMana > Mana)
		{
			CurrentMana = Mana;
		}
	}
	else
	{
		CurrentMana++;
		if(CurrentMana > Mana)
		{
			CurrentMana = Mana;
		}
	}
}

void Cleric::reset()
{
	Fighter::reset();
	
	CurrentMana = Mana;
}

bool Cleric::useAbility()
{
	bool used = false;
	if(CLERIC_ABILITY_COST <= CurrentMana)
	{
		used = true;
		int third = Magic / 3;
		if(third > 1)
		{
			Currenthp += third;
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

		CurrentMana -= CLERIC_ABILITY_COST;
	}
	
	return used;
}
