#include"cmapunit.h"
#ifndef CPOULTRYUNIT_H
#define CPOULTRYUNIT_H
class CPoultryUnit : public CMapUnit
{
	public:
		CPoultryUnit() : egg_number_(0){};
		CPoultryUnit(const CPoultryUnit &rhs);
		CPoultryUnit & operator = (const CPoultryUnit &rhs);
		virtual ~CPoultryUnit();
		virtual void PlayerVisit(CPlayer &);
		virtual void Turn();
		virtual void Reset();
		const int GetEggNumber();
	private:
		int egg_number_; 
};
#endif
