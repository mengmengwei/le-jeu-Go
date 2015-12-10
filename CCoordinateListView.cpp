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
	//x=x*Distance;                                    //�����������λ��
	//y=y*Distance;

	int i;
	for(i=0;i<this->CurrentSize;i++)
		if((this->coordinate[i].x==x)&&(this->coordinate[i].y==y))
		{
			this->coordinate[i].x=this->coordinate[CurrentSize-1].x;        //�ڲ�ע������˳�������£��������������
			this->coordinate[i].y=this->coordinate[CurrentSize-1].y;        //һ����������ǰ�������ɾ��������	
			this->coordinate[i].Color=this->coordinate[CurrentSize-1].Color;//������ϵͳ���Ӳ����������ܵĻ����Ͳ�����������
			//MessageBox(0,L"deleted!",L"dd",0);
			break;                                                          
		}
	this->CurrentSize--;
}

bool CoorList::Add(int x,int y,int Color)
{
	if(CurrentSize==Size*Size)
		return false;                                    //�����������޷�����

	//x=x*Distance;                                        //�����������λ��
	//y=y*Distance;

	for(int i=0;i<this->CurrentSize;i++)
		if((this->coordinate[i].x==x)&&(this->coordinate[i].y==y))
			return false;                                //�����غϣ����ɲ���

	coordinate[CurrentSize].x=x;
	coordinate[CurrentSize].y=y;
	coordinate[CurrentSize].Color=Color;
	CurrentSize++;
	return true;
}

/*
void CoorList::ReDraw(CDC *pDC,int R,int G,int B,int Scale)
//��û�в���˫�����ͼ������£�������Ҫ�����ܼ����ڻ�ͼ�����е��������������������ֻ������
//����˫�����ͼ��������������������̶����ڻ�ͼ�����н��еģ��������Ӱ���û����顣
{
    /***************************���Ʊ���*******************************/
/*	CPen Pen,*pOldPen; 
	Pen.CreatePen(PS_SOLID,1,RGB(R,G,B));//�������� 
	pOldPen=pDC->SelectObject(&Pen);     //ѡ�л��ʣ�ѡ���»���ʱ���ؾɻ��ʣ�Ҫ���� 
	for(int i=0;i<=Distance*Size*Scale;i++)           
	{
		pDC->MoveTo(0,i);
		pDC->LineTo(Distance*Size*Scale,i);
		pDC->MoveTo(i,0);
		pDC->LineTo(i,Distance*Size*Scale);
	}
	pDC->SelectObject(pOldPen);          //�ָ��µĻ��ʣ�������&Pen,    
	
	/**************************��������********************************/	
/*	for(int i=Distance/2*Scale;i<=Distance/2*Scale+Distance*(Size-1)*Scale;i=i+Distance*Scale)           
	{
		pDC->MoveTo(Distance/2*Scale,i);
		pDC->LineTo(Distance/2*Scale+Distance*(Size-1)*Scale,i);
		pDC->MoveTo(i,Distance/2*Scale);
		pDC->LineTo(i,Distance/2*Scale+Distance*(Size-1)*Scale);
	}

	/***************���ƺڰ�����********************/	
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
	Pen.DeleteObject();                     //�ѻ���ɾ����  

}
*/