#include "CCoordinateListView.h"
#include "CGo.h"
#include <iostream>
using namespace std;

int main()
{
	CoorList *coorlist=new CoorList(DefaultBoard,DefaultDistance);               //值得注意的是，奇数参数带来更好的显示效果，设置棋盘大小和列数
	Chessboard *chessboard=new Chessboard(DefaultBoard);
	chessboard->Put(1,1,coorlist);

	return 0;
}