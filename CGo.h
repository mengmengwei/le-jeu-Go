#ifndef CGO_H
#define CGO_H
class GoCoordinate
{
private:
	int state;
public:
	int life;
	int flag;	
public:
	GoCoordinate();
	void GetGoPlaced(int Color,CoorList *coorlist,int x,int y);
	int ChangeFlag(GoCoordinate *direction);
	bool lifeReduce();
};

class Chessboard
{
private:
	int Size;
	GoCoordinate** GoCoordinates;
public:
	int turn;

	Chessboard(int RealSize);
	int Put(int x,int y,CoorList *coorlist);
	void Start();                                       //¿ÉÊ¡ÂÔº¯Êý
	void Judge(int flag,CoorList *coorlist);
	void reFlag(int flagOld,int flagNew);
	void GoRollback();
};                 

#endif