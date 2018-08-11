// Seetxt.cpp : implementation file
//

#include "stdafx.h"
#include "DATAS.h"
#include "Seetxt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Seetxt dialog


Seetxt::Seetxt(CWnd* pParent /*=NULL*/)
	: CDialog(Seetxt::IDD, pParent)
{
	//{{AFX_DATA_INIT(Seetxt)
	m_txt = _T("");
	//}}AFX_DATA_INIT
}


void Seetxt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Seetxt)
	DDX_Text(pDX, IDC_EDIT1, m_txt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Seetxt, CDialog)
	//{{AFX_MSG_MAP(Seetxt)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Seetxt message handlers
