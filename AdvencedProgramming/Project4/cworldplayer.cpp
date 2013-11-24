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
			cout << i << "]"<< setw(20) << playerlist_[i].GetName() << setw(4) << "$" << setw(6) << playerlist_[i].GetMoney() << " �֦� " << playerlist_[i].GetOwned() << " ���" << endl;
		}
	}
	cout << endl;
}
/*
=>[0]           ���g�B   $5000 �֦� 0 ���
  [1]           �]�p��   $5000 �֦� 0 ���
  [2]           ������   $5000 �֦� 0 ���
*/