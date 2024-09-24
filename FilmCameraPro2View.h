// FilmCameraPro2View.h: CFilmCameraPro2View 클래스의 인터페이스
// CFilmCameraPro2View: 뷰(View) 관련 기능을 담당하는 클래스

#pragma once

// CFilmCameraPro2View 클래스는 MFC의 CScrollView 클래스를 상속받아 스크롤이 가능한 뷰를 제공합니다.
class CFilmCameraPro2View : public CScrollView
{
protected: 
    // serialization에서만 사용되는 생성자 (객체를 파일로 저장하거나 파일에서 로드할 때 사용)
	CFilmCameraPro2View() noexcept; 
	DECLARE_DYNCREATE(CFilmCameraPro2View) // 동적 생성 및 런타임 클래스 정보 제공 매크로

// 특성입니다. (Attributes)
public:
	// 문서 객체를 가져오는 함수, 이 뷰에서 처리하고 있는 문서의 포인터를 반환
	CFilmCameraPro2Doc* GetDocument() const;

// 작업입니다. (Operations)
public:

// 재정의입니다. (Overrides)
public:
	// 뷰를 그릴 때 호출되는 함수 (뷰의 내용을 화면에 출력)
	virtual void OnDraw(CDC* pDC); 
	// 윈도우가 생성되기 전에 호출되는 함수 (뷰의 창 속성 설정)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	// 뷰가 처음 생성될 때 초기화 작업을 수행하는 함수
	virtual void OnInitialUpdate(); 
	// 인쇄 준비를 수행하는 함수 (인쇄 설정 전 호출)
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	// 인쇄 시작 전에 호출되는 함수
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	// 인쇄가 끝난 후 호출되는 함수
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다. (Implementation)
public:
	// 소멸자 (클래스 객체가 삭제될 때 호출)
	virtual ~CFilmCameraPro2View();
#ifdef _DEBUG
	// 디버깅을 위한 함수 (유효성 검사)
	virtual void AssertValid() const;
	// 디버깅을 위한 함수 (객체 상태 덤프)
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수 (Generated message map functions)
protected:
	// 파일 미리보기 메뉴를 선택했을 때 호출되는 함수
	afx_msg void OnFilePrintPreview();
	// 마우스 오른쪽 버튼을 눌렀을 때 호출되는 함수
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	// 컨텍스트 메뉴(마우스 오른쪽 버튼 메뉴)를 표시하는 함수
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP() // 메시지 맵 선언
public:
	// 각 필름 효과를 적용하는 메뉴 항목 선택 시 호출되는 함수들
	afx_msg void OnFilm1(); // 필름 효과 1 함수
	afx_msg void OnFilm2(); // 필름 효과 2 함수
	afx_msg void OnFilm3(); // 필름 효과 3 함수
	afx_msg void OnFilm4(); // 필름 효과 4 함수
};

// 디버그 모드에서만 정의되는 인라인 함수로, 현재 뷰와 연결된 문서 객체를 반환
#ifndef _DEBUG  
inline CFilmCameraPro2Doc* CFilmCameraPro2View::GetDocument() const
   { return reinterpret_cast<CFilmCameraPro2Doc*>(m_pDocument); }
#endif
