
// SN2019111388View.cpp: CSN2019111388View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SN2019111388.h"
#endif

#include "SN2019111388Doc.h"
#include "SN2019111388View.h"

#include "CBinCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSN2019111388View

IMPLEMENT_DYNCREATE(CSN2019111388View, CScrollView)

BEGIN_MESSAGE_MAP(CSN2019111388View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSN2019111388View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_REVERSE_IMG, &CSN2019111388View::OnReverseImg)
	ON_COMMAND(IDM_FRM_BLE, &CSN2019111388View::OnFrmBle)
END_MESSAGE_MAP()

// CSN2019111388View 생성/소멸

CSN2019111388View::CSN2019111388View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	height = width = 256;
	int rwsize = (((width * 8) + 31) / 31 * 4);
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));

	BmInfo->bmiHeader.biBitCount = 8;
	BmInfo->bmiHeader.biClrImportant = 256;
	BmInfo->bmiHeader.biSize = 40;
	BmInfo->bmiHeader.biHeight = height;
	BmInfo->bmiHeader.biWidth = width;
	BmInfo->bmiHeader.biPlanes = 1;
	BmInfo->bmiHeader.biCompression = 0;
	BmInfo->bmiHeader.biSizeImage = rwsize * height;
	BmInfo->bmiHeader.biXPelsPerMeter = 0;
	BmInfo->bmiHeader.biYPelsPerMeter = 0;

	for (int i = 0; i < 256; i++) {
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i;
		BmInfo->bmiColors[i].rgbReserved = 0;
	}


}

CSN2019111388View::~CSN2019111388View()
{
	free(BmInfo);
}

BOOL CSN2019111388View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CSN2019111388View 그리기

void CSN2019111388View::OnDraw(CDC* pDC)
{
	CSN2019111388Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m_RevImg[i][j] = pDoc->m_InImg[height - i - 1][j];
		}
	}
	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height, 0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m_RevImg[i][j] = pDoc->m_OutImg[height - i - 1][j];
		}
	}
	SetDIBitsToDevice(pDC->GetSafeHdc(), 300, 0, width, height, 0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);

/*
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			unsigned char InVal = pDoc->m_InImg[i][j];
			unsigned char OutVal = pDoc->m_OutImg[i][j];
			pDC->SetPixel(j, i, RGB(InVal, InVal, InVal));
			pDC->SetPixel(j + 300, i, RGB(OutVal, OutVal, OutVal));
		}
	}
*/
}

void CSN2019111388View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CSN2019111388View 인쇄


void CSN2019111388View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSN2019111388View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSN2019111388View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSN2019111388View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSN2019111388View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSN2019111388View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSN2019111388View 진단

#ifdef _DEBUG
void CSN2019111388View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSN2019111388View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSN2019111388Doc* CSN2019111388View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSN2019111388Doc)));
	return (CSN2019111388Doc*)m_pDocument;
}
#endif //_DEBUG


// CSN2019111388View 메시지 처리기


void CSN2019111388View::OnReverseImg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2019111388Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++)
		{
			pDoc->m_OutImg[i][j] = 255 - pDoc->m_InImg[i][j];
		}
	}
	Invalidate(FALSE);
}


void CSN2019111388View::OnFrmBle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2019111388Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->TwoImgLoad();

	CBinCtrlDlg pbinCtrlDlg;
	pbinCtrlDlg.DoModal();
}
