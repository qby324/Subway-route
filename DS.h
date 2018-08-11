#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <graphics.h>
#define UN 10000
using namespace std; 
class Line;
class Graphic;
class Station;
class MinHeap;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ReadTxt{						//读取txt中的信息
private:
	ifstream in;
public:
	ReadTxt()
	{
		in.open("BaseInfo4.txt");
	}
	void readn(int &num)
	{
		in>>num;
	}
	void reads(string &str)
	{
		in>>str;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class edge{						//边类
private:		
	int Value;					//边的权值
	int ValueB;
	Station *from;				
	Station *to;
public:
	edge()
	{
		Value=0;
		ValueB=0;
		from=NULL;
		to=NULL;
	}
	edge(Station *from,Station *to)
	{
		this->from=from;
		this->to=to;
	}
	void setFrom(Station* p)
	{
		from=p;
	}
	void setTo(Station* p)
	{
		to=p;
	}
	void setValue(int v)
	{
		this->Value=v;
	}
	void setValueB(int v)
	{
		this->ValueB=v;
	}
	int getValue()
	{
		return Value;
	}
	int getValueB()
	{
		return ValueB;
	}
	Station* getFrom()
	{
		return from;
	}
	Station* getTo()
	{
		return to;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////
class Link							//边的链表
{
public:
	edge* data;
	Link* next;
	Link()
	{
		data=NULL;
		next=NULL;
	}
	Link(edge* data)
	{
		this->data=data;
		next=NULL;
	}
};
class LList
{
public:
	Link *head;
	int edgenumber;
	LList()
	{
		head=NULL;
		edgenumber=0;
	}
	void addedge(edge* e)
	{
		
		edgenumber++;
		Link* temp=new Link(e);
		if(head==NULL)
		{
			head=temp;
		}
		else
		{
			Link* temp2=head;
			while(temp2->next!=NULL)
				temp2=temp2->next;
			temp2->next=temp;
		}
	}
	edge* Findedge(int i)
	{
		Link* temp=head;
		while(i>0)
		{
			temp=temp->next;
			i--;
		}
		return temp->data;
	}

};

//////////////////////////////////////////////////////////////////////////////////////////////
class Station{				//车站类
friend class Graphic;
friend class MinHeap;
private:
	string name;					//  站名	
	LList edgeList;					//边的链表 
	Station* before;					//	寻路中的前驱
	int wayValue;					//  自始发站距离和   0表示未加入集合 -1表示已加入集合但值为无穷大
	int X;							//  站的坐标
	int Y;							//  站的坐标
	bool chosen;					//  是否被选中
	Line *father;					//  属于几号线
public:
	Station()
	{
		name=" ";
		before=NULL;
		wayValue=UN;
		chosen=false;
		X=0;
		Y=0;
		father=NULL;
	}
	Station(string name)
	{
		this->name=name;
		before=NULL;
		wayValue=UN;
		chosen=false;
		X=0;
		Y=0;
		father=NULL;
	}
///////////////////////////////////////////
	void setName(string name)
	{
		this->name=name;
	}
	string getName()
	{
		return name;
	}
	void setBefore(Station *p)
	{
		before=p;
	}
	Station* getBefore()
	{
		return before;
	}	
	void setXY(int x,int y)
	{
		X=x;
		Y=y;
	}
	void getXY(int &x,int &y)
	{
		x=X;
		y=Y;
	}
	void setwayValue(int v)
	{
		wayValue=v;
	}
	int getwayValue()
	{
		return wayValue;
	}
	void setFather(Line *l)
	{
		father=l;
	}
	Line* getFather()
	{
		return father;
	}
	bool getChosen()
	{
		return chosen;
	}
///////////////////////////////////////////
	void LinkTo(Station *p,int v1,int v2)						//建立站间联系
	{
		edge *temp=new edge(this,p);
		temp->setValue(v1);
		temp->setValueB(v2);
		edgeList.addedge(temp);
	}
};		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Line{							//地铁线路类				
friend class MinHeap;
private:
	int num;						//包含站数
	string name;					//线路名称
public:
	Station **HStation;			//包含的站
	Line()
	{
		num=0;
		name=" ";
	}
	~Line()
	{
		delete []HStation;
	}
	void iniLine(int n)
	{
		HStation=new Station*[n];
	}
////////////////////////////////////////////
	void setName(string name)
	{
		this->name=name;
	}
	string getName()
	{
		return name;
	}
	int getNum()
	{
		return num;
	}
	Station* FindStation(string name)
	{
		string temp;
		for(int i=0;i<=num;i++)
		{
			temp=(*HStation[i]).getName();
			if(temp==name)
			{
				return HStation[i];
			}
		}
		return NULL;
	}
///////////////////////////////////////////
	void addStation(Station *p)									//Dijistra算法的路线
	{						
		if(p==0)
		{
			num--;
			return;
		}
		HStation[num++]=p;
	}
	void CreatNewLine(ReadTxt &RT)
	{		
		string S;
		int A[4];
		Station *s=NULL;
		num=0;
		RT.reads(S);
		while(1)
		{	
			if(S=="#")
			{
				num--;
				break;												
			}
			HStation[num]=new Station(S);
			HStation[num]->setFather(this);										
			RT.readn(A[0]);
			RT.readn(A[1]);
			RT.readn(A[2]);
			RT.readn(A[3]);
			HStation[num]->setXY(A[0],A[1]);								
			if(num>0)
			{																
				HStation[num-1]->LinkTo(HStation[num],A[2],A[3]);						
				HStation[num]->LinkTo(HStation[num-1],A[2],A[3]);
			}
			num++;
			RT.reads(S);
		}
	}
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MinHeap
{
private:
	Station **heapArray;
	int CurrentSize;
	int MaxSize;
	void BuildHeap()
	{
		for(int i=CurrentSize/2-1;i>=0;i--)
			SiftDown(i);
	}
	void swap(int pos_x,int pos_y)
	{
		Station *temp=heapArray[pos_x];
		heapArray[pos_x]=heapArray[pos_y];
		heapArray[pos_y]=temp;
	}
	int PassN;		//路径通过节点数，用来创建路径
	int phreshold;
	bool isBusy;
public:
	Line *road;
	Line *road2;
	MinHeap()
	{
		CurrentSize=0;
		MaxSize=0;
		PassN=0;
		phreshold=1000;
	}
	~MinHeap(){delete []heapArray;};
	bool isEmpty();
	bool isLeaf(int pos)
	{
		return (pos>=CurrentSize/2) && (pos<CurrentSize);
	}
	int LeftChild(int pos)
	{
		return 2*pos+1;
	}
	int RightChild(int pos)
	{	
		return 2*pos+2;
	}
	int Parent(int pos)
	{
		return (pos-1)/2;
	}
	bool Remove(int pos,Station *node)
	{
		if((pos<0) || (pos>=CurrentSize))
			return false;
		node=heapArray[pos];
		heapArray[pos]=heapArray[--CurrentSize];
		if(heapArray[Parent(pos)]>heapArray[pos])
			SiftUp(pos);
		else
			SiftDown(pos);
		return true;
	}
	bool Insert(Station *newNode)
	{
		if(CurrentSize==MaxSize)
			return false;
		heapArray[CurrentSize]=newNode;
		SiftUp(CurrentSize);
		CurrentSize++;
		return true;
	}
	Station* RemoveMin()
	{
		if(CurrentSize==0 || heapArray[0]->getwayValue()==UN)
		{
			return NULL;
		}
		else
		{
			swap(0,--CurrentSize);
			if(CurrentSize>1)
				SiftDown(0);
			return heapArray[CurrentSize];
		}
	}
	void SiftUp(int position)
	{
		int temppos=position;
		Station *temp=heapArray[temppos];
		while((temppos>0) && (heapArray[Parent(temppos)]->wayValue > temp->wayValue))
		{
			heapArray[temppos]=heapArray[Parent(temppos)];
			temppos=Parent(temppos);
		}
		heapArray[temppos]=temp;
	}

	void SiftDown(int left)
	{
		int i=left;
		int j=LeftChild(i);
		Station *temp=heapArray[i];
		while(j<CurrentSize)
		{
			if((j<CurrentSize-1) && (heapArray[j]->wayValue>heapArray[j+1]->wayValue))
				j++;
			if(temp->wayValue>heapArray[j]->wayValue)
			{
				heapArray[i]=heapArray[j];
				i=j;
				j=LeftChild(j);
				}
			else
				break;
		}
		heapArray[i]=temp;
	}
	void setMax(int n)
	{
		if(n<=0)
			return;
		CurrentSize=0;
		MaxSize=n;
		heapArray=new Station* [MaxSize];
		for(int i=0;i<n;i++)
			heapArray[i]=NULL;
		PassN=0;
		BuildHeap();
		road= new Line;
		road2=new Line;
		phreshold=1000;
		isBusy=false;
	}
	void setEnd(Station *p)					//设置终点
	{
		if(p==0)
		{
			cout<<"设置的目标地址无效"<<endl;
			return;
		}
		else
		{
			p->chosen=true;
			p->wayValue=0;
			p->before=NULL;
			PassN=1;
			int b=0;
			for(b=0;b<CurrentSize;b++)
				if(heapArray[b]->getChosen()==true)
					break;
			Remove(b,NULL);
		}
		for(int i=0;i<p->edgeList.edgenumber;i++)			//更新终点和终点临界点的权值
		{
			if(isBusy==false)
			{
				p->edgeList.Findedge(i)->getTo()->wayValue=p->edgeList.Findedge(i)->getValue();
				p->edgeList.Findedge(i)->getTo()->before=p;
			}
			else
			{
				p->edgeList.Findedge(i)->getTo()->wayValue=p->edgeList.Findedge(i)->getValueB();
				p->edgeList.Findedge(i)->getTo()->before=p;
			}

		}
		BuildHeap();
	}
	void inaStation(Station *p)
	{
		if(p==0)
		{
			cout<<"点地址无效"<<endl;
			return;
		}
		else			//加入点
		{
			p->chosen=true;
			PassN++;
		}
		for(int i=0;i<p->edgeList.edgenumber;i++)				//更新权值
		{
			int temp;
			if(isBusy==false)
				temp=p->wayValue+p->edgeList.Findedge(i)->getValue();
			else
				temp=p->wayValue+p->edgeList.Findedge(i)->getValueB();
			if(p->edgeList.Findedge(i)->getTo()->wayValue>temp || p->edgeList.Findedge(i)->getTo()->wayValue==UN)			//原权值大于经过该点的权值 或 原不可达
			{
				p->edgeList.Findedge(i)->getTo()->wayValue=temp;
				p->edgeList.Findedge(i)->getTo()->before=p;
			}
		}
		BuildHeap();

	}
	void Dijistra(Station *p)
	{
		while(1)
		{
			p=RemoveMin();
			if(p==NULL)
				break;
			inaStation(p);
		}
	}
	void creatroad(Station *p)
	{
		if(p==0)
		{
			cout<<"错误的起始点"<<endl;
			return;
		}
		PassN++;
    	road->iniLine(PassN);
		while(1)
		{
			road->addStation(p);
			if(p==NULL)
				break;
			p=p->before;
		}
	}
/////////////////////////////////////////////////////////////////////////////////////最佳路线
	void iniMinHeap(Station *p)
	{
		Insert(p);
		for(int i=0;i<MaxSize;i++)
		{
			if(heapArray[i]==NULL)
				break;
			else
			{
				heapArray[i]->chosen=false;
				heapArray[i]->wayValue=UN;
				heapArray[i]->before=NULL;
			}
		}
		CurrentSize=i;
		PassN=0;
	}

	void setEndG(Station *p)					//设置终点
	{
		if(p==0)
		{
			cout<<"设置的目标地址无效"<<endl;
			return;
		}
		else
		{
			p->chosen=true;
			p->wayValue=0;
			p->before=NULL;
			PassN=1;
			int b=0;
			for(b=0;b<CurrentSize;b++)
				if(heapArray[b]->getChosen()==true)
					break;
			Remove(b,NULL);
		}
		for(int i=0;i<p->edgeList.edgenumber;i++)			//更新终点和终点临界点的权值
		{
			if(p->edgeList.Findedge(i)->getTo()->getName()!=p->getName())
			{
				if(isBusy==false)
					p->edgeList.Findedge(i)->getTo()->wayValue=p->edgeList.Findedge(i)->getValue();
				else
					p->edgeList.Findedge(i)->getTo()->wayValue=p->edgeList.Findedge(i)->getValueB();
			}
			else
			{
				if(isBusy==false)
					p->edgeList.Findedge(i)->getTo()->wayValue=p->edgeList.Findedge(i)->getValue()+phreshold;
				else
					p->edgeList.Findedge(i)->getTo()->wayValue=p->edgeList.Findedge(i)->getValueB()+phreshold;
			}
			p->edgeList.Findedge(i)->getTo()->before=p;
		}
		BuildHeap();
	}
	void inaStationG(Station *p)
	{
		if(p==0)
		{
			cout<<"点地址无效"<<endl;
			return;
		}
		else			//加入点
		{
			p->chosen=true;
			PassN++;
		}
		for(int i=0;i<p->edgeList.edgenumber;i++)				//更新权值
		{
			int temp;
			if(p->edgeList.Findedge(i)->getTo()->getName()!=p->getName())
			{
				if(isBusy==false)
					temp=p->wayValue+p->edgeList.Findedge(i)->getValue();
				else
					temp=p->wayValue+p->edgeList.Findedge(i)->getValueB();
			}

			else
			{
				if(isBusy==false)
					temp=p->wayValue+p->edgeList.Findedge(i)->getValue()+phreshold;
				else
					temp=p->wayValue+p->edgeList.Findedge(i)->getValueB()+phreshold;

			}
			if(p->edgeList.Findedge(i)->getTo()->wayValue>temp || p->edgeList.Findedge(i)->getTo()->wayValue==UN)			//原权值大于经过该点的权值 或 原不可达
			{

				p->edgeList.Findedge(i)->getTo()->wayValue=temp;
				p->edgeList.Findedge(i)->getTo()->before=p;
			}
		}
		BuildHeap();

	}
	void DijistraG(Station *p)
	{
		while(1)
		{
			p=RemoveMin();
			if(p==NULL)
				break;
			inaStationG(p);
		}
	}
	void creatroad2(Station *p)
	{
		if(p==0)
		{
			cout<<"错误的起始点"<<endl;
			return;
		}
		PassN++;
    	road2->iniLine(PassN);
		while(1)
		{
			road2->addStation(p);
			if(p==NULL)
				break;
			p=p->before;
		}
	}
	void setBusy(bool b)
	{
		isBusy=b;
	}
	int getphreshold()
	{
		return phreshold;
	}
};
//////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////