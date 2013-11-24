#include"clivestockunit.h"
#include<iostream>
using namespace std;

CLivestockUnit::~CLivestockUnit()
{
	
}


const int CLivestockUnit::GetTurn()
{
	return turn_;
}

const int CLivestockUnit::GetNumber()
{
	return number_;
}

/*
 * PlayerVisit : when player visit this unit
 */
void CLivestockUnit::PlayerVisit(CPlayer &player)
{
	if(player.GetIdentifier() == owner_)	
	{
		if(number_ == 0) /* can't harvest */
		{
			cout << "SEEDING~~" << endl;
			player.AddMoney(-1 * seeding_price_);
		}	
		else /* can harvest */
		{
			cout << "harvest, add money " << harvest_price_ * number_ << endl;
			player.AddMoney(harvest_price_ * number_);
			number_ = 0;	
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
			cout << "be stool.... decrease 1" << unit_ << endl;
			if(number_ > 0)
			{
				number_--;
			}
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
void CLivestockUnit::Turn()
{
	if(owner_ != -1)
	{
		turn_ = ( turn_ + 1 ) % live_period_;
		if(turn_ == 0)
		{
			number_++;
		}
	}

}
/*
 * Reset : when owner is break, this unit will reset
 */
void CLivestockUnit::Reset()
{
	owner_ = -1;
	number_ = 0;
	turn_ = 0;
}
