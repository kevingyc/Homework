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
	cout << worldplayer_.playerlist_[i].GetName() << ", 請選擇? (1:擲骰子 / 2:離開遊戲)...> ";
}

void CFarmGame::Start()
{
	int person = 0;
	const int ini_money = 5000;
	
	cout << "請輸入玩家總數?(Maximum:4)...> ";
	cin >> person;
	worldplayer_.SetPerson(person);
	worldmap_.IniRoad(person);
	for(int i = 0 ; i < person ; i++)
	{
		string name;
		cout << "請輸入玩家 "<< i + 1 << " 的名字 : ";
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
					cout << "輸入錯誤, 請重新輸入!" << endl;
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
			cout << worldplayer_.playerlist_[currentplayer].GetName() << "破產了, 所擁有的東西將全數歸還...." << endl;
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
			cout << "全數玩家都破產了, 遊戲結束...." << endl;
			system("pause");
		}
	}
}

