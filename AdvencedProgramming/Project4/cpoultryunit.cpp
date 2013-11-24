#include"cpoultryunit.h"
#include<iostream>
using namespace std;

CPoultryUnit::~CPoultryUnit()
{
	
}

const int CPoultryUnit::GetEggNumber()
{
	return egg_number_;
}

/*
 * PlayerVisit : when player visit this unit
 */
void CPoultryUnit::PlayerVisit(CPlayer &player)
{
	if(player.GetIdentifier() == owner_)	
	{
		if(egg_number_ == 0) /* can't harvest */
		{
			cout << "SEEDING~~" << endl;
			player.AddMoney(-1 * seeding_price_);
		}	
		else /* can harvest */
		{
			cout << "harvest, add money " << harvest_price_ * egg_number_ << endl;
			player.AddMoney(harvest_price_ * egg_number_);
			egg_number_ = 0;	
		}
	}
	else if(owner_ == -1) /* no owned */
	{
		cout << "Do you want to buy this Unit?(y/n) ";
		char choice;
		cin >> choice;
		if(choice == 'y')
		{
			player.AddMoney(-1 * buy_price_);
			owner_ = player.GetIdentifier();	
			player.SetOwned(player.GetOwned() + 1);
			cout << "Spend " << buy_price_ << " for BUY this Unit..... ";
		}
	}
	else /* others owned */
	{
		int pass = rand() % 2;
		if(pass == 1) /* steal success */
		{
			cout << "be stool.... decrease " << egg_number_ / 2;
			egg_number_ /= 2;
		}
		else /* steal failure*/
		{
			cout << "nothing to happen...." << endl;
		}
	}
}

/*
 * Turn : every turn change on this unit	
 */
void CPoultryUnit::Turn()
{
	if(owner_ != -1)
	{
		egg_number_++;
	}
}
/*
 * Reset : when owner is break, this unit will reset
 */
void CPoultryUnit::Reset()
{
	owner_ = -1;
	egg_number_ = 0;
}
