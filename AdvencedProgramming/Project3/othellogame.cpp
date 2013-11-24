#include <cstdlib>
#include <iostream>
#include <conio.h>
#include "othellogame.h"
using namespace std;

/*
 * othellogame.h : enum SelectType{GameClose = 0, GameEnd, GameStart};
 * gameboard.h : enum Direction{D_LeftUp = 0, D_Up = 1, D_RightUp = 2, D_Left = 3, D_Center = 4, D_Right = 5, D_LeftDown = 6, D_Down = 7, D_RightDown = 8};
 *				 enum ChessType{Nil = -1, Black = 0, White = 1, Current = 2};	
 */

/* 
 * constructor 
 */
OthelloGame::OthelloGame()
{

}

/* 
 * destructor 
 */
OthelloGame::~OthelloGame()
{

}

/* 
 * ShowMain : print instruction 
 */
void OthelloGame::ShowMain() const
{
	cout << "Welcome to play Othllo Game......." << endl;
	cout << "1. Start a new game." << endl;
	cout << "2. Load an old game." << endl;
	cout << "3. Quit the program." << endl;
	cout << "Selection : ";	
}

void OthelloGame::StartGame()
{
	ShowMain();
    int select = 0, game = GameClose, fileNo = 0;
	bool isFunc = false;
	char ch = 0;
	while(select != 3)
	{
		cin >> select;
		switch(select)
		{
			case 1: /* start a new game */
				select = 3;
				game = GameStart;
				gameboard_.ClearBoard();
				break;
			case 2: /* load a saved game */
				cout << "Which file would you want to load? (1-9) : "; 
				cin >> fileNo;
				gameboard_.ClearBoard();
				gameboard_ = database_.Load(gameboard_, fileNo);
				system("pause");
				game = GameStart;
				select = 3;
				break;
			case 3: /* quit a game */
				break;
			default:/* error selection */
				cout << "Invalid Choice, Please select again." << endl;
				cout << "Selection : ";	
				break;
		}

		bool cantPut[GameBoard::CHESS_TYPE] = {true};

		while(game == GameStart)
		{	
			system("cls");
			gameboard_.ShowBoard();
			gameboard_.Calculus();

			if(gameboard_.GetPlayer()) // 0 -> black, 1 -> white
				cout << "Player White's Turn!!!" << endl;
			else
				cout << "Player Black's Turn!!!" << endl;	

			cout << "Black(¡´): " << gameboard_.GetNumber(Black) << "  " << "White(¡³) : " << gameboard_.GetNumber(White) << endl;

			if(!gameboard_.CheckBoard()) // can't place
			{
				cantPut[gameboard_.GetPlayer()] = false;

				if(gameboard_.GetPlayer())
					cout << "Player White cannot place......!!!" << endl;
				else
					cout << "Player Black cannot place......!!!" << endl;	
				gameboard_.ChangePlayer();
				if(!cantPut[Black] && !cantPut[White]) // both black and white can't place
				{
					game = GameEnd;
				}
			}
			else
			{
				cantPut[Black] = true;
				cantPut[White] = true;
				ch = getch();
				//cout << (int)ch << endl;
				if(ch == VK_END)
				{
					system("cls");
					ShowMain();
					select = 0;
					game = GameClose;
					break;
				}
				else if(ch == VK_FUNC)
					isFunc = true;

				if(isFunc == true)
				{
					switch(ch)
					{
						case VK_UP:
							//cout<<"¡ô"<<endl;
							gameboard_.SetLocation(D_Up);
							isFunc = false;
							break;
						case VK_LEFT:
							//cout<<"¡ö"<<endl;
							gameboard_.SetLocation(D_Left);
							isFunc = false;
							break;
						case VK_RIGHT:
							//cout<<"¡÷"<<endl;
							gameboard_.SetLocation(D_Right);
							isFunc = false;
							break;
						case VK_DOWN:
							//cout<<"¡õ"<<endl;
							gameboard_.SetLocation(D_Down);
							isFunc = false;
							break;
					}
				}
				else
				{
					if(ch == VK_ENTER)
					{
						if(gameboard_.AddMove())
							gameboard_.ChangePlayer();
					}
					else if(ch == VK_BACKSPACE)
					{
						database_.Save(gameboard_);
					}
				}
			}
		}

		if(game == GameEnd)
		{
			if(gameboard_.GetNumber(Black) > gameboard_.GetNumber(White))
			{
				cout << "Black win." << endl;
			}
			else if(gameboard_.GetNumber(Black) < gameboard_.GetNumber(White))
			{
				cout << "White win." << endl;
			}
			else
			{
				cout << "Draw game." << endl;
			}
			select = 0;
			game = GameClose;
			system("pause");
			system("cls");
			ShowMain();
		}
	} 
}
