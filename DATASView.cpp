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
	int Transnumber=0;					//����վ��
	int StationNumber=0;
	ReadTxt R;							//��ȡ�ļ�
	R.readn(Linenum);
	l=new Line[Linenum];			//�洢�������ݵ���·��
	for(int i=0;i<Linenum;i++)				//����·����
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
	for(i=0;i<Transnumber;i++)				//����������
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
////////////////////////////////////////////////////////////////�����ͼ
	CBitmap bitmap;
	CDC dcmemory;
	bitmap.LoadBitmap(IDB_SUBWAY);
	dcmemory.CreateCompatibleDC(pDC);
	dcmemory.SelectObject(&bitmap);
	pDC->BitBlt(5,5,1505,1005,&dcmemory,0,0,SRCCOPY);
//////////////////////////////////////////////////////////////////����·��
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
			AfxMessageBox("����վ������");
			exit(0);
		}
		G->setEnd(T);
		G->Dijistra(T);
		G->creatroad(F);
		G->iniMinHeap(T);
		G->setEndG(T);
		G->DijistraG(T);
		G->creatroad2(F);
/////////////////////////////////////////////////////////////����·��
		CPen newPen(PS_SOLID,5,RGB(0,255,100));
		pDC->SelectObject(&newPen);
		int x,y;
		if(type==0)								//���ʱ��
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
///////////////////////////////////////////////////////////////��������
			int n=1;
			for(int i=0;i<=G->road->getNum();i++)
			{
				if(i<G->road->getNum() && G->road->HStation[i]->getFather()!=G->road->HStation[i+1]->getFather())			//����վ
				{
					temp.Format("%d",i+n);
					txt+="��";txt+=temp;txt+="վ";
					txt+="(����վ)";txt+=G->road->HStation[i]->getName().c_str();txt+="\t�� ";
					txt+=G->road->HStation[i]->getFather()->getName().c_str();txt+=" ���� ";
					txt+=G->road->HStation[i+1]->getFather()->getName().c_str();txt+="\r\n";
					i++;
					n--;
					continue;
				}
				if(i!=0 && i!=G->road->getNum())		//���������յ�վ
				{
					temp.Format("%d",i+n);
					txt+="��";txt+=temp;txt+="վ\t";
				}
				else
				{
					if(i==0)
						txt+="���վ\t";
					else
						txt+="�յ�վ\t";
				}
				txt+=G->road->HStation[i]->getName().c_str();txt+="\t";
				txt+=G->road->HStation[i]->getFather()->getName().c_str();txt+="\r\n";
			}
			int a=G->road->HStation[0]->getwayValue();
			while(a>G->getphreshold()+50)
				a-=G->getphreshold();
			temp.Format("%d",a);
			txt+="����:	";txt+=temp;txt+="����\r\n";
			temp.Format("%d",G->road->getNum()+n);
			txt+="����:	";txt+=temp;txt+="վ\t";txt+="����:\t";
			temp.Format("%d",1-n);
			txt+=temp;txt+="��\r\n";
		}
		else                                                          //���ٻ���
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
				if(i<G->road2->getNum() && G->road2->HStation[i]->getFather()!=G->road2->HStation[i+1]->getFather())			//����վ
				{
					temp.Format("%d",i+n);
					txt+="��";txt+=temp;txt+="վ";
					txt+="(����վ)";txt+=G->road2->HStation[i]->getName().c_str();txt+="\t�� ";
					txt+=G->road2->HStation[i]->getFather()->getName().c_str();txt+=" ���� ";
					txt+=G->road2->HStation[i+1]->getFather()->getName().c_str();txt+="\r\n";
					i++;
					n--;
					continue;
				}
				if(i!=0 && i!=G->road2->getNum())		//���������յ�վ
				{
					temp.Format("%d",i+n);
					txt+="��";txt+=temp;txt+="վ\t";
				}
				else
				{
					if(i==0)
						txt+="���վ\t";
					else
						txt+="�յ�վ\t";
				}
				txt+=G->road2->HStation[i]->getName().c_str();txt+="\t";
				txt+=G->road2->HStation[i]->getFather()->getName().c_str();txt+="\r\n";
			}
			int a=G->road2->HStation[0]->getwayValue();
			while(a>G->getphreshold()+50)
				a-=G->getphreshold();
			temp.Format("%d",a);
			txt+="����:	";txt+=temp;txt+="����\r\n";
			temp.Format("%d",G->road2->getNum()+n);
			txt+="����:	";txt+=temp;txt+="վ\t";txt+="����:\t";
			temp.Format("%d",1-n);
			txt+=temp;txt+="��\r\n";
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
