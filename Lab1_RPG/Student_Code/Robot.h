#pragma once
#include "Fighter.h"
#include <cmath>
class Robot :
	public Fighter
{
public:
	Robot(string name, int maxhp, int st, int sp, int mag);//add the rest
	virtual ~Robot(void);
	//void regenerate();
	int getDamage();
	void reset();
	bool useAbility();

private:
	int Power;
	int CurrentPower;
	int BonusDamage;
};

