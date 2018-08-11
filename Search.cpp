// Search.cpp : implementation file
//

#include "stdafx.h"
#include "DATAS.h"
#include "Search.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Search dialog


Search::Search(CWnd* pParent /*=NULL*/)
	: CDialog(Search::IDD, pParent)
{
	//{{AFX_DATA_INIT(Search)
	m_Start = _T("");
	m_End = _T("");
	m_isBusy = -1;
	m_type = -1;
	//}}AFX_DATA_INIT
}


void Search::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Search)
	DDX_Text(pDX, IDC_EDIT1, m_Start);
	DDX_Text(pDX, IDC_EDIT2, m_End);
	DDX_Radio(pDX, IDC_RADIO1, m_isBusy);
	DDX_Radio(pDX, IDC_RADIO3, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Search, CDialog)
	//{{AFX_MSG_MAP(Search)
	ON_BN_CLICKED(IDC_REPUT, OnReput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Search message handlers

void Search::OnReput() 
{
	// TODO: Add your control notification handler code here
	m_Start="";
	m_End="";
	m_isBusy=0;
	m_type=0;
	UpdateData(FALSE);
	
}

BOOL Search::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Start="";
	m_End="";
	m_isBusy=0;
	m_type=0;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
