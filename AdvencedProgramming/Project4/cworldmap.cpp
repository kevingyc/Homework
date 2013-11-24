#include"cworldmap.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

CWorldMap::CWorldMap()
{
	ReadMapData();
}

CWorldMap::~CWorldMap()
{
	for(int i = 0 ; i < mapsize_ ; i++)
	{
		delete map_[i];
	}
	delete map_;
}
	
int CWorldMap::GetMapSize()
{
	return mapsize_;
}
	
/*
 * ReadMapData : read board from a saved file
 * 檔案內含 : 地圖資料
 */
void CWorldMap::ReadMapData()
{
	ifstream fptr ("farmmap.farmmap", ifstream::in);
	if(fptr.is_open())
	{
		fptr >> mapsize_;
		map_ = new CMapUnit*[mapsize_];
		fptr.ignore();
		
		for(int i = 0 ; i < mapsize_ ; i++)
		{
			char kind;
			string name, unit;
			int buy, seed, harv, period;
			fptr >> kind;
			switch(kind)
			{
				case 'V': /* Vegetable */
					map_[i] = new CVegetableUnit();
					break;
				case 'O': /* Orchard */
					map_[i] = new COrchardUnit();
					break;
				case 'L': /* Livestock */	
					map_[i] = new CLivestockUnit();
					break;
				case 'P': /* Poultry */
					map_[i] = new CPoultryUnit();	
					break;
				default:
					break;															
			}
			map_[i]->SetType(kind);
			fptr >> name;
			map_[i]->SetMapName(name);
			fptr >> buy;
			map_[i]->SetBuyPrice(buy);
			fptr >> seed;
			map_[i]->SetSeedingPrice(seed);
			fptr >> harv;
			map_[i]->SetHarvestPrice(harv);
			if(kind == 'L')
			{
				fptr >> period;
				((CLivestockUnit*)map_[i])->SetLivePeriod(period);
				fptr >> unit;
				((CLivestockUnit*)map_[i])->SetUnit(unit);
			}
			fptr.ignore();
		}
	
		fptr.close();
	}
	else
	{
		cout << "File not exist." << endl;
	}
}

/*
 * IniRoad : initialize the player' s location
 */
void CWorldMap::IniRoad(int person)
{
	person_ = person;
	playerroad_ = new bool*[mapsize_];
	for(int i = 0 ; i < mapsize_ ; i++)
	{
		playerroad_[i] = new bool[person_];
		for(int j = 0 ; j < person_ ; j++)
		{
			if(i == 0)
			{
				playerroad_[i][j] = true; /* player at here */
			}
			else
			{
				playerroad_[i][j] = false;
			}
		}
	}
}

/*
 * SetRoad : player move.
 */
void CWorldMap::SetRoad(CPlayer &person, int steps)
{
	playerroad_[person.GetLocation()][person.GetIdentifier()] = false;
	int next = person.GetLocation() + steps;
	if(next >= mapsize_) /* if player walk back start point */
	{
		next -= mapsize_;
		person.AddMoney(-500);
	}
	person.SetLocation(next);
	playerroad_[person.GetLocation()][person.GetIdentifier()] = true;
}

/*
 * ShowAll : print all the map status
 */
const void CWorldMap::ShowAll()
{
	for(int i = 0 ; i < mapsize_ ; i++)
	{
		cout << "=";
		for(int j = 0 ; j < person_ ; j++)
		{
			if(playerroad_[i][j])
			{
				cout << j;
			}
			else
			{
				cout << ' ';
			}
		}
		
		cout << "=";
		cout << "[" << setw (2) << i << "]";
		cout << setw(10) << map_[i]->GetMapName();
		
		if(map_[i]->GetOwner() == -1)
		{
			cout << " {"  << ' ' << "} ";
			cout << "(-" << setw(4) << map_[i]->GetBuyPrice() << "/-" << setw(4) << map_[i]->GetSeedingPrice() << "/+" << setw(4) << map_[i]->GetHarvestPrice() << ")" << endl;
		}
		else
		{
			cout << " {"  << map_[i]->GetOwner() << "} ";
			cout << "(-" << setw(4) << map_[i]->GetSeedingPrice() << "/+" << setw(4) << map_[i]->GetHarvestPrice() << ")" ;
			switch(map_[i]->GetType())
			{
				case 'V':
					if(((CVegetableUnit*)map_[i])->GetVGState())
					{
						cout << " 待收成" << endl;
					}
					else
					{
						cout << " 未播種" << endl;
					}
					break;
				case 'O':
					switch(((COrchardUnit*)map_[i])->GetState())
					{
						case 0:
							cout << " 未播種";
							break;
						case 1:
							cout << " 小幼苗";
							break;
						case 2:
							cout << " 小果樹";
							break;
						case 3:
							cout << " 大果樹";
							break;
						case 4:
							cout << " 待收成";
							break;
						default:
							break;
					}
					for(int j = 0 ; j < ((COrchardUnit*)map_[i])->GetDamege() ; j++)
					{
						cout << "蟲";
					}
					cout << endl;
					break;
				case 'L':	
					cout << " 目前有" << setw(4) << ((CLivestockUnit*)map_[i])->GetNumber() << " " << ((CLivestockUnit*)map_[i])->GetUnit() << "(" << ((CLivestockUnit*)map_[i])->GetLivePeriod() - ((CLivestockUnit*)map_[i])->GetTurn() << ")" << endl;
					break;
				case 'P':
					cout << " 目前有" << setw(4) << ((CPoultryUnit*)map_[i])->GetEggNumber() << " 顆蛋" << endl;
					break;
				default:
					break;	
			}
		}
	}
	cout << endl;
}

/*
= = [ 0]      菠菜園 { }  (- 100/-  10/+  60)
= = [ 1]        雞舍 { }  (- 500/-  10/+   5)
= = [ 2]    空心菜園 { }  (- 100/-  10/+  50)
= = [ 3]        馬廄 { }  (-1000/- 500/+ 100)
= = [ 4]      蘋果園 { }  (- 400/- 100/+2000)
= = [ 5]    紅蘿蔔園 { }  (- 100/-  10/+  30)
=0= [ 6]        鴨舍 { }  (- 400/-  10/+   8)
= = [ 7]        牛棚 { }  (- 800/- 400/+  80)
= = [ 8]      西瓜園 { }  (- 300/-  50/+1000)
= = [ 9]    哈蜜瓜園 { }  (- 600/- 150/+3000)
= = [10]        鵝舍 { }  (- 500/-  10/+  10)
= = [11]        驢廄 { }  (- 700/- 350/+  70)
= = [12]      香菜園 { }  (- 100/-  10/+  70)
= = [13]        鴿舍 { }  (- 400/-  10/+   3)
= = [14]      水梨園 { }  (- 700/- 200/+4000)
= = [15]        羊圈 { }  (- 600/- 300/+  60)
*/

/*
 * EveryTurn : every turn' s change of whole map
 */
void CWorldMap::EveryTurn()
{
	for(int i = 0 ; i < mapsize_ ; i++)	
	{
		map_[i]->Turn();
	}
}

/*
 * RIP : when player no money, its all resource will be reset
 */
void CWorldMap::RIP(int player)
{
	for(int i = 0 ; i < mapsize_ ; i++)
	{
		if(map_[i]->GetOwner() == player)
		{
			map_[i]->Reset();
		}
	}
}