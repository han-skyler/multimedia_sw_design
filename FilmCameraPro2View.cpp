
// FilmCameraPro2View.cpp: CFilmCameraPro2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "FilmCameraPro2.h"
#endif

#include "FilmCameraPro2Doc.h"
#include "FilmCameraPro2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFilmCameraPro2View

IMPLEMENT_DYNCREATE(CFilmCameraPro2View, CScrollView)

BEGIN_MESSAGE_MAP(CFilmCameraPro2View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFilmCameraPro2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILM1, &CFilmCameraPro2View::OnFilm1)
	ON_COMMAND(ID_FILM2, &CFilmCameraPro2View::OnFilm2)
	ON_COMMAND(ID_FILM3, &CFilmCameraPro2View::OnFilm3)
	ON_COMMAND(ID_FILM4, &CFilmCameraPro2View::OnFilm4)
END_MESSAGE_MAP()

// CFilmCameraPro2View 생성/소멸

CFilmCameraPro2View::CFilmCameraPro2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CFilmCameraPro2View::~CFilmCameraPro2View()
{
}

BOOL CFilmCameraPro2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CFilmCameraPro2View 그리기

void CFilmCameraPro2View::OnDraw(CDC* pDC)
{
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	int RR, GG, BB;
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			RR = pDoc->m_InputImageR[i][k];
			GG = pDoc->m_InputImageG[i][k];
			BB = pDoc->m_InputImageB[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(RR, GG, BB));
		}
	}
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			RR = pDoc->m_OutputImageR[i][k];
			GG = pDoc->m_OutputImageG[i][k];
			BB = pDoc->m_OutputImageB[i][k];
			pDC->SetPixel(pDoc->m_inW + k + 20, i + 5, RGB(RR, GG, BB));
		}
	}
}

void CFilmCameraPro2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CFilmCameraPro2View 인쇄


void CFilmCameraPro2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFilmCameraPro2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CFilmCameraPro2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CFilmCameraPro2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CFilmCameraPro2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFilmCameraPro2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFilmCameraPro2View 진단

#ifdef _DEBUG
void CFilmCameraPro2View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFilmCameraPro2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFilmCameraPro2Doc* CFilmCameraPro2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFilmCameraPro2Doc)));
	return (CFilmCameraPro2Doc*)m_pDocument;
}
#endif //_DEBUG


// CFilmCameraPro2View 메시지 처리기


void CFilmCameraPro2View::OnFilm1()
{
	// 노란빛 필름효과
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEffect1();

	Invalidate(FALSE);
}


void CFilmCameraPro2View::OnFilm2()
{
	// 파란빛 필름효과
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEffect2();

	Invalidate(FALSE);
}


void CFilmCameraPro2View::OnFilm3()
{
	// 엠보싱효과
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEffect3();

	Invalidate(FALSE);
}


void CFilmCameraPro2View::OnFilm4()
{
	// 흑백 필름효과
	CFilmCameraPro2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEffect4();

	Invalidate(FALSE);
}
