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
	m_listCnt = 0;
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

	m_ctrlList.InsertColumn(0, _T("File ID"), LVCFMT_CENTER, 100);
	m_ctrlList.InsertColumn(1, _T("Threshold"), LVCFMT_CENTER, 100);
	m_ctrlList.InsertColumn(2, _T("Accuracy"), LVCFMT_CENTER, 100);
	m_ctrlList.InsertColumn(3, _T("X"), LVCFMT_CENTER, 100);
	m_ctrlList.InsertColumn(4, _T("Y"), LVCFMT_CENTER, 100);



	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgLogViewer::AddLogList()
{
	m_ctrlList.DeleteAllItems();
	m_listCnt = 0;

	CString sPath;
	GetModuleFileName(nullptr, sPath.GetBuffer(_MAX_PATH + 1), _MAX_PATH);
	sPath.ReleaseBuffer();
	CString path = sPath.Left(sPath.ReverseFind(_T('\\')));
	path += "\\logdata";



	CFileFind file_find;
	BOOL bWorking;
	bWorking = file_find.FindFile(path + ("\\*.jpg"));


	float sTh = 0.6f;
	//	CString strLogFile = _T("");
	while (bWorking)
	{
		bWorking = file_find.FindNextFile();
		if (!file_find.IsDots()){
			CString filePath = file_find.GetFilePath();
			int loc = filePath.Find(_T("."));
			filePath.Delete(loc, 4);

			FILE* fp;
			fopen_s(&fp, (CStringA)filePath, "rb");
			if (fp){
				unsigned int resSize = 0;
				unsigned int nCode = 0;
				float fTh = 0.0f;

				CString strCode, strFth;
				

				CString strTmp;
				float x, y, z, a;

				while (!feof(fp)){
					fread(&nCode, sizeof(int), 1, fp);
					fread(&resSize, sizeof(int), 1, fp);
					fread(&fTh, sizeof(float), 1, fp);

					strCode.Format(_T("%u"), nCode);
					strFth.Format(_T("%3.2f"), fTh);

					


					for (int i = 0; i < resSize; i++){

						fread(&x, sizeof(float), 1, fp);
						fread(&y, sizeof(float), 1, fp);
						fread(&z, sizeof(float), 1, fp);
						fread(&a, sizeof(float), 1, fp);


						m_ctrlList.InsertItem(m_listCnt, strCode, 0);
						m_ctrlList.SetItemText(m_listCnt, 1, strFth);

						strTmp.Format(_T("%3.2f"), a);			m_ctrlList.SetItemText(m_listCnt, 2, strTmp);
						strTmp.Format(_T("%3.2f"), x);			m_ctrlList.SetItemText(m_listCnt, 3, strTmp);
						strTmp.Format(_T("%3.2f"), y);			m_ctrlList.SetItemText(m_listCnt, 4, strTmp);

						m_listCnt++;

					//	if (m_listCnt > 500)
					//		break;
					}			

				//	if (m_listCnt > 500)
				//		break;
				}
				fclose(fp);
			}			
		}
	}
	return TRUE;
}