// DlgLogViewer.cpp : implementation file
//

#include "stdafx.h"
#include "CutNSearch.h"
#include "DlgLogViewer.h"
#include "afxdialogex.h"


// CDlgLogViewer dialog

IMPLEMENT_DYNAMIC(CDlgLogViewer, CDialog)

CDlgLogViewer::CDlgLogViewer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogViewer::IDD, pParent)
{

}

CDlgLogViewer::~CDlgLogViewer()
{
}

void CDlgLogViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CDlgLogViewer, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDlgLogViewer::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CDlgLogViewer message handlers


void CDlgLogViewer::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


BOOL CDlgLogViewer::Create(CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(IDD, pParentWnd);
}


BOOL CDlgLogViewer::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CenterWindow();

	m_ctrlList.InsertColumn(0, _T("File ID"), LVCFMT_CENTER, 70);
	m_ctrlList.InsertColumn(1, _T("Threshold"), LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(2, _T("Accuracy"), LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(3, _T("X"), LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(4, _T("Y"), LVCFMT_CENTER, 50);



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
