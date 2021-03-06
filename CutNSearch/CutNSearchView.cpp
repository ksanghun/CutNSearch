
// CutNSearchView.cpp : implementation of the CCutNSearchView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CutNSearch.h"
#endif

#include "CutNSearchDoc.h"
#include "CutNSearchView.h"
#include "MainFrm.h"
#include "afxbasetabctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCutNSearchView


IMPLEMENT_DYNCREATE(CCutNSearchView, CView)

BEGIN_MESSAGE_MAP(CCutNSearchView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_RENDER_SORTBYGROUP, &CCutNSearchView::OnRenderSortbygroup)
	ON_COMMAND(ID_RENDER_SORTBYORDER, &CCutNSearchView::OnRenderSortbyorder)
	ON_COMMAND(ID_IMAGE_CLEARIMAGES, &CCutNSearchView::OnImageClearimages)
END_MESSAGE_MAP()

// CCutNSearchView construction/destruction
CCutNSearchView* pView = nullptr;

CCutNSearchView::CCutNSearchView()
{
	// TODO: add construction code here
	pView = this;

	m_pImageView = NULL;
	pDlg = NULL;
	
}

CCutNSearchView::~CCutNSearchView()
{
	if (m_pImageView != nullptr){
		delete m_pImageView;
	}

	if (pDlg != nullptr){
		delete pDlg;
	}


}

BOOL CCutNSearchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCutNSearchView drawing

void CCutNSearchView::OnDraw(CDC* /*pDC*/)
{
	//CCutNSearchDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;
	// TODO: add draw code for native data here
}

void CCutNSearchView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCutNSearchView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCutNSearchView diagnostics

#ifdef _DEBUG
void CCutNSearchView::AssertValid() const
{
	CView::AssertValid();
}

void CCutNSearchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

//CCutNSearchDoc* CCutNSearchView::GetDocument() const // non-debug version is inline
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCutNSearchDoc)));
//	return (CCutNSearchDoc*)m_pDocument;
//}
#endif //_DEBUG


// CCutNSearchView message handlers


int CCutNSearchView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect cRect;
	GetWindowRect(&cRect);


	// Create tab ctrl //
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_ctrlTab.Create(CMFCTabCtrl::STYLE_3D_ROUNDED, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	if (m_pImageView == nullptr){
		m_pImageView = new CImageView;
	//	m_pImageView->Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE, cRect, this, 0x01);
		m_pImageView->Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE, cRect, &m_ctrlTab, 0x01);
		m_pImageView->InitGLview(0, 0);
	}

	m_ctrlTab.AddTab(m_pImageView, L"2D View", (UINT)0);

	if (pDlg == NULL){
		pDlg = new CDlgCutNSearch;
		pDlg->Create(this);
		pDlg->ShowWindow(SW_HIDE);
	}
	return 0;
}


void CCutNSearchView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_ctrlTab.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrlTab.SetLocation(CMFCTabCtrl::LOCATION_TOP);

	//if (m_pImageView){
	//	m_pImageView->MoveWindow(0, 0, cx, cy);
	//}
}

void CCutNSearchView::AddSNImage(CString str)
{
	//if (m_pImageView){
	//	m_pImageView->LoadSNImage(str);
	//}

}

void CCutNSearchView::ShowCNSDlg(int _th)
{	
	pDlg->ShowWindow(SW_SHOW);
	pDlg->SetSliderPos(_th);
}

void CCutNSearchView::SetDlgImagePath(CString str)
{
	pDlg->SetSNImage(str);
}

void CCutNSearchView::SetTreeDragItem(CImageList* pImage, HTREEITEM hItem, CViewTree* pCtrl)
{
	if (m_pImageView){
		m_pImageView->SetTreeDragItem(pImage, hItem, pCtrl);
	}
}

void CCutNSearchView::RenderImageView()
{
	if (m_pImageView){
		m_pImageView->Render();
	}
}


void CCutNSearchView::DoCNSearchForPixelMap(IplImage *ptemp)
{
	if (m_pImageView){
		m_pImageView->StartCNSearchAll(ptemp);
	}

}

void CCutNSearchView::DoCNSearch(IplImage *ptemp, bool IsKeyword)
{
	if (m_pImageView){
		m_pImageView->StartCNSearch(ptemp, IsKeyword);
	}

}

void CCutNSearchView::SetThreshold(int _value)
{
	if (m_pImageView){
		m_pImageView->SetThreshold(_value);
	}
}

float CCutNSearchView::GetGhreshold()
{	
	return	m_pImageView->GetThreshold();
}

IplImage* CCutNSearchView::ExtractTempleteFromResult()
{
	if (m_pImageView){
		return m_pImageView->ExtractAverTempleteFromResult();
	}
	return NULL;
}



BOOL CCutNSearchView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (m_pImageView){
		m_pImageView->MouseWheel(zDelta);
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CCutNSearchView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == 17){  // ctrl key dowon
		if (m_pImageView){
			m_pImageView->SetIconMode(true);
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CCutNSearchView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 17){  // ctrl key dowon
		if (m_pImageView){
			m_pImageView->SetIconMode(false);
		}
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CCutNSearchView::OnRenderSortbygroup()
{
	// TODO: Add your command handler code here
	if (m_pImageView){
		m_pImageView->SetRenderMode(_BYGROUP);
	}
}


void CCutNSearchView::OnRenderSortbyorder()
{
	// TODO: Add your command handler code here
	if (m_pImageView){
		m_pImageView->SetRenderMode(_BYORDER);
	}
}

void CCutNSearchView::ClearMatchingResult()
{
	if (m_pImageView){
		m_pImageView->ClearMatchingResult();
	}
}

void CCutNSearchView::OnImageClearimages()
{
	// TODO: Add your command handler code here
	if (m_pImageView){
		m_pImageView->ReleaseImageData();
	}
}

void CCutNSearchView::initImageData()
{
	if (m_pImageView){
		m_pImageView->ReleaseImageData();
	}
}

void CCutNSearchView::SetPixelMap(IplImage* pImg)
{
	pDlg->SetPixelMap(pImg);
}

void CCutNSearchView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->InitConfituration();

	if (m_pImageView){
	//	m_pImageView->SetTreeDragItem(0,0,0);
	//	m_pImageView->SetImageData();

		// Add Log Data //
		LoadLogFile();
	}
	
}


void CCutNSearchView::LoadLogFile()
{
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	if (m_pImageView){


		CString sPath;
		GetModuleFileName(nullptr, sPath.GetBuffer(_MAX_PATH + 1), _MAX_PATH);
		sPath.ReleaseBuffer();
		CString path = sPath.Left(sPath.ReverseFind(_T('\\')));
		path += "\\logdata";


		CString strSubPath;
		CString strFileName;
		CFileFind file_find;
		BOOL bWorking;
		bWorking = file_find.FindFile(path + ("\\*.jpg"));

		CString strLogFile = _T("");
		while (bWorking)
		{
			bWorking = file_find.FindNextFile();
			if (!file_find.IsDots()){

				//_IMGPATHInfo info;
				//info.strPath = path;
				
				CString filePath = file_find.GetFilePath();
					
				CString strFileName = file_find.GetFileName();
				int loc = strFileName.Find(_T("."));
				strFileName.Delete(loc, 4);

				pM->AddLogList(m_pImageView->GetLogCBitmap(filePath), strFileName);

			}
		}
	}

}

void CCutNSearchView::AddMatchResultFromLogFile(CString strName)
{
	if (m_pImageView){
		m_pImageView->AddMatchResultFromLogFile(strName);
	}

}

void CCutNSearchView::EnableLogSearch(BOOL isLog)
{
	if (m_pImageView){
		m_pImageView->EnableLogSearch(isLog);
	}
}