//#include"StdAfx.h"
#include"CCoordinateListView.h"
#include"CGo.h"



/**************************GoCoordinate���ʵ��************************/
GoCoordinate::GoCoordinate()
{
	life=4;
	flag=0;
}

bool GoCoordinate::lifeReduce()
{
	life--;         
	if(life==0&&flag!=0)  //�ǿյ�������lifeΪ0��������Щ���������������Ч��
		return false;
	else
		return true;
}

int GoCoordinate::ChangeFlag(GoCoordinate *Direction)
{
	if(state==Direction->state)
		if(Direction->flag==0)
		{
			Direction->flag=flag;//flag����������,�������������ȣ��ѵ㣺���Ƕ���������ӵ�һ�������
		    return 0;
		}
		else
			return 1;           //�����顱ͬɫ����������
	else
		return -1;              //��ͬɫ����
}

void GoCoordinate::GetGoPlaced(int Color,CoorList *coorlist,int x,int y)
{
	state=Color;
	if(Color==Empty)
		coorlist->Del(x,y);
}

/****************************Chessboard���ʵ��***************************/
Chessboard::Chessboard(int RealSize)
{
	this->Size=RealSize+2;
	this->turn=0;

	this->GoCoordinates=new GoCoordinate*[Size];
	int i;
	for(i=0;i<Size;i++)
		GoCoordinates[i]=new GoCoordinate[Size];

	for(i=1;i<Size-1;i++)                              //�������̱߽�����,��Ϊ������֮�佨����ϵ
	{	
		GoCoordinates[1][i].lifeReduce();
		GoCoordinates[Size-2][i].lifeReduce();
	}
	for(i=1;i<Size-1;i++)
	{
		GoCoordinates[i][1].lifeReduce();
		GoCoordinates[i][Size-2].lifeReduce();
	}
}

void Chessboard::Judge(int flag,CoorList *coorlist)                            //�ж������Ƿ�����,����
{
	int i,j;
	for(i=1;i<this->Size-1;i++)
		for(j=1;j<this->Size-1;j++)
			if(this->GoCoordinates[i][j].flag==flag&&this->GoCoordinates[i][j].life!=0)
				return;                   //һ��������������0�����ӣ����������ж�
	for(i=1;i<this->Size-1;i++)
		for(j=1;j<this->Size-1;j++)		  //�˶δ����д��Ż�,������ɹ�����ظ��ж�,�˶γ��򣬱��������齫���ӵ�ַ��ţ���������ΪӦ�þ����ܶ�����cpu�������ڴ�
			if(this->GoCoordinates[i][j].flag==flag)
			{
				this->GoCoordinates[i][j].GetGoPlaced(Empty,coorlist,i,j);
				this->GoCoordinates[i][j].flag=0;
				this->GoCoordinates[i-1][j].life++;
				this->GoCoordinates[i+1][j].life++;
				this->GoCoordinates[i][j+1].life++;
				this->GoCoordinates[i][j-1].life++;
			}	
}

void Chessboard::reFlag(int flagOld,int flagNew)
/***ChangFlag�����Ĺ��ܲ��亯����ˢ�������ϵ�������ͬ�����ٵ����ӵ�flagֵ***/
/********��������Ĵ������ڣ���Ҫˢ���������̣�Ч�ʵ��£���ʵ�ּ�*********/
{
	int i,j;
	for(i=0;i<this->Size-1;i++)
		for(j=0;j<this->Size-1;j++)
			if(this->GoCoordinates[i][j].flag==flagOld)
				this->GoCoordinates[i][j].flag=flagNew;
}

int Chessboard::Put(int x,int y,CoorList *coorlist)
{	
	//����x��y����,������ת��Ϊ�߼����꣺
	x=x/coorlist->Distance+1;
	y=y/coorlist->Distance+1;

	int i=0;
	if(x<=0||x>=this->Size-1||y<=0||y>=this->Size-1)    //�Ƿ���������Ĵ���
		return 0;
	else if(this->GoCoordinates[x][y].flag!=0)
	{	
		//MessageBox(0,L"�˴��Ѿ������ӣ�",L"����",0);   //�˴��д��Ľ�������ʹ���Ի�ؼ����
		return 0;
	}
	if(turn%2==1)
	{
		this->GoCoordinates[x][y].GetGoPlaced(White,coorlist,x,y);
		coorlist->Add(x,y,White);
	}
	else
	{
		this->GoCoordinates[x][y].GetGoPlaced(Black,coorlist,x,y);
	    coorlist->Add(x,y,Black);
	}                                                                               //��������ȱ�����ڣ���������ظ�����

	turn++;                                                                         //��Ϸ�غϼ�1
	/*ȷ�����ӵı�ʶflag*/
	if(this->GoCoordinates[x-1][y].ChangeFlag(&this->GoCoordinates[x][y])==1)       //�������ͬ���ӣ��ı��ʶflag
		reFlag(this->GoCoordinates[x-1][y].flag,this->GoCoordinates[x][y].flag);    //���ȸ���ǰ���ӵķ�0�ı�ʶ��Ȼ��
	if(this->GoCoordinates[x][y+1].ChangeFlag(&this->GoCoordinates[x][y])==1)       //���ݵ�ǰ���ӵı�ʶ��ˢ������
		reFlag(this->GoCoordinates[x][y+1].flag,this->GoCoordinates[x][y].flag);    //��������ͬ�����ڵ����ӡ������е�һ
	if(this->GoCoordinates[x+1][y].ChangeFlag(&this->GoCoordinates[x][y])==1)       //���ж��ƺ��Ƕ���ģ�
		reFlag(this->GoCoordinates[x+1][y].flag,this->GoCoordinates[x][y].flag);
    if(this->GoCoordinates[x][y-1].ChangeFlag(&this->GoCoordinates[x][y])==1)
		reFlag(this->GoCoordinates[x][y-1].flag,this->GoCoordinates[x][y].flag);       
		
	if(this->GoCoordinates[x][y].flag==0)
		this->GoCoordinates[x][y].flag=turn;
	/*�ж����ӵ�����*/
	if(this->GoCoordinates[x][y-1].lifeReduce()==false&&this->GoCoordinates[x][y].flag!=this->GoCoordinates[x][y-1].flag)
		Judge(this->GoCoordinates[x][y-1].flag,coorlist);
	if(this->GoCoordinates[x+1][y].lifeReduce()==false&&this->GoCoordinates[x][y].flag!=this->GoCoordinates[x+1][y].flag)
		Judge(this->GoCoordinates[x+1][y].flag,coorlist);
	if(this->GoCoordinates[x][y+1].lifeReduce()==false&&this->GoCoordinates[x][y].flag!=this->GoCoordinates[x][y+1].flag)
		Judge(this->GoCoordinates[x][y+1].flag,coorlist);
	if(this->GoCoordinates[x-1][y].lifeReduce()==false&&this->GoCoordinates[x][y].flag!=this->GoCoordinates[x-1][y].flag)                            
		Judge(this->GoCoordinates[x-1][y].flag,coorlist);
	//�������if�������й��˵���ͬɫ���ӵ��жϣ����������˴���ִ��Ч�ʣ�Ҳ����˳Ե��������ӵ�bug��
	if(this->GoCoordinates[x][y].life==0)   /*����Ϊ0���������ӵĵط�*/
	{
		int m,n;
		for(m=1;m<this->Size-1;m++)
			for(n=1;n<this->Size-1;n++)
				if(this->GoCoordinates[m][n].flag==this->GoCoordinates[x][y].flag&&this->GoCoordinates[m][n].life!=0)
				    goto End;         //һ��������������0�����ӣ���������

		//�Ƴ��Ѿ��µ������ϵ����ӣ����ָ������ܵ�Ӱ������ӵ�����ֵlife
		this->GoCoordinates[x][y].GetGoPlaced(Empty,coorlist,x,y);
		this->GoCoordinates[x][y].flag=0;
		this->GoCoordinates[x-1][y].life++;
		this->GoCoordinates[x+1][y].life++;
		this->GoCoordinates[x][y+1].life++;
		this->GoCoordinates[x][y-1].life++;
		//MessageBox(0,L"�˴���������",L"����",0);
		turn--;
		return 0;
	}
End:
	return 1;   //��ȷ���ӣ�������		
}