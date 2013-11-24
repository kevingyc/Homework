#include"corchardunit.h"
#include<iostream>
using namespace std;

COrchardUnit::~COrchardUnit()
{
	
}


const int COrchardUnit::GetState()
{
	return state_;
}

const int COrchardUnit::GetDamege()
{
	return damage_level_;
}

/*
 * PlayerVisit : when player visit this unit
 */
void COrchardUnit::PlayerVisit(CPlayer &player)
{
	if(player.GetIdentifier() == owner_)	
	{
		if(state_ != 4) /* can't harvest */
		{
			cout << "Do you want to SEEDING this Unit?(y/n) ";
			char choice;
			cin >> choice;
			if(choice == 'y')
			{
				player.AddMoney(-1 * seeding_price_);
				state_++;
				cout << "Spend " << seeding_price_ << " for SEEDING..... ";
			}

		}	
		else /* can harvest */
		{

			int pass = rand() % (damage_level_ + 1);

			if(pass == 0) /* harvest success */
			{
				cout << "harvest, add money " << harvest_price_<< endl;			
				player.AddMoney(harvest_price_);
			}
			else /* harvest failure */
			{
				cout << "harvest failure....." << endl;
			}
			damage_level_ = 0;	
			state_ = 0;
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
		if(pass == 1) /* put bug success */
		{
			if(damage_level_ < 4 && state_ != 0)
			{
				cout << "put bug...." << endl;
				damage_level_++;
			}
		}
		else /* put bug failure*/
		{
			cout << "nothing to happen...." << endl;
		}
	}	
}

/*
 * Turn : every turn change on this unit	
 */
void COrchardUnit::Turn(){}
/*
 * Reset : when owner is break, this unit will reset
 */
void COrchardUnit::Reset()
{
	owner_ = 0;
	state_ = 0;
	damage_level_ = 0;
}
