#pragma once
#include "afxcmn.h"


// CDlgLogViewer dialog

class CDlgLogViewer : public CDialog
{
	DECLARE_DYNAMIC(CDlgLogViewer)

public:
	CDlgLogViewer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLogViewer();

// Dialog Data
	enum { IDD = IDD_DIALOG_LOGVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ctrlList;
	virtual BOOL Create(CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
};
