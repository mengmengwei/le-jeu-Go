#ifndef COORDINATELIST
#define COORDINATELIST 

struct Coordinate
{
	int x;
	int y;
	int Color;
};

class CoorList
{
private:                    
	int CurrentSize;
	int Size;       //×ø±êÊýÁ¿
	Coordinate *coordinate;	

public:	
	int Distance;

	CoorList(int Size,int Distance);

	void RollBack();
	int GetColor(int ID);
	int GetX(int ID);
	int GetY(int ID);
	int GetCurrentSize();
	void Del(int x,int y);
	bool Add(int x,int y,int Color);
	//void ReDraw(CDC *pDC,int R,int G,int B,int Scale);

};

inline int CoorList::GetX(int ID){return coordinate[ID].x*Distance;}

inline int CoorList::GetY(int ID){return coordinate[ID].y*Distance;}

inline int CoorList::GetColor(int ID){return coordinate[ID].Color;}

inline int CoorList::GetCurrentSize(){return CurrentSize;}

inline void CoorList::RollBack(){CurrentSize--;}


#endif

#ifndef CHESSBOARD
#define CHESSBOARD
#define DefaultBoard 5
#define DefaultDistance 20
#define Empty 0
#define Black 1
#define White 2
#endif