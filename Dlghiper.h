//{{AFX_INCLUDES()
#include "msdgridctrl.h"
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGHIPER_H__4DF84DC1_9007_4418_AE0E_C15998A2F962__INCLUDED_)
#define AFX_DLGHIPER_H__4DF84DC1_9007_4418_AE0E_C15998A2F962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlghiper.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlghiper dialog

class CDlghiper : public CDialog
{
// Construction
public:
	void OnTimer(UINT nIDEvent);
	CDlghiper(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlghiper)
	enum { IDD = IDD_DLGhiper };
	CListBox	m_Output;
	CButton	m_BTNWrite;
	CButton	m_BTNDisconnect;
	CButton	m_BTNConnect;
	CEdit	m_FileName;
	CMSFlexGrid	m_Grid;
	int cur_n;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlghiper)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlghiper)
	afx_msg void OnBTNConnect();
	afx_msg void OnBTNWrite();
	virtual BOOL OnInitDialog();
	afx_msg void OnBTNDisconnect();
	afx_msg void OnBTNOpenFile();
	afx_msg void OnBTNPause();
	afx_msg void OnBTNHome();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHIPER_H__4DF84DC1_9007_4418_AE0E_C15998A2F962__INCLUDED_)
