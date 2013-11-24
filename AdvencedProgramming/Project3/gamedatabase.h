#ifndef _gamedatabase_h_
#define _gamedatabase_h_

#include <iostream>
#include "gameboard.h"
using namespace std;

class GameDatabase
{
      public:

			static const int NAMESIZE = 10;

			GameDatabase();
			~GameDatabase();
			void Save(GameBoard) const;
			GameBoard Load(GameBoard, const int) const;

      private:
			char **filename_;
};
#endif


