// DATASView.cpp : implementation of the CDATASView class
//

#include "stdafx.h"
#include "DATAS.h"

#include "DATASDoc.h"
#include "DATASView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDATASView

IMPLEMENT_DYNCREATE(CDATASView, CView)

BEGIN_MESSAGE_MAP(CDATASView, CView)
	//{{AFX_MSG_MAP(CDATASView)
	ON_COMMAND(ID_MSEARCH, OnMsearch)
	ON_COMMAND(ID_MSEETXT, OnMseetxt)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDATASView construction/destruction

CDATASView::CDATASView()
{
	// TODO: add construction code here
	type=0;
	totalStation=0;
	Paint=false;
	int Transnumber=0;					//换乘站数
	int StationNumber=0;
	ReadTxt R;							//读取文件
	R.readn(Linenum);
	l=new Line[Linenum];			//存储具体数据的线路类
	for(int i=0;i<Linenum;i++)				//读线路数据
	{		
		string S;
		R.reads(S);
		R.readn(StationNumber);
		totalStation+=StationNumber;
		l[i].iniLine(StationNumber);
		l[i].setName(S);
		l[i].CreatNewLine(R);
	}
	R.readn(Transnumber);
	for(i=0;i<Transnumber;i++)				//读换乘数据
	{
		string S;
		int a[4];
		Station *s1=0,*s2=0;
		R.reads(S);
		R.readn(a[0]);
		R.readn(a[1]);
		R.readn(a[2]);
		R.readn(a[3]);
		s1=l[a[0]].FindStation(S);
		s2=l[a[1]].FindStation(S);
		if(s1==0 || s2==0)
		{
			cout<<"errotransfstation"<<endl;
			break;
		}
		s1->LinkTo(s2,a[2],a[3]);
		s2->LinkTo(s1,a[2],a[3]);
	}

}

CDATASView::~CDATASView()
{
}

BOOL CDATASView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDATASView drawing

void CDATASView::OnDraw(CDC* pDC)
{
	CDATASDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
////////////////////////////////////////////////////////////////读入地图
	CBitmap bitmap;
	CDC dcmemory;
	bitmap.LoadBitmap(IDB_SUBWAY);
	dcmemory.CreateCompatibleDC(pDC);
	dcmemory.SelectObject(&bitmap);
	pDC->BitBlt(5,5,1505,1005,&dcmemory,0,0,SRCCOPY);
//////////////////////////////////////////////////////////////////计算路径
	if(Paint==true)
	{
		CString temp;
		txt="";
		G=new MinHeap;
		G->setMax(totalStation);
		int i;
		for(i=0;i<Linenum;i++)
			for(int c=0;c<l[i].getNum();c++)
					G->Insert(l[i].HStation[c]);
		Station *F=NULL;
		Station *T=NULL;
		if(Busy==0)
			G->setBusy(true);
		else
			G->setBusy(false);
		for(i=0;i<Linenum;i++)
		{						
			F=l[i].FindStation(string(Start));
			if(F!=NULL)
				break;
		}
		for(i=0;i<Linenum;i++)
		{					
			T=l[i].FindStation(string(End));
			if(T!=0)
				break;
		}
		if(F==NULL||T==NULL)
		{
			AfxMessageBox("输入站名错误！");
			exit(0);
		}
		G->setEnd(T);
		G->Dijistra(T);
		G->creatroad(F);
		G->iniMinHeap(T);
		G->setEndG(T);
		G->DijistraG(T);
		G->creatroad2(F);
/////////////////////////////////////////////////////////////画出路线
		CPen newPen(PS_SOLID,5,RGB(0,255,100));
		pDC->SelectObject(&newPen);
		int x,y;
		if(type==0)								//最短时间
		{
			G->road->HStation[0]->getXY(x,y);
			pDC->MoveTo(x,y);
			for(int c=0;c<=G->road->getNum();c++)
			{	
				G->road->HStation[c]->getXY(x,y);
				pDC->LineTo(x,y);
				pDC->MoveTo(x,y);
			}
			CPen newPen2(PS_SOLID,5,RGB(255,0,0));
			pDC->SelectObject(&newPen2);
			G->road->HStation[0]->getXY(x,y);
			pDC->Ellipse(x-4,y-4,x+4,y+4);
			CPen newPen3(PS_SOLID,5,RGB(0,0,255));
			pDC->SelectObject(&newPen3);
			G->road->HStation[c-1]->getXY(x,y);
			pDC->Ellipse(x-4,y-4,x+4,y+4);
///////////////////////////////////////////////////////////////增加文字
			int n=1;
			for(int i=0;i<=G->road->getNum();i++)
			{
				if(i<G->road->getNum() && G->road->HStation[i]->getFather()!=G->road->HStation[i+1]->getFather())			//换乘站
				{
					temp.Format("%d",i+n);
					txt+="第";txt+=temp;txt+="站";
					txt+="(换乘站)";txt+=G->road->HStation[i]->getName().c_str();txt+="\t由 ";
					txt+=G->road->HStation[i]->getFather()->getName().c_str();txt+=" 换乘 ";
					txt+=G->road->HStation[i+1]->getFather()->getName().c_str();txt+="\r\n";
					i++;
					n--;
					continue;
				}
				if(i!=0 && i!=G->road->getNum())		//不是起点或终点站
				{
					temp.Format("%d",i+n);
					txt+="第";txt+=temp;txt+="站\t";
				}
				else
				{
					if(i==0)
						txt+="起点站\t";
					else
						txt+="终点站\t";
				}
				txt+=G->road->HStation[i]->getName().c_str();txt+="\t";
				txt+=G->road->HStation[i]->getFather()->getName().c_str();txt+="\r\n";
			}
			int a=G->road->HStation[0]->getwayValue();
			while(a>G->getphreshold()+50)
				a-=G->getphreshold();
			temp.Format("%d",a);
			txt+="共计:	";txt+=temp;txt+="分钟\r\n";
			temp.Format("%d",G->road->getNum()+n);
			txt+="共计:	";txt+=temp;txt+="站\t";txt+="换乘:\t";
			temp.Format("%d",1-n);
			txt+=temp;txt+="次\r\n";
		}
		else                                                          //最少换乘
		{
			G->road2->HStation[0]->getXY(x,y);
			pDC->MoveTo(x,y);
			for(int c=0;c<=G->road2->getNum();c++)
			{	
				G->road2->HStation[c]->getXY(x,y);
				pDC->LineTo(x,y);
				pDC->MoveTo(x,y);
			}
			CPen newPen2(PS_SOLID,5,RGB(255,0,0));
			pDC->SelectObject(&newPen2);
			G->road2->HStation[0]->getXY(x,y);
			pDC->Ellipse(x-4,y-4,x+4,y+4);
			CPen newPen3(PS_SOLID,5,RGB(0,0,255));
			pDC->SelectObject(&newPen3);
			G->road2->HStation[c-1]->getXY(x,y);
			pDC->Ellipse(x-4,y-4,x+4,y+4);
//////////////////////////////////////////////////////////////////////
			int n=1;
			for(int i=0;i<=G->road2->getNum();i++)
			{
				if(i<G->road2->getNum() && G->road2->HStation[i]->getFather()!=G->road2->HStation[i+1]->getFather())			//换乘站
				{
					temp.Format("%d",i+n);
					txt+="第";txt+=temp;txt+="站";
					txt+="(换乘站)";txt+=G->road2->HStation[i]->getName().c_str();txt+="\t由 ";
					txt+=G->road2->HStation[i]->getFather()->getName().c_str();txt+=" 换乘 ";
					txt+=G->road2->HStation[i+1]->getFather()->getName().c_str();txt+="\r\n";
					i++;
					n--;
					continue;
				}
				if(i!=0 && i!=G->road2->getNum())		//不是起点或终点站
				{
					temp.Format("%d",i+n);
					txt+="第";txt+=temp;txt+="站\t";
				}
				else
				{
					if(i==0)
						txt+="起点站\t";
					else
						txt+="终点站\t";
				}
				txt+=G->road2->HStation[i]->getName().c_str();txt+="\t";
				txt+=G->road2->HStation[i]->getFather()->getName().c_str();txt+="\r\n";
			}
			int a=G->road2->HStation[0]->getwayValue();
			while(a>G->getphreshold()+50)
				a-=G->getphreshold();
			temp.Format("%d",a);
			txt+="共计:	";txt+=temp;txt+="分钟\r\n";
			temp.Format("%d",G->road2->getNum()+n);
			txt+="共计:	";txt+=temp;txt+="站\t";txt+="换乘:\t";
			temp.Format("%d",1-n);
			txt+=temp;txt+="次\r\n";
		}
		delete G;
		
	}

}

/////////////////////////////////////////////////////////////////////////////
// CDATASView printing

BOOL CDATASView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDATASView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDATASView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDATASView diagnostics

#ifdef _DEBUG
void CDATASView::AssertValid() const
{
	CView::AssertValid();
}

void CDATASView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDATASDoc* CDATASView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDATASDoc)));
	return (CDATASDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDATASView message handlers

void CDATASView::OnMsearch() 
{
	// TODO: Add your command handler code here
	Search dlg;
	dlg.m_Start=Start;
	dlg.m_End=End;
	dlg.m_isBusy=Busy;
	dlg.m_type=type;
	if(dlg.DoModal()==IDOK)
	{
		Start=dlg.m_Start;
		End=dlg.m_End;
		Busy=dlg.m_isBusy;
		type=dlg.m_type;
		Paint=true;
	}
	else
		Paint=false;
	Invalidate(TRUE);
	
}

void CDATASView::OnMseetxt() 
{
	// TODO: Add your command handler code here
	Seetxt dlg;
	dlg.m_txt=txt;
	dlg.DoModal();
}
