#include "Robot.h"


Robot::Robot(string name, int maxhp, int st, int sp, int mag) : Fighter(name, maxhp, st, sp, mag)//add rest
{
	Power = mag * 2;
	BonusDamage = 0;
}

int Robot::getDamage() 
{
	int damage = Strength + BonusDamage;
	return damage;
}

void Robot::reset()
{
	Fighter::reset();
	CurrentPower = Power;
	BonusDamage = 0;
}

bool Robot::useAbility()
{
	bool used = false;
	if(ROBOT_ABILITY_COST <= CurrentPower)
	{
		used = true;
		BonusDamage = (Strength * (pow((((double)CurrentPower / Power)), 4)));
		CurrentPower -= ROBOT_ABILITY_COST;
	}
	else
	{
		BonusDamage = 0;
	}

	return used;
}

Robot::~Robot(void)
{
}
