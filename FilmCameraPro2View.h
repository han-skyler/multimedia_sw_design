
// FilmCameraPro2View.h: CFilmCameraPro2View 클래스의 인터페이스
//

#pragma once


class CFilmCameraPro2View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CFilmCameraPro2View() noexcept;
	DECLARE_DYNCREATE(CFilmCameraPro2View)

// 특성입니다.
public:
	CFilmCameraPro2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CFilmCameraPro2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFilm1();
	afx_msg void OnFilm2();
	afx_msg void OnFilm3();
	afx_msg void OnFilm4();
};

#ifndef _DEBUG  // FilmCameraPro2View.cpp의 디버그 버전
inline CFilmCameraPro2Doc* CFilmCameraPro2View::GetDocument() const
   { return reinterpret_cast<CFilmCameraPro2Doc*>(m_pDocument); }
#endif

