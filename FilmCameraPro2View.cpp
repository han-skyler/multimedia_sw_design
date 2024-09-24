// FilmCameraPro2View.cpp: CFilmCameraPro2View 클래스의 구현

#include "pch.h" // 미리 컴파일된 헤더 파일 포함
#include "framework.h"

// SHARED_HANDLERS가 정의되지 않은 경우에만 이 프로젝트의 헤더 파일을 포함
#ifndef SHARED_HANDLERS
#include "FilmCameraPro2.h"
#endif

#include "FilmCameraPro2Doc.h" // 문서 클래스 헤더 파일 포함
#include "FilmCameraPro2View.h" // 뷰 클래스 헤더 파일 포함

#ifdef _DEBUG
#define new DEBUG_NEW // 디버그 모드에서의 메모리 누수 검사를 위한 매크로 정의
#endif

// CFilmCameraPro2View 클래스의 동적 생성 매크로
IMPLEMENT_DYNCREATE(CFilmCameraPro2View, CScrollView)

// 메시지 맵(MFC의 메시지 처리 매커니즘) 정의
BEGIN_MESSAGE_MAP(CFilmCameraPro2View, CScrollView)
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint) // 파일 인쇄 명령 처리
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint) // 직접 인쇄 명령 처리
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFilmCameraPro2View::OnFilePrintPreview) // 파일 미리보기 명령 처리
	ON_WM_CONTEXTMENU() // 컨텍스트 메뉴 메시지 처리
	ON_WM_RBUTTONUP() // 마우스 오른쪽 버튼 눌림 메시지 처리
	ON_COMMAND(ID_FILM1, &CFilmCameraPro2View::OnFilm1) // 필름 효과 1 처리
	ON_COMMAND(ID_FILM2, &CFilmCameraPro2View::OnFilm2) // 필름 효과 2 처리
	ON_COMMAND(ID_FILM3, &CFilmCameraPro2View::OnFilm3) // 필름 효과 3 처리
	ON_COMMAND(ID_FILM4, &CFilmCameraPro2View::OnFilm4) // 필름 효과 4 처리
END_MESSAGE_MAP()

// CFilmCameraPro2View 생성자
CFilmCameraPro2View::CFilmCameraPro2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

// CFilmCameraPro2View 소멸자
CFilmCameraPro2View::~CFilmCameraPro2View()
{
}

// 뷰의 윈도우가 생성되기 전에 호출되는 함수 (윈도우 스타일 또는 속성을 수정할 수 있음)
BOOL CFilmCameraPro2View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs); // 기본 동작 호출
}

// 뷰의 내용을 그리는 함수, 입력 이미지와 필터 적용 후 이미지를 화면에 그립니다.
void CFilmCameraPro2View::OnDraw(CDC* pDC)
{
	CFilmCameraPro2Doc* pDoc = GetDocument(); // 문서 객체 가져오기
	ASSERT_VALID(pDoc); // 문서 객체의 유효성 검사
	if (!pDoc)
		return;

	int RR, GG, BB;
	// 원본 이미지 그리기
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			RR = pDoc->m_InputImageR[i][k]; // R 채널
			GG = pDoc->m_InputImageG[i][k]; // G 채널
			BB = pDoc->m_InputImageB[i][k]; // B 채널
			pDC->SetPixel(k + 5, i + 5, RGB(RR, GG, BB)); // 픽셀 그리기
		}
	}
	// 필터 적용 후 이미지 그리기
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			RR = pDoc->m_OutputImageR[i][k]; // R 채널
			GG = pDoc->m_OutputImageG[i][k]; // G 채널
			BB = pDoc->m_OutputImageB[i][k]; // B 채널
			pDC->SetPixel(pDoc->m_inW + k + 20, i + 5, RGB(RR, GG, BB)); // 필터 적용 후 픽셀 그리기
		}
	}
}

// 뷰가 처음 생성되고 초기화될 때 호출되는 함수
void CFilmCameraPro2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// 뷰의 전체 크기를 설정합니다 (기본값은 100x100).
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal); // 스크롤 크기 설정
}

// 인쇄 미리보기 처리 함수
void CFilmCameraPro2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

// 인쇄 준비를 위한 함수, 기본적으로 인쇄 준비를 수행하도록 합니다.
BOOL CFilmCameraPro2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo); // 기본적인 인쇄 준비 수행
}

// 인쇄가 시작되기 전에 호출되는 함수 (추가 초기화 작업)
void CFilmCameraPro2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 시작 전에 추가 초기화 작업을 수행합니다.
}

// 인쇄가 종료된 후 호출되는 함수 (정리 작업)
void CFilmCameraPro2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 수행합니다.
}

// 마우스 오른쪽 버튼을 눌렀을 때 호출되는 함수, 컨텍스트 메뉴 표시를 위해 사용
void CFilmCameraPro2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point); // 화면 좌표로 변환
	OnContextMenu(this, point); // 컨텍스트 메뉴 호출
}

// 컨텍스트 메뉴를 표시하는 함수
void CFilmCameraPro2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// 필름 효과 1 (노란빛 필름 효과)를 적용하는 함수
void CFilmCameraPro2View::OnFilm1()
{
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEffect1(); // 문서 객체의 필름 효과 1 함수 호출

	Invalidate(FALSE); // 화면 갱신
}

// 필름 효과 2 (파란빛 필름 효과)를 적용하는 함수
void CFilmCameraPro2View::OnFilm2()
{
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEffect2(); // 문서 객체의 필름 효과 2 함수 호출

	Invalidate(FALSE); // 화면 갱신
}

// 필름 효과 3 (엠보싱 효과)를 적용하는 함수
void CFilmCameraPro2View::OnFilm3()
{
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEffect3(); // 문서 객체의 필름 효과 3 함수 호출

	Invalidate(FALSE); // 화면 갱신
}

// 필름 효과 4 (흑백 필름 효과)를 적용하는 함수
void CFilmCameraPro2View::OnFilm4()
{
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEffect4(); // 문서 객체의 필름 효과 4 함수 호출

	Invalidate(FALSE); // 화면 갱신
}

// 디버그 모드에서 유효성을 검사하는 함수
#ifdef _DEBUG
void CFilmCameraPro2View::AssertValid() const
{
	CScrollView::AssertValid(); // 부모 클래스의 유효성 검사 함수 호출
}

// 디버그 모드에서 객체 상태를 덤프하는 함수
void CFilmCameraPro2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc); // 부모 클래스의 덤프 함수 호출
}

// 문서 객체를 반환하는 함수 (디버그 모드에서만 사용)
CFilmCameraPro2Doc* CFilmCameraPro2View::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFilmCameraPro2Doc))); // 문서 객체의 클래스 유형 확인
	return (CFilmCameraPro2Doc*)m_pDocument; // 문서 객체 반환
}
#endif //_DEBUG
