﻿
// SN2019111388Doc.h: CSN2019111388Doc 클래스의 인터페이스
//


#pragma once


class CSN2019111388Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CSN2019111388Doc() noexcept;
	DECLARE_DYNCREATE(CSN2019111388Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CSN2019111388Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char m_InImg[256][256];
	unsigned char m_OutImg[256][256];
	unsigned char m_InImg1[256][256];
	unsigned char m_InImg2[256][256];
	void TwoImgLoad();
	void BinThresh(int height, int width, int threshVal);
	void ImageBlend(int height, int width, int alpha);
};
