#if !defined(AFX_SEARCH_H__4F4D347A_6076_43B7_8F2D_1453D96DF62E__INCLUDED_)
#define AFX_SEARCH_H__4F4D347A_6076_43B7_8F2D_1453D96DF62E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Search.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Search dialog

class Search : public CDialog
{
// Construction
public:
	Search(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Search)
	enum { IDD = IDD_DIALOG1 };
	CString	m_Start;
	CString	m_End;
	int		m_isBusy;
	int		m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Search)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Search)
	afx_msg void OnReput();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCH_H__4F4D347A_6076_43B7_8F2D_1453D96DF62E__INCLUDED_)
