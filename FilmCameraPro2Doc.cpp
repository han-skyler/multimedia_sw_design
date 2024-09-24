
// FilmCameraPro2Doc.cpp: CFilmCameraPro2Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "FilmCameraPro2.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "FilmCameraPro2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFilmCameraPro2Doc

IMPLEMENT_DYNCREATE(CFilmCameraPro2Doc, CDocument)

BEGIN_MESSAGE_MAP(CFilmCameraPro2Doc, CDocument)
END_MESSAGE_MAP()


// CFilmCameraPro2Doc 생성/소멸

CFilmCameraPro2Doc::CFilmCameraPro2Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CFilmCameraPro2Doc::~CFilmCameraPro2Doc()
{
}

BOOL CFilmCameraPro2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CFilmCameraPro2Doc serialization

void CFilmCameraPro2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CFilmCameraPro2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CFilmCameraPro2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFilmCameraPro2Doc::SetSearchContent(const CString& value)
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

// CFilmCameraPro2Doc 진단

#ifdef _DEBUG
void CFilmCameraPro2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFilmCameraPro2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFilmCameraPro2Doc 명령

BOOL CFilmCameraPro2Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 입력 메모리 해제 (R G B)
	free2D(m_InputImageR, m_inH); free2D(m_InputImageG, m_inH); free2D(m_InputImageB, m_inH);
	free2D(m_Input2ImageR, m_inH); free2D(m_Input2ImageG, m_inH); free2D(m_Input2ImageB, m_inH);
	free2D(m_subImageR, m_inH); free2D(m_subImageG, m_inH); free2D(m_subImageB, m_inH);

	// 컬러파일을 읽는 CImage 라이브러리 활용
	CImage bitmap;
	bitmap.Load(lpszPathName); // 입력 데이터 Load
	
	CFileDialog dlg(TRUE);

	// 이미지의 높이, 폭 계산
	m_inH = bitmap.GetHeight();
	m_inW = bitmap.GetWidth();

	// 메모리 할당
	m_InputImageR = malloc2D(m_inH, m_inW);
	m_InputImageG = malloc2D(m_inH, m_inW);
	m_InputImageB = malloc2D(m_inH, m_inW);

	m_Input2ImageR = malloc2D(m_inH, m_inW);
	m_Input2ImageG = malloc2D(m_inH, m_inW);
	m_Input2ImageB = malloc2D(m_inH, m_inW);

	COLORREF px; 
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			px = bitmap.GetPixel(k, i); // 픽셀 받아오기 (행, 열)
			m_InputImageR[i][k] = (unsigned char)GetRValue(px);
			m_InputImageG[i][k] = (unsigned char)GetGValue(px);
			m_InputImageB[i][k] = (unsigned char)GetBValue(px);

			m_Input2ImageR[i][k] = (unsigned char)GetRValue(px);
			m_Input2ImageG[i][k] = (unsigned char)GetGValue(px);
			m_Input2ImageB[i][k] = (unsigned char)GetBValue(px);
		}
	}

	return TRUE;
}

BOOL CFilmCameraPro2Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_OutputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return FALSE;
	}
	// .PNG 로 저장하는 관례적인 코드
	static TCHAR BASED_CODE szFilter[] = _T("PNG파일(*.PNG) | *.png | 모든파일(*.*) | *.* ||");
	CFileDialog SaveDlg(TRUE, _T("*.png"), _T(""), OFN_HIDEREADONLY, szFilter);
	if (SaveDlg.DoModal() != IDOK)
		return FALSE;
	CImage bitmap;
	bitmap.Create(m_outW, m_outH, 32); // 빈 파일 만들기(행, 열, 32); // CImage는 i랑 k가 반대임.
	COLORREF px;
	unsigned char RR, GG, BB;
	for (int i = 0; i < m_outW; i++) {
		for (int k = 0; k < m_outH; k++) {
			RR = m_OutputImageR[k][i];
			GG = m_OutputImageG[k][i];
			BB = m_OutputImageB[k][i];

			RR = m_Output2ImageR[k][i];
			GG = m_Output2ImageG[k][i];
			BB = m_Output2ImageB[k][i];

			px = RGB(RR, GG, BB);
			bitmap.SetPixel(i, k, px);
		}
	}
	bitmap.Save(SaveDlg.GetPathName(), Gdiplus::ImageFormatPNG); // MFC에서는 PNG포멧을 지원한다.
	return TRUE; // 리턴 True해줘야 정상저장됨
}

unsigned char** CFilmCameraPro2Doc::malloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = (unsigned char**)malloc(h * sizeof(unsigned char*));
	for (int i = 0; i < h; i++)
		memory[i] = (unsigned char*)malloc(w * sizeof(unsigned char));

	// 초기화(클리어)
	for (int i = 0; i < h; i++)
		for (int k = 0; k < w; k++)
			memory[i][k] = 255;

	return memory;
}

void CFilmCameraPro2Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	free2D(m_InputImageR, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageR, m_outH);
	free2D(m_InputImageG, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageG, m_outH);
	free2D(m_InputImageB, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageB, m_outH);

	free2D(m_Input2ImageR, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_Output2ImageR, m_outH);
	free2D(m_Input2ImageG, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_Output2ImageG, m_outH);
	free2D(m_Input2ImageB, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_Output2ImageB, m_outH);

	CDocument::OnCloseDocument();
}

unsigned char** CFilmCameraPro2Doc(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = (unsigned char**)malloc(h * sizeof(unsigned char*));
	for (int i = 0; i < h; i++)
		memory[i] = (unsigned char*)malloc(w * sizeof(unsigned char));
	// 초기화(클리어)
	for (int i = 0; i < h; i++)
		for (int k = 0; k < w; k++)
			memory[i][k] = 255;
	return memory;
}

void CFilmCameraPro2Doc::free2D(unsigned char** memory, int h)
{
	if (memory != NULL) {
		for (int i = 0; i < h; i++)
			free(memory[i]);
		free(memory);
	}
}

double** CFilmCameraPro2Doc::malloc2D_double(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** mem;
	mem = (double**)malloc(h * sizeof(double*));
	for (int i = 0; i < h; i++)
		mem[i] = (double*)malloc(w * sizeof(double));

	// 초기화(Clear)
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			mem[i][k] = 0;
		}
	}
	return mem;
}

void CFilmCameraPro2Doc::free2D_double(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory != NULL) {
		for (int i = 0; i < h; i++)
			free(memory[i]);
		free(memory);
	}
}

double CFilmCameraPro2Doc::doubleABS(double x)
{
	// TODO: 여기에 구현 코드 추가.

	if (x >= 0) return x;
	else        return -x;
}

void CFilmCameraPro2Doc::OnEffect1()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}

	// 기존 출력 메모리 해제

	memory_free();

	// 코드 실행

	pixel_contrast(); // 명암조절
	pixel_color_filter(); // 색상필터
	pixel_noise_gaussian(); // 가우시안
	//pixel_vignette_sub(); 
}

// 기존 출력 메모리 해제
void CFilmCameraPro2Doc::memory_free()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}

	free2D(m_OutputImageR, m_outH);
	free2D(m_OutputImageG, m_outH);
	free2D(m_OutputImageB, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImageR = malloc2D(m_outH, m_outW);
	m_OutputImageG = malloc2D(m_outH, m_outW);
	m_OutputImageB = malloc2D(m_outH, m_outW);

	free2D(m_Output2ImageR, m_outH);
	free2D(m_Output2ImageG, m_outH);
	free2D(m_Output2ImageB, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_Output2ImageR = malloc2D(m_outH, m_outW);
	m_Output2ImageG = malloc2D(m_outH, m_outW);
	m_Output2ImageB = malloc2D(m_outH, m_outW);
}

// 명암조절
void CFilmCameraPro2Doc::pixel_contrast()
{
	float value;

	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			//흑백값으로 변환
			value = (m_InputImageR[x][y] + m_InputImageG[x][y] + m_InputImageB[x][y]) / 3;

			// ========== 실제 실행 코드 ===========
			// RGB평균값으로 명암을 구별하였음
			// value가 127 초과면 더 밝게
			if (value > 127) {
				value = (value - 127) * 0.1;
				if		(m_InputImageR[x][y] + value > 255)	  m_Input2ImageR[x][y] = 255;	// 오버플로우 방지
				else if (m_InputImageR[x][y] + value < 0)	  m_Input2ImageR[x][y] = 0;		// 언더플로우 방지
				else										  m_Input2ImageR[x][y] = m_InputImageR[x][y] + value;

				if		(m_InputImageG[x][y] + value > 255)	  m_Input2ImageG[x][y] = 255;
				else if (m_InputImageG[x][y] + value < 0)	  m_Input2ImageG[x][y] = 0;
				else										  m_Input2ImageG[x][y] = m_InputImageG[x][y] + value;

				if		(m_InputImageB[x][y] + value > 255)		  m_Input2ImageB[x][y] = 255;
				else if (m_InputImageB[x][y] + value < 0)	  m_Input2ImageB[x][y] = 0;
				else										  m_Input2ImageB[x][y] = m_InputImageB[x][y] + value;
			}
			// value가 127 이하면 더 어둡게
			else if (value <= 127) {
				value = (127 - value) * 0.3;
				if		(m_InputImageR[x][y] - value > 255)	  m_Input2ImageR[x][y] = 255;
				else if (m_InputImageR[x][y] - value < 0)	  m_Input2ImageR[x][y] = 0;
				else										  m_Input2ImageR[x][y] = m_InputImageR[x][y] - value;

				if		(m_InputImageG[x][y] - value > 255)	  m_Input2ImageG[x][y] = 255;
				else if (m_InputImageG[x][y] - value < 0)	  m_Input2ImageG[x][y] = 0;
				else										  m_Input2ImageG[x][y] = m_InputImageG[x][y] - value;

				if		(m_InputImageB[x][y] - value > 255)	  m_Input2ImageB[x][y] = 255;
				else if (m_InputImageB[x][y] - value < 0)	  m_Input2ImageB[x][y] = 0;
				else										  m_Input2ImageB[x][y] = m_InputImageB[x][y] - value;
			}

			/* =========== 출력 확인용 코드 ============
			// 값이 127 이상이면 명도를 높임
			if (value > 127) {
				value = (value - 127) * 0.1;
				if (m_InputImageR[x][y] + value > 255) m_OutputImageR[x][y] = 255;
				else if (m_InputImageR[x][y] + value < 0) m_OutputImageR[x][y] = 0;
				else m_OutputImageR[x][y] = m_InputImageR[x][y] + value;

				if (m_InputImageG[x][y] + value > 255) m_OutputImageG[x][y] = 255;
				else if (m_InputImageG[x][y] + value < 0) m_OutputImageG[x][y] = 0;
				else m_OutputImageG[x][y] = m_InputImageG[x][y] + value;

				if (m_InputImageB[x][y] + value > 255) m_OutputImageB[x][y] = 255;
				else if (m_InputImageB[x][y] + value < 0) m_OutputImageB[x][y] = 0;
				else m_OutputImageB[x][y] = m_InputImageB[x][y] + value;
			}

			else if (value <= 127) {
				value = (127 - value) * 0.1;
				if (m_InputImageR[x][y] - value > 255) m_OutputImageR[x][y] = 255;
				else if (m_InputImageR[x][y] - value < 0) m_OutputImageR[x][y] = 0;
				else m_OutputImageR[x][y] = m_InputImageR[x][y] - value;

				if (m_InputImageG[x][y] - value > 255) m_OutputImageG[x][y] = 255;
				else if (m_InputImageG[x][y] - value < 0) m_OutputImageG[x][y] = 0;
				else m_OutputImageG[x][y] = m_InputImageG[x][y] - value;

				if (m_InputImageB[x][y] - value > 255) m_OutputImageB[x][y] = 255;
				else if (m_InputImageB[x][y] - value < 0) m_OutputImageB[x][y] = 0;
				else m_OutputImageB[x][y] = m_InputImageB[x][y] - value;
			}*/
		}
	}
}

// 색상 필터
void CFilmCameraPro2Doc::pixel_color_filter()
{
	// TODO: 여기에 구현 코드 추가.

	float Red_filter = 40;
	float Green_filter = 25;

	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			if		(m_Input2ImageR[x][y] + Red_filter > 255)	  m_Output2ImageR[x][y] = 255;
			else if (m_Input2ImageR[x][y] + Red_filter < 0)	 	  m_Output2ImageR[x][y] = 0;
			else												  m_Output2ImageR[x][y] = m_Input2ImageR[x][y] + Red_filter;

			if		(m_Input2ImageG[x][y] + Green_filter > 255)	  m_Output2ImageG[x][y] = 255;
			else if (m_Input2ImageG[x][y] + Green_filter < 0)	  m_Output2ImageG[x][y] = 0;
			else												  m_Output2ImageG[x][y] = m_Input2ImageG[x][y] + Green_filter;

			m_Output2ImageB[x][y] = m_Input2ImageB[x][y];
		}
	}

	//==================출력 확인용==================
	/*
	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			if (m_InputImageR[x][y] + Red_filter > 255) m_OutputImageR[x][y] = 255;
			else if (m_InputImageR[x][y] + Red_filter < 0) m_OutputImageR[x][y] = 0;
			else m_OutputImageR[x][y] = m_InputImageR[x][y] + Red_filter;

			if (m_InputImageG[x][y] + Green_filter > 255) m_OutputImageG[x][y] = 255;
			else if (m_InputImageG[x][y] + Green_filter < 0) m_OutputImageG[x][y] = 0;
			else m_OutputImageG[x][y] = m_InputImageG[x][y] + Green_filter;

			m_OutputImageB[x][y] = m_InputImageB[x][y];
		}
	}*/
}

// 가우시안 효과 적용
void CFilmCameraPro2Doc::pixel_noise_gaussian()
{
	float num1;
	float num2;

	float value = 0;

	for (int x = 0; x < m_inH; x++)
		for (int y = 0; y < m_inW; y++) {

			//랜덤한 두 값 생성 
			num1 = (float)rand() / 51251; //51251은 임의의 값
			num2 = (float)rand() / 51251; //51251은 임의의 값

			// 가우시안 함수
			value = sqrt(-2 * 100 * log(num1)) * cos(2 * 3.141592 * num2); // 분산 100으로 설정

			// ============ 실제 실행 코드 ==============
			if (value > 255) value = 255; // 오버플로우 방지

			else if (value < 0) value = 0; // 언더플로우 방지

			// RGB값 오버플로우 방지
			// value와 InputImage를 합하여 랜덤한 노이즈 생성
			if ((value + m_Output2ImageR[x][y]) > 255)		m_OutputImageR[x][y] = 255;
			else if ((value + m_Output2ImageG[x][y]) > 255) m_OutputImageG[x][y] = 255;
			else if ((value + m_Output2ImageB[x][y]) > 255) m_OutputImageB[x][y] = 255;

			// RGB값 언더플로우 방지
			else if ((value + m_Output2ImageR[x][y]) < 0) m_OutputImageR[x][y] = 0;
			else if ((value + m_Output2ImageG[x][y]) < 0) m_OutputImageG[x][y] = 0;
			else if ((value + m_Output2ImageB[x][y]) < 0) m_OutputImageB[x][y] = 0;
			
			else
			{
				m_OutputImageR[x][y] = value + m_Output2ImageR[x][y];
				m_OutputImageG[x][y] = value + m_Output2ImageG[x][y];
				m_OutputImageB[x][y] = value + m_Output2ImageB[x][y];
			}

			/* ============ 가우시안 노이즈 확인용 코드 ===============
			//오버플로우 방지
			if (value > 255)
			{
				value = 255;
			}

			// 언더플로우 방지
			else if (value < 0)
			{
				value = 0;
			}

			// RGB값 오버플로우 방지
			// value와 InputImage를 합하여 랜덤한 노이즈 생성
			if ((value + m_InputImageR[x][y]) > 255)
			{
				m_Input2ImageR[x][y] = 255;
			}
			else if ((value + m_InputImageG[x][y]) > 255)
			{
				m_Input2ImageG[x][y] = 255;
			}
			else if ((value + m_InputImageB[x][y]) > 255)
			{
				m_Input2ImageB[x][y] = 255;
			}

			// RGB값 언더플로우 방지
			else if ((value + m_InputImageR[x][y]) < 0)
			{
				m_Input2ImageR[x][y] = 0;
			}
			else if ((value + m_InputImageG[x][y]) < 0)
			{
				m_Input2ImageG[x][y] = 0;
			}
			else if ((value + m_InputImageB[x][y]) < 0)
			{
				m_Input2ImageB[x][y] = 0;
			}
			else
			{
				m_Input2ImageR[x][y] = value + m_InputImageR[x][y];
				m_Input2ImageG[x][y] = value + m_InputImageG[x][y];
				m_Input2ImageB[x][y] = value + m_InputImageB[x][y];
			}*/
		}
}

// 비네트 영상 합성
/*void CFilmCameraPro2Doc::pixel_vignette_sub()
{
	char szFilter[] = "BMP File (*.BMP) | *.BMP; | All Files(*.*)|*.*||";
	CString strPathName; //파일 경로 저장

	CImage bitmap;

	CFileDialog dlg(TRUE);

	AfxMessageBox(_T("비네팅 파일을 선택해 주세요."));
	if (IDOK != dlg.DoModal()) //두 번째 이미지 파일 대화상자 열기 
	{
		bitmap.Load(strPathName);
	}
	strPathName = dlg.GetPathName();
	
	int m_subH = bitmap.GetHeight();
	int m_subW = bitmap.GetWidth();

	m_subImageR = malloc2D(m_subH, m_subW);
	m_subImageG = malloc2D(m_subH, m_subW);
	m_subImageB = malloc2D(m_subH, m_subW);

	COLORREF px; // 한점(R G B) _ (컬러레퍼런스) _ MFC라이브러리
	for (int i = 0; i < m_subH; i++) {
		for (int k = 0; k < m_subW; k++) {
			px = bitmap.GetPixel(k, i); // 픽셀 받아오기 (행, 열)
			m_subImageR[i][k] = (unsigned char)GetRValue(px);
			m_subImageG[i][k] = (unsigned char)GetGValue(px);
			m_subImageB[i][k] = (unsigned char)GetBValue(px);
		}
	}

	float tmp;
	float value;

	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			tmp = m_InputImageR[x][y] + (m_subImageR[x][y] / 5); //비네팅 영상과 합치기
			if (tmp > 255)
			{
				tmp = 255;
				m_OutputImageR[x][y] = tmp;
			}
			else if (tmp < 0) {
				tmp = 0;
				m_OutputImageR[x][y] = tmp;
			}
			else m_OutputImageR[x][y] = tmp;

			tmp = m_InputImageG[x][y] + (m_subImageG[x][y] / 5); //비네팅 영상과 합치기
			if (tmp > 255)
			{
				tmp = 255;
				m_OutputImageG[x][y] = tmp;
			}
			else if (tmp < 0) {
				tmp = 0;
				m_OutputImageG[x][y] = tmp;
			}
			else m_OutputImageG[x][y] = tmp;

			tmp = m_InputImageB[x][y] + (m_subImageB[x][y] / 5); //비네팅 영상과 합치기
			if (tmp > 255)
			{
				tmp = 255;
				m_OutputImageB[x][y] = tmp;
			}
			else if (tmp < 0) {
				tmp = 0;
				m_OutputImageB[x][y] = tmp;
			}
			else m_OutputImageB[x][y] = tmp;
		}
	}
}*/

void CFilmCameraPro2Doc::OnEffect2()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}

	// 기존 출력 메모리 해제

	memory_free();

	// 코드 실행

	pixel_contrast(); // 명암조절
	pixel_color_filter_effect2(); //색감 조절
	pixel_noise_gaussian_effect2(); //가우시안

}

void CFilmCameraPro2Doc::pixel_color_filter_effect2()
{
	// TODO: 여기에 구현 코드 추가.

	float Blue_filter = 10;
	float Green_filter = 10;

	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			if		(m_Input2ImageR[x][y] > 255)				  m_Output2ImageB[x][y] = 255;
			else if (m_Input2ImageR[x][y] < 0)					  m_Output2ImageB[x][y] = 0;
			else												  m_Output2ImageR[x][y] = m_Input2ImageR[x][y];

			if		(m_Input2ImageG[x][y] + Green_filter > 255)	  m_Output2ImageG[x][y] = 255;
			else if (m_Input2ImageG[x][y] + Green_filter < 0)	  m_Output2ImageG[x][y] = 0;
			else												  m_Output2ImageG[x][y] = m_Input2ImageG[x][y] + Green_filter;

			if		(m_Input2ImageB[x][y] + Blue_filter > 255)	  m_Output2ImageB[x][y] = 255;
			else if (m_Input2ImageB[x][y] + Blue_filter < 0)	  m_Output2ImageB[x][y] = 0;
			else												  m_Output2ImageB[x][y] = m_Input2ImageB[x][y] + Blue_filter;
			
		}
	}

	//==================출력 확인용==================
	/*
	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			if (m_InputImageR[x][y] + Red_filter > 255) m_OutputImageR[x][y] = 255;
			else if (m_InputImageR[x][y] + Red_filter < 0) m_OutputImageR[x][y] = 0;
			else m_OutputImageR[x][y] = m_InputImageR[x][y] + Red_filter;

			if (m_InputImageG[x][y] + Green_filter > 255) m_OutputImageG[x][y] = 255;
			else if (m_InputImageG[x][y] + Green_filter < 0) m_OutputImageG[x][y] = 0;
			else m_OutputImageG[x][y] = m_InputImageG[x][y] + Green_filter;

			m_OutputImageB[x][y] = m_InputImageB[x][y];
		}
	}*/
}


void CFilmCameraPro2Doc::pixel_noise_gaussian_effect2()
{
	float num1;
	float num2;

	float value = 0;

	for (int x = 0; x < m_inH; x++)
		for (int y = 0; y < m_inW; y++) {

			//랜덤한 두 값 생성 
			num1 = (float)rand() / 51251; //51251은 임의의 값
			num2 = (float)rand() / 51251; //51251은 임의의 값

			// 가우시안 함수
			value = sqrt(-2 * 150 * log(num1)) * cos(2 * 3.141592 * num2); // 분산 400으로 설정

			// ============ 실제 실행 코드 ==============
			if (value > 255) value = 255; // 오버플로우 방지

			//else if (value < 0) value = 0; // 언더플로우 방지

			// RGB값 오버플로우 방지
			// value와 InputImage를 합하여 랜덤한 노이즈 생성
			if		((value + m_Output2ImageR[x][y]) > 255)	m_OutputImageR[x][y] = 255;
			else if ((value + m_Output2ImageG[x][y]) > 255) m_OutputImageG[x][y] = 255;
			else if ((value + m_Output2ImageB[x][y]) > 255) m_OutputImageB[x][y] = 255;

			// RGB값 언더플로우 방지
			else if ((value + m_Output2ImageR[x][y]) < 0) m_OutputImageR[x][y] = 0;
			else if ((value + m_Output2ImageG[x][y]) < 0) m_OutputImageG[x][y] = 0;
			else if ((value + m_Output2ImageB[x][y]) < 0) m_OutputImageB[x][y] = 0;

			else
			{
				m_OutputImageR[x][y] = value + m_Output2ImageR[x][y];
				m_OutputImageG[x][y] = value + m_Output2ImageG[x][y];
				m_OutputImageB[x][y] = value + m_Output2ImageB[x][y];
			}

			/* ============ 가우시안 노이즈 확인용 코드 ===============
			//오버플로우 방지
			if (value > 255)
			{
				value = 255;
			}

			// 언더플로우 방지
			else if (value < 0)
			{
				value = 0;
			}

			// RGB값 오버플로우 방지
			// value와 InputImage를 합하여 랜덤한 노이즈 생성
			if ((value + m_InputImageR[x][y]) > 255)
			{
				m_Input2ImageR[x][y] = 255;
			}
			else if ((value + m_InputImageG[x][y]) > 255)
			{
				m_Input2ImageG[x][y] = 255;
			}
			else if ((value + m_InputImageB[x][y]) > 255)
			{
				m_Input2ImageB[x][y] = 255;
			}

			// RGB값 언더플로우 방지
			else if ((value + m_InputImageR[x][y]) < 0)
			{
				m_Input2ImageR[x][y] = 0;
			}
			else if ((value + m_InputImageG[x][y]) < 0)
			{
				m_Input2ImageG[x][y] = 0;
			}
			else if ((value + m_InputImageB[x][y]) < 0)
			{
				m_Input2ImageB[x][y] = 0;
			}
			else
			{
				m_Input2ImageR[x][y] = value + m_InputImageR[x][y];
				m_Input2ImageG[x][y] = value + m_InputImageG[x][y];
				m_Input2ImageB[x][y] = value + m_InputImageB[x][y];
			}*/
		}
}


void CFilmCameraPro2Doc::OnEffect3()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}

	// 기존 출력 메모리 해제

	memory_free();

	// 엠보싱
	pixel_embos();
}

// 엠보싱
void CFilmCameraPro2Doc::pixel_embos()
{
	double mask[3][3] = { {	-1.,	0.,		0.},
						 {	0.,		0.,		0.},
						 {	0.,		0.,		1.} };
	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2);
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {
			tmpInput[x + 1][y + 1] = (unsigned char)((m_InputImageR[x][y] + m_InputImageG[x][y] + m_InputImageB[x][y]) / 3);
		}
	}

	double S; // 마스크9개 X 입력영상 9개의 합 마스크
	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {
			S = 0.0; // 누적 값 초기화
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[x + m][y + n] * mask[m][n];
				}
			}
			tmpOutput[x][y] = S;
		}
	}

	// 다듬기 --> 마스크합계가 0 또는 1 이면 127 더하기
	for (int x = 0; x < m_outH; x++) {
		for (int y = 0; y < m_outW; y++) {
			tmpOutput[x][y] += 127.0;
		}
	}
	// tmpOutput -> m_OutputImage // 오버플로우 언더플로우
	for (int x = 0; x < m_outH; x++) {
		for (int y = 0; y < m_outW; y++) {
			double v = tmpOutput[x][y];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImageR[x][y] = m_OutputImageG[x][y] = m_OutputImageB[x][y] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
}


void CFilmCameraPro2Doc::OnEffect4()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}

	// 기존 출력 메모리 해제

	memory_free();

	// 흑백 필름효과

	pixel_contrast();
	pixel_gray();
	pixel_noise_gaussian();

}


void CFilmCameraPro2Doc::pixel_gray()
{
	float value = 0;

	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			value = (m_Input2ImageR[x][y] + m_Input2ImageG[x][y] + m_Input2ImageB[x][y]) / 3;

			m_Output2ImageR[x][y] = value;
			m_Output2ImageG[x][y] = value;
			m_Output2ImageB[x][y] = value;
		}
	}
}
