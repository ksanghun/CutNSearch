// LogListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "CutNSearch.h"
#include "LogListCtrl.h"
#include "MainFrm.h"


// CLogListCtrl

IMPLEMENT_DYNAMIC(CLogListCtrl, CListCtrl)

CLogListCtrl::CLogListCtrl()
{

}

CLogListCtrl::~CLogListCtrl()
{
}


BEGIN_MESSAGE_MAP(CLogListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CLogListCtrl::OnNMDblclk)
END_MESSAGE_MAP()



// CLogListCtrl message handlers




void CLogListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = GetItemText(pNMLV->iItem, 1);

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->AddLogResult(str);


	*pResult = 0;
}
