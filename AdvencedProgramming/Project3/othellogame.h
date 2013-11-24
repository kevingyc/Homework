/*
 * ½sÄ¶Àô¹Ò : visual studio 2008
 */

#ifndef _othellogame_h_
#define _othellogame_h_

#include <iostream>
#include"gamedatabase.h"
using namespace std;

enum SelectType{GameClose = 0, GameEnd, GameStart};

enum Key{VK_END = 27, VK_FUNC = -32, VK_UP = 72, VK_DOWN = 80, VK_LEFT = 75, VK_RIGHT = 77, VK_ENTER = 13, VK_BACKSPACE = 8};

class OthelloGame
{
      public:
            OthelloGame();
            ~OthelloGame();
			void ShowMain() const;
			void StartGame();
      private:      
			GameDatabase database_;
			GameBoard gameboard_;
};
#endif

