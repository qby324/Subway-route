// DATAS.h : main header file for the DATAS application
//

#if !defined(AFX_DATAS_H__D8255538_15C2_4971_BC69_05DF35D3E4A6__INCLUDED_)
#define AFX_DATAS_H__D8255538_15C2_4971_BC69_05DF35D3E4A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDATASApp:
// See DATAS.cpp for the implementation of this class
//

class CDATASApp : public CWinApp
{
public:
	CDATASApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATASApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDATASApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAS_H__D8255538_15C2_4971_BC69_05DF35D3E4A6__INCLUDED_)
