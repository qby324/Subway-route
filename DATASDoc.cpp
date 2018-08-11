// DATASDoc.cpp : implementation of the CDATASDoc class
//

#include "stdafx.h"
#include "DATAS.h"

#include "DATASDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDATASDoc

IMPLEMENT_DYNCREATE(CDATASDoc, CDocument)

BEGIN_MESSAGE_MAP(CDATASDoc, CDocument)
	//{{AFX_MSG_MAP(CDATASDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDATASDoc construction/destruction

CDATASDoc::CDATASDoc()
{
	// TODO: add one-time construction code here

}

CDATASDoc::~CDATASDoc()
{
}

BOOL CDATASDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDATASDoc serialization

void CDATASDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDATASDoc diagnostics

#ifdef _DEBUG
void CDATASDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDATASDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDATASDoc commands
