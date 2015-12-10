//#include"StdAfx.h"
#include"CCoordinateListView.h"
#include"CGo.h"



/**************************GoCoordinate类的实现************************/
GoCoordinate::GoCoordinate()
{
	life=4;
	flag=0;
}

bool GoCoordinate::lifeReduce()
{
	life--;         
	if(life==0&&flag!=0)  //非空的坐标且life为0，过滤那些空坐标有助于提高效率
		return false;
	else
		return true;
}

int GoCoordinate::ChangeFlag(GoCoordinate *Direction)
{
	if(state==Direction->state)
		if(Direction->flag==0)
		{
			Direction->flag=flag;//flag，大者优先,先于棋盘者优先；难点：考虑多块棋子连接到一起的情形
		    return 0;
		}
		else
			return 1;           //两“块”同色棋子相遇；
	else
		return -1;              //非同色棋子
}

void GoCoordinate::GetGoPlaced(int Color,CoorList *coorlist,int x,int y)
{
	state=Color;
	if(Color==Empty)
		coorlist->Del(x,y);
}

/****************************Chessboard类的实现***************************/
Chessboard::Chessboard(int RealSize)
{
	this->Size=RealSize+2;
	this->turn=0;

	this->GoCoordinates=new GoCoordinate*[Size];
	int i;
	for(i=0;i<Size;i++)
		GoCoordinates[i]=new GoCoordinate[Size];

	for(i=1;i<Size-1;i++)                              //处理棋盘边界问题,并为各坐标之间建立联系
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

void Chessboard::Judge(int flag,CoorList *coorlist)                            //判断棋子是否生存,提子
{
	int i,j;
	for(i=1;i<this->Size-1;i++)
		for(j=1;j<this->Size-1;j++)
			if(this->GoCoordinates[i][j].flag==flag&&this->GoCoordinates[i][j].life!=0)
				return;                   //一旦发现有气数非0的棋子，马上跳出判断
	for(i=1;i<this->Size-1;i++)
		for(j=1;j<this->Size-1;j++)		  //此段代码有待优化,容易造成过多的重复判断,此段程序，本可用数组将棋子地址存放，但个人认为应该尽可能多利用cpu而不是内存
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
/***ChangFlag函数的功能补充函数：刷新棋盘上的所有相同且相临的棋子的flag值***/
/********这个函数的代价在于：需要刷新整个棋盘，效率低下，但实现简单*********/
{
	int i,j;
	for(i=0;i<this->Size-1;i++)
		for(j=0;j<this->Size-1;j++)
			if(this->GoCoordinates[i][j].flag==flagOld)
				this->GoCoordinates[i][j].flag=flagNew;
}

int Chessboard::Put(int x,int y,CoorList *coorlist)
{	
	//处理x和y坐标,将他们转化为逻辑坐标：
	x=x/coorlist->Distance+1;
	y=y/coorlist->Distance+1;

	int i=0;
	if(x<=0||x>=this->Size-1||y<=0||y>=this->Size-1)    //非法落子区域的处理
		return 0;
	else if(this->GoCoordinates[x][y].flag!=0)
	{	
		//MessageBox(0,L"此处已经有棋子！",L"警告",0);   //此处有待改进，若能使用自绘控件最好
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
	}                                                                               //这样做的缺陷在于，做了许多重复工作

	turn++;                                                                         //游戏回合加1
	/*确定棋子的标识flag*/
	if(this->GoCoordinates[x-1][y].ChangeFlag(&this->GoCoordinates[x][y])==1)       //如果是相同棋子，改变标识flag
		reFlag(this->GoCoordinates[x-1][y].flag,this->GoCoordinates[x][y].flag);    //首先给当前棋子的非0的标识，然后，
	if(this->GoCoordinates[x][y+1].ChangeFlag(&this->GoCoordinates[x][y])==1)       //根据当前棋子的标识，刷新整个
		reFlag(this->GoCoordinates[x][y+1].flag,this->GoCoordinates[x][y].flag);    //棋盘上相同且相邻的棋子。（其中第一
	if(this->GoCoordinates[x+1][y].ChangeFlag(&this->GoCoordinates[x][y])==1)       //个判断似乎是多余的）
		reFlag(this->GoCoordinates[x+1][y].flag,this->GoCoordinates[x][y].flag);
    if(this->GoCoordinates[x][y-1].ChangeFlag(&this->GoCoordinates[x][y])==1)
		reFlag(this->GoCoordinates[x][y-1].flag,this->GoCoordinates[x][y].flag);       
		
	if(this->GoCoordinates[x][y].flag==0)
		this->GoCoordinates[x][y].flag=turn;
	/*判断棋子的生死*/
	if(this->GoCoordinates[x][y-1].lifeReduce()==false&&this->GoCoordinates[x][y].flag!=this->GoCoordinates[x][y-1].flag)
		Judge(this->GoCoordinates[x][y-1].flag,coorlist);
	if(this->GoCoordinates[x+1][y].lifeReduce()==false&&this->GoCoordinates[x][y].flag!=this->GoCoordinates[x+1][y].flag)
		Judge(this->GoCoordinates[x+1][y].flag,coorlist);
	if(this->GoCoordinates[x][y+1].lifeReduce()==false&&this->GoCoordinates[x][y].flag!=this->GoCoordinates[x][y+1].flag)
		Judge(this->GoCoordinates[x][y+1].flag,coorlist);
	if(this->GoCoordinates[x-1][y].lifeReduce()==false&&this->GoCoordinates[x][y].flag!=this->GoCoordinates[x-1][y].flag)                            
		Judge(this->GoCoordinates[x-1][y].flag,coorlist);
	//在这里，在if的条件中过滤掉对同色棋子的判断，不仅增加了代码执行效率，也免除了吃掉己方棋子的bug。
	if(this->GoCoordinates[x][y].life==0)   /*气数为0，不可落子的地方*/
	{
		int m,n;
		for(m=1;m<this->Size-1;m++)
			for(n=1;n<this->Size-1;n++)
				if(this->GoCoordinates[m][n].flag==this->GoCoordinates[x][y].flag&&this->GoCoordinates[m][n].life!=0)
				    goto End;         //一旦发现有气数非0的棋子，马上跳出

		//移除已经下到棋牌上的棋子，并恢复其他受到影响的棋子的生命值life
		this->GoCoordinates[x][y].GetGoPlaced(Empty,coorlist,x,y);
		this->GoCoordinates[x][y].flag=0;
		this->GoCoordinates[x-1][y].life++;
		this->GoCoordinates[x+1][y].life++;
		this->GoCoordinates[x][y+1].life++;
		this->GoCoordinates[x][y-1].life++;
		//MessageBox(0,L"此处不可落子",L"警告",0);
		turn--;
		return 0;
	}
End:
	return 1;   //正确落子，返回真		
}