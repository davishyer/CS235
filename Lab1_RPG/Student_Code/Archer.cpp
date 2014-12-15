#include "Archer.h"


Archer::Archer(string name, int maxhp, int st, int sp, int mag) : Fighter(name, maxhp, st, sp, mag)//add rest
{
	ASpeed = sp;
}

int Archer::getDamage() 
{
	int damage = Speed;
	return damage;
}

void Archer::reset()
{
	Fighter::reset();
	Speed = ASpeed;
}

bool Archer::useAbility()
{
	Speed++;
	bool used = true;
	return used;
}


Archer::~Archer(void)
{
}
