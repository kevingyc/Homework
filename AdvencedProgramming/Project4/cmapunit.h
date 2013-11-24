#include<string>
#include"cplayer.h"
#ifndef CMAPUNIT_H 
#define CMAPUNIT_H
using namespace std;

class CMapUnit
{
	public:
		CMapUnit() : buy_price_(0), seeding_price_(0), harvest_price_(0), owner_(-1), mapname_(""){};
		CMapUnit(const CMapUnit &);
		CMapUnit & operator = (const CMapUnit &rhs);
		virtual ~CMapUnit(){};
		virtual void PlayerVisit(CPlayer &) = 0;
		virtual void Turn() = 0;
		virtual void Reset() = 0;
		void SetType(const char type){ type_ = type; };
		void SetBuyPrice(const int buy){ buy_price_ = buy; };
		void SetSeedingPrice(const int seed) { seeding_price_ = seed; };
		void SetHarvestPrice(const int harv){ harvest_price_ = harv; };
		void SetOwner(const int owner){ owner_ = owner; };
		void SetMapName(const string name){ mapname_ = name; };
		const int GetType(){ return type_; };
		const int GetBuyPrice(){ return buy_price_;};
		const int GetSeedingPrice(){ return seeding_price_;};
		const int GetHarvestPrice(){ return harvest_price_;};
		const int GetOwner(){ return owner_;};
		const string GetMapName(){ return mapname_; };

	protected:
		char type_;
		int buy_price_;
		int seeding_price_;
		int harvest_price_;
		int owner_;
		string mapname_;

};
#endif 
