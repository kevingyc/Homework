#include"cplayer.h"
#ifndef CWORLDPLAYER_H
#define CWORLDPLAYER_H
class CWorldPlayer
{
	public:
		CWorldPlayer();
		CWorldPlayer(const CWorldPlayer &);
		CWorldPlayer & operator = (const CWorldPlayer &rhs);
		~CWorldPlayer();
		void SetPerson(int);
		const void ShowAll(int);
		void PlayerDie(int);
		friend class CFarmGame;
	protected:
		CPlayer *playerlist_;
		int person_;
};
#endif