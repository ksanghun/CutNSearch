#pragma once


// CLogListCtrl

class CLogListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CLogListCtrl)

public:
	CLogListCtrl();
	virtual ~CLogListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


