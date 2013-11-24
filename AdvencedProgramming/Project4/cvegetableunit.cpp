#include"cvegetableunit.h"
#include<iostream>
using namespace std;

CVegetableUnit::~CVegetableUnit()
{
	
}


const bool CVegetableUnit::GetVGState()
{
	return vg_state_;
}

/*
 * PlayerVisit : when player visit this unit
 */
void CVegetableUnit::PlayerVisit(CPlayer &player)
{
	if(player.GetIdentifier() == owner_)	
	{
		if(vg_state_) /* can harvest */
		{
			cout << "harvest, add money " << harvest_price_ << endl;
			player.AddMoney(harvest_price_);
			vg_state_ = false;
		}	
		else /* can't harvest */
		{
			cout << "Do you want to SEEDING this Unit?(y/n) ";
			char choice;
			cin >> choice;
			if(choice == 'y')
			{
				player.AddMoney(-1 * seeding_price_);
				vg_state_ = true;	
				cout << "Spend " << seeding_price_ << " for SEEDING..... ";
			}
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
		cout << "nothing to happen...." << endl;
	}
}

/*
 * Turn : every turn change on this unit	
 */
void CVegetableUnit::Turn(){}
/*
 * Reset : when owner is break, this unit will reset
 */
void CVegetableUnit::Reset()
{
	owner_ = -1;
	vg_state_ = false;
}
