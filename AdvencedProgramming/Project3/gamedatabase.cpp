#include <iostream>
#include <fstream>
#include <cstring>
#include "gamedatabase.h"
using namespace std;

/* 
 * constructor 
 */
GameDatabase::GameDatabase()
{
	filename_ = new char*[GameDatabase::NAMESIZE];
	for(int i = 0 ; i < GameDatabase::NAMESIZE ; i++)
	{
		filename_[i] = new char[GameDatabase::NAMESIZE];
	}

	strcpy(filename_[1], "1.othllo");
	strcpy(filename_[2], "2.othllo");
	strcpy(filename_[3], "3.othllo");
	strcpy(filename_[4], "4.othllo");
	strcpy(filename_[5], "5.othllo");
	strcpy(filename_[6], "6.othllo");
	strcpy(filename_[7], "7.othllo");
	strcpy(filename_[8], "8.othllo");
	strcpy(filename_[9], "9.othllo");
}

/* 
 * destructor 
 */
GameDatabase::~GameDatabase()
{
	for(int i = 0 ; i < GameDatabase::NAMESIZE ; i++)
	{
		delete []filename_[i];
	}
	delete []filename_;
}

/*
 * Load : read board from a saved file
 * 檔案內含 : 盤面 輪到的玩家 
 */
GameBoard GameDatabase::Load(GameBoard gameboard, const int fileno) const
{
	ifstream fptr (filename_[fileno], ifstream::in);
	if(fptr.is_open())
	{
		int temp;
		fptr >> temp;
		gameboard.SetPlayer(temp);
		fptr.ignore();
		for(int i = 1 ; i < gameboard.SIZE - 1 ; i++)
		{
			for(int j = 1 ; j < gameboard.SIZE - 1 ; j++)
			{
				int k;
				fptr >> k;
				gameboard.SetBoard(i, j, k);
				fptr.ignore();
			}
		}
		fptr.close();
	}
	else
	{
		cout << "File not exist." << endl;
		cout << "Start a new game........" << endl;
	}
	return gameboard;
}

/*
 * Save : write board to a file
 * 檔案內含 : 盤面 輪到的玩家 
 */
void GameDatabase::Save(GameBoard gameboard) const
{
	int fileNo;
	cout << "Which file would you want to save? (1-9) : "; 
	cin >> fileNo;
	ofstream fptr (filename_[fileNo]);	
	fptr << gameboard.GetPlayer() << "\n";
	for(int i = 1 ; i < gameboard.SIZE - 1 ; i++)
	{
		for(int j = 1 ; j < gameboard.SIZE - 1 ; j++)
		{
			if(j != 1)
			{
				fptr << " ";
			}
			fptr << gameboard.GetBoard(i, j) ;
		}
		fptr << "\n";
	}
	fptr.close();
}

