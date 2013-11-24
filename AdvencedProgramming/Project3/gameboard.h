#ifndef _gameboard_h_
#define _gameboard_h_

#include <iostream>
using namespace std;

enum Direction{D_LeftUp = 0, D_Up = 1, D_RightUp = 2, D_Left = 3, D_Center = 4, D_Right = 5, D_LeftDown = 6, D_Down = 7, D_RightDown = 8};
enum ChessType{Nil = -1, Black = 0, White = 1, Current = 2};

class GameBoard
{
      public:
            GameBoard();
            ~GameBoard(); 

			static const int SIZE = 10, DIRECT = 8, CHESS_TYPE = 3;

            int AddMove();
            void ShowBoard() const;
			void SetLocation(int);
			void ChangePlayer();
			int GetPlayer() const;
			void SetPlayer(const int);
			int GetBoard(const int, const int) const;
			void SetBoard(const int, const int, const int);
			bool Trace(const int, const int, const int, const int);
			int CheckBoard();
			int GetNumber(const int) const;
			void Calculus();
			void ClearBoard();

      private:
            void Replace(int, int, const int);
            int CanPlace(const int, const int);
            
			int cursor_x_, cursor_y_;
            int board_[SIZE][SIZE];  
			int player_;
			int number_[CHESS_TYPE];
};
#endif



