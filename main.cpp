#include "CCoordinateListView.h"
#include "CGo.h"
#include <iostream>
using namespace std;

int main()
{
	CoorList *coorlist=new CoorList(DefaultBoard,DefaultDistance);               //ֵ��ע����ǣ����������������õ���ʾЧ�����������̴�С������
	Chessboard *chessboard=new Chessboard(DefaultBoard);
	chessboard->Put(1,1,coorlist);

	return 0;
}