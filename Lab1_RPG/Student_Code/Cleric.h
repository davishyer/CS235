#include "Fighter.h"
#pragma once
class Cleric :
	public Fighter
{
public:
	Cleric(string name, int maxhp, int st, int sp, int mag);//add the rest
	virtual ~Cleric(void);
	void regenerate();
	int getDamage();
	void reset();
	bool useAbility();

private:
	int Mana;
	int CurrentMana;
};

