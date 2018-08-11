#if !defined(AFX_SEETXT_H__FE42C169_8A16_4235_9BCD_922FBEF2FE67__INCLUDED_)
#define AFX_SEETXT_H__FE42C169_8A16_4235_9BCD_922FBEF2FE67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Seetxt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Seetxt dialog

class Seetxt : public CDialog
{
// Construction
public:
	Seetxt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Seetxt)
	enum { IDD = IDD_DIALOG2 };
	CString	m_txt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Seetxt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Seetxt)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEETXT_H__FE42C169_8A16_4235_9BCD_922FBEF2FE67__INCLUDED_)
