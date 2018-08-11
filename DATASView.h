// DATASView.h : interface of the CDATASView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATASVIEW_H__7606C27A_D02C_41BE_9DAC_158C25118BAC__INCLUDED_)
#define AFX_DATASVIEW_H__7606C27A_D02C_41BE_9DAC_158C25118BAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DS.h"
#include "Search.h"
#include "Seetxt.h"
class CDATASView : public CView
{
protected: // create from serialization only
	CDATASView();
	DECLARE_DYNCREATE(CDATASView)

// Attributes
public:
	CDATASDoc* GetDocument();

// Operations
public:
	MinHeap *G;
	CString Start;
	CString End;
	int Busy;
	Line *l;
	int Linenum;
	bool Paint;
	int totalStation;
	int type;
	CString txt;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATASView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDATASView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDATASView)
	afx_msg void OnMsearch();
	afx_msg void OnMseetxt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DATASView.cpp
inline CDATASDoc* CDATASView::GetDocument()
   { return (CDATASDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASVIEW_H__7606C27A_D02C_41BE_9DAC_158C25118BAC__INCLUDED_)
