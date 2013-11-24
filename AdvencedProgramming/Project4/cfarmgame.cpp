#include"cfarmgame.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
using namespace std;

CFarmGame::CFarmGame()
{
	
}

CFarmGame::~CFarmGame()
{
	
}

const void CFarmGame::Instruction(const int i)
{
	cout << worldplayer_.playerlist_[i].GetName() << ", �п��? (1:�Y��l / 2:���}�C��)...> ";
}

void CFarmGame::Start()
{
	int person = 0;
	const int ini_money = 5000;
	
	cout << "�п�J���a�`��?(Maximum:4)...> ";
	cin >> person;
	worldplayer_.SetPerson(person);
	worldmap_.IniRoad(person);
	for(int i = 0 ; i < person ; i++)
	{
		string name;
		cout << "�п�J���a "<< i + 1 << " ���W�r : ";
		cin >> name;
		worldplayer_.playerlist_[i].SetName(name);
		worldplayer_.playerlist_[i].SetLocation(0);
		worldplayer_.playerlist_[i].SetMoney(ini_money);
		worldplayer_.playerlist_[i].SetIdentifier(i);
	}
	
	worldmap_.ReadMapData();
	int currentplayer = 0;
	bool gamestart = true;
	while(gamestart)
	{
		srand((unsigned)time(NULL));
		system("cls");
		worldmap_.ShowAll();
		worldplayer_.ShowAll(currentplayer);
		Instruction(currentplayer);
		int steps = rand() % 6 + 1;
		char choice = '0' ;
		while(choice != '2')
		{
			cin.get(choice) >> choice;
			switch(choice)
			{
				case '1':
					choice = '2';
					break;
				case '2':
					choice = '2';
					gamestart = false;
					break;
				default:
					cout << "��J���~, �Э��s��J!" << endl;
					break;
			}
		}

		if(gamestart)
		{
			worldmap_.SetRoad(worldplayer_.playerlist_[currentplayer] ,steps);
			system("cls");
			worldmap_.ShowAll();
			worldplayer_.ShowAll(currentplayer);
			worldmap_.EveryTurn();
			worldmap_.map_[worldplayer_.playerlist_[currentplayer].GetLocation()]->PlayerVisit(worldplayer_.playerlist_[currentplayer]);
			currentplayer = ( currentplayer + 1 ) % person; 
			system("pause");
		}

		if(worldplayer_.playerlist_[currentplayer].GetMoney() <= 0)
		{
			cout << worldplayer_.playerlist_[currentplayer].GetName() << "�}���F, �Ҿ֦����F��N�����k��...." << endl;
			system("pause");
			worldmap_.RIP(currentplayer);
			worldplayer_.PlayerDie(currentplayer);
		}

		int dieman = 0;

		for(int i = 0 ; i < person ; i++)
		{
			if(worldplayer_.playerlist_[i].IsDie())
			{
				dieman++;
			}
		}

		if(dieman == person)
		{
			gamestart = false;
			cout << "���ƪ��a���}���F, �C������...." << endl;
			system("pause");
		}
	}
}

