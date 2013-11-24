#include <string>
using namespace std;
#ifndef CPLAYER_H
#define CPLAYER_H
class CPlayer
{
	public:
		CPlayer();
		CPlayer(const CPlayer &rhs);
		CPlayer & operator = (const CPlayer &rhs);
		~CPlayer();
		const string GetName();
		const int GetLocation();
		const int GetMoney();
		void AddMoney(const int);
		const int GetIdentifier();
		const int GetOwned();
		void SetName(const string );
		void SetLocation(const int );
		void SetMoney(const int );
		void SetIdentifier(const int );
		void SetOwned(const int );
		void Die();
		bool IsDie();
	private:
		string name_;
		int identifier_;
		int location_;
		int money_;
		int owned_;
		bool isdie_;
};
#endif
