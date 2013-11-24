#include"CWorldPlayer.h"
#include<iostream>
#include<iomanip>
using namespace std;

CWorldPlayer::CWorldPlayer()
{

}

CWorldPlayer::~CWorldPlayer()
{
	delete []playerlist_;
}

void CWorldPlayer::SetPerson(int people)
{
	person_ = people;
	playerlist_ = new CPlayer[person_];	
}

void CWorldPlayer::PlayerDie(int player)
{
	playerlist_[player].Die();
}

const void CWorldPlayer::ShowAll(int current)
{
	for(int i = 0 ; i < person_ ; i++)	
	{

		if(!playerlist_[i].IsDie())
		{
			if(i == current)
			{
				cout << "=>[";
			}
			else
			{
				cout << "  [";
			}
			cout << i << "]"<< setw(20) << playerlist_[i].GetName() << setw(4) << "$" << setw(6) << playerlist_[i].GetMoney() << " 局Τ " << playerlist_[i].GetOwned() << " 虫" << endl;
		}
	}
	cout << endl;
}
/*
=>[0]              $5000 局Τ 0 虫
  [1]           甝   $5000 局Τ 0 虫
  [2]           īī   $5000 局Τ 0 虫
*/