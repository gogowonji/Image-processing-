
// SN2019111388Doc.cpp: CSN2019111388Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SN2019111388.h"
#endif

#include "SN2019111388Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSN2019111388Doc

IMPLEMENT_DYNCREATE(CSN2019111388Doc, CDocument)

BEGIN_MESSAGE_MAP(CSN2019111388Doc, CDocument)
END_MESSAGE_MAP()


// CSN2019111388Doc 생성/소멸

CSN2019111388Doc::CSN2019111388Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSN2019111388Doc::~CSN2019111388Doc()
{
}

BOOL CSN2019111388Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSN2019111388Doc serialization

void CSN2019111388Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//처리된 영상배열 m_OutImg를 파일로 저장
		ar.Write(m_OutImg, 256 * 256);
	}
	else
	{
		//입력할 파일의 포인터를 가져옴
		CFile* infile = ar.GetFile();
		if (infile->GetLength() != 256 * 256)
		{
			AfxMessageBox((LPCTSTR)"파일 크기 오류");
			return;
		}
		//영상 파일을 읽어 m_InImg배열에 저장
		ar.Read(m_InImg, (UINT)infile->GetLength());
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CSN2019111388Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CSN2019111388Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSN2019111388Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSN2019111388Doc 진단

#ifdef _DEBUG
void CSN2019111388Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSN2019111388Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSN2019111388Doc 명령


void CSN2019111388Doc::TwoImgLoad()
{
	CFile file;

	CFileDialog opendlg1(TRUE);

	if (opendlg1.DoModal() == IDOK) {
		file.Open(opendlg1.GetPathName(), CFile::modeRead);
		file.Read(m_InImg1, sizeof(m_InImg1));
		file.Close();
	}

	CFileDialog opendlg2(TRUE);

	if (opendlg2.DoModal() == IDOK) {
		file.Open(opendlg2.GetPathName(), CFile::modeRead);
		file.Read(m_InImg2, sizeof(m_InImg2));
		file.Close();
	}
}

void CSN2019111388Doc::BinThresh(int height, int width, int threshVal)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (m_InImg[i][j] > threshVal)
				m_OutImg[i][j] = 255;
			else
				m_OutImg[i][j] = 0;
		}
	}
}


void CSN2019111388Doc::ImageBlend(int height, int width, int alpha)
{
	// TODO: 여기에 구현 코드 추가.
	
	//alpha이 0-255사이의 값이므로 0-1사이의 값으로변환
	double w = alpha / 255.0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			m_OutImg[i][j] = w * m_InImg1[i][j] +
				(1 - w) * m_InImg2[i][j];
		}
	}
}
