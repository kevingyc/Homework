#include"cmapunit.h"
#ifndef CVEGETABLEUNIT_H
#define CVEGETABLEUNIT_H
class CVegetableUnit : public CMapUnit
{
	public:
		CVegetableUnit() : vg_state_(false){};
		CVegetableUnit(const CVegetableUnit &rhs);
		CVegetableUnit & operator = (const CVegetableUnit &rhs);
		virtual ~CVegetableUnit();
		virtual void PlayerVisit(CPlayer &);
		virtual void Turn();
		virtual void Reset();
		const bool GetVGState();
	private:
		bool vg_state_; /* false : can't harvest, true : can harvest */
};
#endif
