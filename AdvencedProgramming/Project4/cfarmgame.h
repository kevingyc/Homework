#include"cworldmap.h"
#include"cworldplayer.h"
#ifndef CFARMGAME_H
#define CFARMGAME_H
class CFarmGame
{
	public:
		CFarmGame();
		CFarmGame(const CFarmGame &);
		CFarmGame & operator = (const CFarmGame &rhs);
		~CFarmGame();
		const void Instruction(const int);
		void Start();
	private:
		CWorldMap worldmap_;			
		CWorldPlayer worldplayer_;
};
#endif
