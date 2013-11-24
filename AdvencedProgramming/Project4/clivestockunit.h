#include <string>
using namespace std;
#include"cmapunit.h"

#ifndef CLIVESTOCKUNIT_H
#define CLIVESTOCKUNIT_H
class CLivestockUnit : public CMapUnit
{
	public:
		CLivestockUnit() : number_(0), turn_(0), live_period_(0), unit_(""){};
		CLivestockUnit(const CLivestockUnit &);
		CLivestockUnit & operator = (const CLivestockUnit &rhs);
		virtual ~CLivestockUnit();
		virtual void PlayerVisit(CPlayer &);
		virtual void Turn();
		virtual void Reset();
		void SetLivePeriod(const int live_period){ live_period_ = live_period; };
		void SetUnit(const string unit){ unit_ = unit; };
		const int GetNumber();
		const int GetTurn();
		const int GetLivePeriod(){ return live_period_; };
		const string GetUnit(){ return unit_; };
	private:
		int number_; 
		int turn_;
		int live_period_;
		string unit_;
};
#endif
