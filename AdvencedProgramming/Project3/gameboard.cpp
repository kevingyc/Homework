#include <iostream>
#include"gameboard.h"
using namespace std;

/*
 * ¡³ : 1, ¡´ : 0, ¥״«e¦ל¸m : 2, ´ׁ½L¹w³] : -1
 * gameboard.h : enum Direction{D_LeftUp = 0, D_Up = 1, D_RightUp = 2, D_Left = 3, D_Center = 4, D_Right = 5, D_LeftDown = 6, D_Down = 7, D_RightDown = 8};
 *				 enum ChessType{Nil = -1, Black = 0, White = 1, Current = 2};			
 * x : ¡פ¡ץ 
 * y : ¡צ¡ק
 * 0 1 2
 * 3 4 5
 * 6 7 8
 */


/* 
 * constructor 
 */
GameBoard::GameBoard()
{
	ClearBoard();
}

/* 
 * destructor 
 */
GameBoard::~GameBoard()
{

}

/* 
 * SetLocation : implement cursor move
 */
void GameBoard::SetLocation(int direction)
{

	int dx = (direction / 3) - 1, dy = (direction % 3) - 1;

	if(board_[cursor_x_][cursor_y_] != Black && board_[cursor_x_][cursor_y_] != White)
		board_[cursor_x_][cursor_y_] = Nil;
	/*
	 * boundary detect
	 */
	cursor_x_ += dx;
	if(cursor_x_ >= GameBoard::SIZE - 1)
	{
		cursor_x_ = 1;
	}
	else if(cursor_x_ < 1)
	{
		cursor_x_ = GameBoard::SIZE - 2;
	}

	cursor_y_ += dy;
	if(cursor_y_ >= GameBoard::SIZE - 1)
	{
		cursor_y_ = 1;
	}
	else if(cursor_y_ < 1)
	{
		cursor_y_ = GameBoard::SIZE - 2;
	}
	if(board_[cursor_x_][cursor_y_] == Nil)
		board_[cursor_x_][cursor_y_] = Current;
}

/* 
 * AddMove : place a chess
 */
int GameBoard::AddMove()
{
	int result = 0;
	if(board_[cursor_x_][cursor_y_] != Black && board_[cursor_x_][cursor_y_] != White)
	{
		if((result = CanPlace(cursor_x_, cursor_y_)) != 0) // can place
		{
			return 1;
		}
		else
		{
			cout << "this position has been placed.." << endl;
			return 0;
		}
	}
	else
	{
		cout << "this position has been placed.." << endl;
		return 0;
	}
}

/* 
 * ShowBoard : print board
 * SIZE¡G8*8 
 */
void GameBoard::ShowBoard() const
{
	cout << "שÝשששÞשששÞשששÞשששÞשששÞשששÞשששÞשששß"<< endl;
	for(int i = 1 ; i < GameBoard::SIZE - 1 ; i++)
	{
		for(int j = 1 ; j < GameBoard::SIZE - 1 ; j++)
		{
			cout << "שר";
			if(board_[i][j] == Nil)
				cout << "  ";
			else if(board_[i][j] == Black)
				cout << "¡´";
			else if(board_[i][j] == White)
				cout << "¡³";
			else
				cout << "¡¸";
		}
		cout <<"שר"<< endl;
		if(i != GameBoard::SIZE - 2)
			cout << "שאשששבשששבשששבשששבשששבשששבשששבשששג"<< endl;
		else
			cout << "שדשששהשששהשששהשששהשששהשששהשששהשששו" << endl;
	}
	cout << "Arrow key : Move.   Backspace : Save the current game." << endl << "Enter : Take a move.   ESC : Go back to the main memu." << endl << endl;
}


void GameBoard::ChangePlayer()
{
	player_++;
	player_ = player_ % 2;
}

void GameBoard::SetPlayer(const int player)
{
	player_ = player;	
}

int GameBoard::GetPlayer() const
{
	return player_;	
}

int GameBoard::GetBoard(const int x, const int y) const
{
	return board_[x][y];	
}

void GameBoard::SetBoard(const int x, const int y, const int value)
{
	board_[x][y] = value;	
}

/* 
 * CanPlace : check if the position can be place 
 */
int GameBoard::CanPlace(const int x, const int y)
{
	int count = 0;
	for(int i = x - 1 ; i <= x + 1 ; i++)
	{
		for(int j = y - 1 ; j <= y + 1 ; j++)
		{
			if(i != x || j != y) // no self
			{
				if(player_ != board_[i][j] && board_[i][j] != Nil) // check difference color
				{
					if(Trace(i, j, i - x, j - y)) // through this way
					{
						board_[x][y] = player_;
						Replace(x, y, 3 * (i - x + 1) + (j - y + 1));
						count++;
					}
				}
			}
		}
	}
	return count;
}


/* 
 * Trace : check by through a way
 */
bool GameBoard::Trace(const int x, const int y, const int dispx, const int dispy)
{
	if(x + dispx > 0 && x + dispx < GameBoard::SIZE - 1 && y + dispy > 0 && y + dispy < GameBoard::SIZE - 1 // boundary detect
		&& board_[x + dispx][y + dispy] != Nil && board_[x + dispx][y + dispy] != Current) // have chess?
	{
		if(board_[x][y] == board_[x + dispx][y + dispy])
		{
			Trace(x + dispx, y + dispy, dispx, dispy); // go next
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
	
}

/* 
 * Replace : change color of chess
 */
void GameBoard::Replace(int x,int y, const int direction)
{
	int dx = (direction / 3) - 1, dy = (direction % 3) - 1;
	
	if(x > 0 && x < GameBoard::SIZE - 1 && y > 0 && y < GameBoard::SIZE - 1) // boundary detect
	{
		while(board_[x][y] != board_[x + dx][y + dy] && board_[x + dx][y + dy] != Nil)  // replace to tail?
		{
			board_[x + dx][y + dy] = board_[x][y];
			x += dx; 
			y += dy; // go next
		}
	}
}

/* 
 * CheckBoard : check can the player place chess on board
 */
int GameBoard::CheckBoard()
{
	for(int i = 1 ; i < GameBoard::SIZE - 1 ; i++)
	{
		for(int j = 1 ; j < GameBoard::SIZE - 1 ; j++)
		{
			if(board_[i][j] == -1)
			{
				for(int k = D_LeftUp ; k <= D_RightDown ; k++)
				{
					if(k != D_Center)
					{
						if(Trace(i, j, (k / 3) - 1, (k % 3) - 1))
						{
							return 1;
						}					
					}
				}
			}
		}
	}
	return 0;
}

/* 
 * Calculus : compute how many chess with white and black
 */
void GameBoard::Calculus()
{
	number_[Black] = 0;
	number_[White] = 0;
	number_[Current] = 0;

	for(int i = 1 ; i < GameBoard::SIZE - 1 ; i++)
	{
		for(int j = 1 ; j < GameBoard::SIZE - 1 ; j++)
		{
			if(board_[i][j] != -1)
				number_[board_[i][j]]++;
		}
	}
}

int GameBoard::GetNumber(const int player) const
{
	return number_[player];
}


void GameBoard::ClearBoard()
{
	for(int i = 0 ; i < GameBoard::SIZE  ; i++)
	{
		for(int j = 0 ; j < GameBoard::SIZE ; j++)
		{
			board_[i][j] = Nil;
		}
	}
	cursor_x_ = 4;
	cursor_y_ = 4;
	board_[cursor_x_][cursor_y_] = Current;
	board_[4][4] = White;
	board_[5][5] = White;
	board_[4][5] = Black;
	board_[5][4] = Black;
	player_ = Black;

	for(int i = 0 ; i < GameBoard::CHESS_TYPE ; i++)
	{
		number_[i] = 0;
	}
}
