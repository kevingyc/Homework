#include"cmapunit.h"
#include"cvegetableunit.h"
#include"corchardunit.h"
#include"clivestockunit.h"
#include"cpoultryunit.h"
#ifndef CWORLDMAP_H
#define CWORLDMAP_H
class CWorldMap
{
	public:
		CWorldMap();
		CWorldMap(const CWorldMap &);
		CWorldMap & operator = (const CWorldMap &rhs);
		~CWorldMap();
		int GetMapSize();
		void ReadMapData();
		void IniRoad(int);
		void SetRoad(CPlayer &, int);
		const void ShowAll();
		void EveryTurn();
		void RIP(int);
		friend class CFarmGame;
	protected:
		CMapUnit **map_;
		bool **playerroad_;
		int mapsize_, person_;
};
#endif