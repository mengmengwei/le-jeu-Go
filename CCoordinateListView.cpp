#include"CCoordinateListView.h"
#define NULL 0

CoorList::CoorList(int Size,int Distance)
{
	coordinate=new Coordinate[Size*Size];
	this->Size=Size;
	this->CurrentSize=0;
	this->Distance=Distance;
}

void CoorList::Del(int x,int y)
{
	//x=x*Distance;                                    //修正鼠标点击的位置
	//y=y*Distance;

	int i;
	for(i=0;i<this->CurrentSize;i++)
		if((this->coordinate[i].x==x)&&(this->coordinate[i].y==y))
		{
			this->coordinate[i].x=this->coordinate[CurrentSize-1].x;        //在不注重数组顺序的情况下，不妨仅仅将最后
			this->coordinate[i].y=this->coordinate[CurrentSize-1].y;        //一个数组项提前，以填补被删除的数组	
			this->coordinate[i].Color=this->coordinate[CurrentSize-1].Color;//如果想给系统增加操作撤销功能的话，就不能这样做了
			//MessageBox(0,L"deleted!",L"dd",0);
			break;                                                          
		}
	this->CurrentSize--;
}

bool CoorList::Add(int x,int y,int Color)
{
	if(CurrentSize==Size*Size)
		return false;                                    //数组已满，无法插入

	//x=x*Distance;                                        //修正鼠标点击的位置
	//y=y*Distance;

	for(int i=0;i<this->CurrentSize;i++)
		if((this->coordinate[i].x==x)&&(this->coordinate[i].y==y))
			return false;                                //坐标重合，不可插入

	coordinate[CurrentSize].x=x;
	coordinate[CurrentSize].y=y;
	coordinate[CurrentSize].Color=Color;
	CurrentSize++;
	return true;
}

/*
void CoorList::ReDraw(CDC *pDC,int R,int G,int B,int Scale)
//在没有采用双缓冲绘图的情况下，我们需要尽可能减少在绘图过程中的运算量，所以这个函数只适用于
//采用双缓冲绘图的情况。否则，许多运算过程都是在绘图过程中进行的，这会严重影响用户体验。
{
    /***************************绘制背景*******************************/
/*	CPen Pen,*pOldPen; 
	Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));//创建画笔 
	pOldPen=pDC->SelectObject(&Pen);     //选中画笔，选中新画笔时返回旧画笔，要保存 
	for(int i=0;i<=Distance*Size*Scale;i++)           
	{
		pDC->MoveTo(0,i);
		pDC->LineTo(Distance*Size*Scale,i);
		pDC->MoveTo(i,0);
		pDC->LineTo(i,Distance*Size*Scale);
	}
	pDC->SelectObject(pOldPen);          //恢复新的画笔，返回了&Pen,    
	
	/**************************绘制棋盘********************************/	
/*	for(int i=Distance/2*Scale;i<=Distance/2*Scale+Distance*(Size-1)*Scale;i=i+Distance*Scale)           
	{
		pDC->MoveTo(Distance/2*Scale,i);
		pDC->LineTo(Distance/2*Scale+Distance*(Size-1)*Scale,i);
		pDC->MoveTo(i,Distance/2*Scale);
		pDC->LineTo(i,Distance/2*Scale+Distance*(Size-1)*Scale);
	}

	/***************绘制黑白棋子********************/	
/*	for(int i=0;i<this->GetCurrentSize();i++)
	{	
		if(this->GetColor(i)==White)
		{
			pDC->Rectangle(this->GetX(i)-Distance*Scale+1,
				 		   this->GetY(i)-Distance*Scale+1,
						   this->GetX(i)-1,
						   this->GetY(i)-1);
		}
		else
		{
			for(int j=this->GetY(i)-Distance*Scale+1;j<this->GetY(i)-1;j++)
			{
				pDC->MoveTo(this->GetX(i)-Distance*Scale+1,j);
				pDC->LineTo(this->GetX(i)-1,j);
			}
		}
	}
	Pen.DeleteObject();                     //把画笔删除掉  

}
*/