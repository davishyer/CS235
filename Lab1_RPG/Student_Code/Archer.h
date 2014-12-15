#pragma once
#include "Fighter.h"
class Archer :
	public Fighter
{
public:
	Archer(string name, int maxhp, int st, int sp, int mag);//add the rest
	virtual ~Archer(void);
	//void regenerate();
	int getDamage();
	void reset();
	bool useAbility();

private:
	int ASpeed;
};

