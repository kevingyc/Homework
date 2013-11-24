#include"cmapunit.h"
#ifndef CORCHARDUNIT_H
#define CORCHARDUNIT_H
class COrchardUnit : public CMapUnit
{
	public:
		COrchardUnit() : state_(0), damage_level_(0){};
		COrchardUnit(const COrchardUnit &rhs);
		COrchardUnit & operator = (const COrchardUnit &rhs);
		virtual ~COrchardUnit();
		virtual void PlayerVisit(CPlayer &);
		virtual void Turn();
		virtual void Reset();
		const int GetState();
		const int GetDamege();
	private:
		int state_; /*0~4*/
		int damage_level_; /*0~4*/
};
#endif
