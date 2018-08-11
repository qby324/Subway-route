// DATASDoc.h : interface of the CDATASDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATASDOC_H__7B1D14AF_AB65_46A8_B7EA_CB9229BE6955__INCLUDED_)
#define AFX_DATASDOC_H__7B1D14AF_AB65_46A8_B7EA_CB9229BE6955__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDATASDoc : public CDocument
{
protected: // create from serialization only
	CDATASDoc();
	DECLARE_DYNCREATE(CDATASDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDATASDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDATASDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDATASDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASDOC_H__7B1D14AF_AB65_46A8_B7EA_CB9229BE6955__INCLUDED_)
