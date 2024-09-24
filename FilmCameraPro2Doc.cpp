
// FilmCameraPro2Doc.cpp: CFilmCameraPro2Doc 클래스의 구현
//
// 이 파일은 CFilmCameraPro2Doc 클래스의 구현 파일입니다.
// MFC의 Document/View 구조에서 'Document'에 해당하는 기능을 담당합니다.
// 문서 데이터의 생성, 소멸, 직렬화(파일 저장 및 불러오기) 등의 기능을 처리합니다.

#include "pch.h" // 사전 컴파일된 헤더 파일을 포함합니다.
#include "framework.h" // MFC 프레임워크 관련 헤더 파일을 포함합니다.

// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있습니다.
// 이 부분은 SHARED_HANDLERS가 정의되지 않은 경우에만 `FilmCameraPro2.h` 헤더를 포함하도록 합니다.
#ifndef SHARED_HANDLERS
#include "FilmCameraPro2.h"
#endif

#include <stdlib.h> // 표준 라이브러리 함수 (예: 메모리 할당, 해제 등) 포함
#include <stdio.h>  // 표준 입출력 함수 (예: printf, scanf 등) 포함
#include <math.h>   // 수학 함수 (예: sin, cos, sqrt 등) 포함
#include <string.h> // 문자열 처리 함수 (예: strcpy, strlen 등) 포함

// 해당 문서의 헤더 파일을 포함합니다.
#include "FilmCameraPro2Doc.h"

#include <propkey.h> // 문서 속성 키(Property Key) 관리를 위한 헤더 파일

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFilmCameraPro2Doc
// CFilmCameraPro2Doc 클래스의 구현 매크로입니다.
// IMPLEMENT_DYNCREATE는 런타임 클래스 정보를 동적으로 생성하는 매크로로,
// 런타임 시점에 객체를 생성할 수 있도록 해줍니다.
IMPLEMENT_DYNCREATE(CFilmCameraPro2Doc, CDocument)

// CFilmCameraPro2Doc 메시지 맵
// BEGIN_MESSAGE_MAP과 END_MESSAGE_MAP 매크로는 클래스가 처리하는 메시지들을 정의합니다.
// 이 클래스는 별도의 메시지 처리 핸들러를 정의하고 있지 않습니다.
BEGIN_MESSAGE_MAP(CFilmCameraPro2Doc, CDocument)
END_MESSAGE_MAP()

// CFilmCameraPro2Doc 생성/소멸

// 생성자: CFilmCameraPro2Doc 객체가 생성될 때 호출됩니다.
CFilmCameraPro2Doc::CFilmCameraPro2Doc() noexcept
{
    // TODO: 여기에 일회성 생성 코드를 추가합니다.
    // 객체가 생성될 때 실행되는 초기화 코드 작성
}

// 소멸자: CFilmCameraPro2Doc 객체가 소멸될 때 호출됩니다.
CFilmCameraPro2Doc::~CFilmCameraPro2Doc()
{
    // 문서 객체가 파괴될 때 실행되는 정리 코드 작성
}

// 새로운 문서가 생성될 때 호출됩니다.
BOOL CFilmCameraPro2Doc::OnNewDocument()
{
    // 기본 CDocument 클래스의 OnNewDocument 함수 호출
    if (!CDocument::OnNewDocument())
        return FALSE; // 문서 생성 실패 시 FALSE 반환

    // TODO: 여기에 재초기화 코드를 추가합니다.
    // 이 문서는 SDI(Single Document Interface)로 구성된 문서입니다.
    // 문서를 다시 사용할 때 필요한 초기화 코드 작성

    return TRUE; // 문서 생성 성공 시 TRUE 반환
}

// CFilmCameraPro2Doc serialization
// Serialize 함수는 문서 데이터를 저장하거나 불러오는 역할을 합니다.
// 파일 입출력 또는 데이터 직렬화 시 호출됩니다.
void CFilmCameraPro2Doc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) // 문서를 저장하는 경우
    {
        // TODO: 여기에 저장 코드를 추가합니다.
        // 예: ar << m_strData;
    }
    else // 문서를 불러오는 경우
    {
        // TODO: 여기에 로딩 코드를 추가합니다.
        // 예: ar >> m_strData;
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
	// 함수 객체 유효한지 확인
	CDocument::AssertValid();
}

void CFilmCameraPro2Doc::Dump(CDumpContext& dc) const
{
	// 디버깅 정보제공
	CDocument::Dump(dc);
}
#endif


// CFilmCameraPro2Doc 명령

BOOL CFilmCameraPro2Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// 파일 열기 실패했을때
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE; // 파일 열기 실패

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 입력 메모리 해제 (R G B)
	// 2차원 배열에 할당된 메모리 해제 - 메모리 누수 방지
	// 새로운 메모리 할당하기 전에 반드시 해제해야함
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
	// 첫번째 입력이미지
	// malloc2D = 2차원 배열 동적으로 할당함
	m_InputImageR = malloc2D(m_inH, m_inW);
	m_InputImageG = malloc2D(m_inH, m_inW);
	m_InputImageB = malloc2D(m_inH, m_inW);

	// 두번째 입력이미지
	m_Input2ImageR = malloc2D(m_inH, m_inW);
	m_Input2ImageG = malloc2D(m_inH, m_inW);
	m_Input2ImageB = malloc2D(m_inH, m_inW);

	COLORREF px; 
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			px = bitmap.GetPixel(k, i); // 픽셀 받아오기 (행, 열)
			// GetRValue : px 변수에서 R값 저장
			// GetGValue : px 변수에서 G값 저장
			// GetBValue : px 변수에서 B값 저장

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
	// 출력 이미지가 비어 있는 경우(즉, 파일이 열리지 않았거나 이미지가 로드되지 않은 경우) 오류 메시지를 표시하고 저장을 중단합니다.
	if (m_OutputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return FALSE;
	}

	// 파일 저장 시 사용할 파일 형식을 설정합니다. 기본적으로 .PNG 파일을 사용합니다.
	static TCHAR BASED_CODE szFilter[] = _T("PNG파일(*.PNG) | *.png | 모든파일(*.*) | *.* ||");
	CFileDialog SaveDlg(TRUE, _T("*.png"), _T(""), OFN_HIDEREADONLY, szFilter);
	if (SaveDlg.DoModal() != IDOK)
		return FALSE;

	// CImage 객체를 생성하여 빈 이미지를 만듭니다.
	CImage bitmap;
	bitmap.Create(m_outW, m_outH, 32); // 폭(m_outW), 높이(m_outH), 비트 깊이 32비트 (RGB + Alpha)

	COLORREF px;
	unsigned char RR, GG, BB;

	// 이미지 데이터를 순회하며 각 픽셀의 R, G, B 값을 설정합니다.
	for (int i = 0; i < m_outW; i++) {
		for (int k = 0; k < m_outH; k++) {
			// 첫 번째 이미지의 R, G, B 값을 가져옵니다.
			RR = m_OutputImageR[k][i];
			GG = m_OutputImageG[k][i];
			BB = m_OutputImageB[k][i];
			
			 // 두 번째 이미지의 R, G, B 값을 가져옵니다.
			RR = m_Output2ImageR[k][i];
			GG = m_Output2ImageG[k][i];
			BB = m_Output2ImageB[k][i];

			// 픽셀 색상 값(RGB)을 생성합니다.
			px = RGB(RR, GG, BB);
			// 생성된 색상 값을 이미지의 특정 위치(i, k)에 설정합니다.
			bitmap.SetPixel(i, k, px);
		}
	}
	// MFC에서는 PNG포멧을 지원한다.
	bitmap.Save(SaveDlg.GetPathName(), Gdiplus::ImageFormatPNG); 
	return TRUE; // 리턴 True해줘야 정상 저장됨
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
	// 입력 이미지에 대한 메모리를 해제
	free2D(m_InputImageR, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageR, m_outH);
	free2D(m_InputImageG, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageG, m_outH);
	free2D(m_InputImageB, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageB, m_outH);

	// 추가적인 입력 이미지에 대한 메모리를 해제
	free2D(m_Input2ImageR, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_Output2ImageR, m_outH);
	free2D(m_Input2ImageG, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_Output2ImageG, m_outH);
	free2D(m_Input2ImageB, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_Output2ImageB, m_outH);

	// 기본 클래스의 OnCloseDocument 함수를 호출하여 추가적인 문서 닫기 작업을 처리
	CDocument::OnCloseDocument();
}

unsigned char** CFilmCameraPro2Doc(int h, int w)
{
    // 2차원 unsigned char 배열을 동적으로 할당하기 위한 함수
    // 높이(h)와 폭(w)을 입력으로 받아 각각의 요소를 255(흰색)로 초기화
    unsigned char** memory;
    
    // 높이만큼의 포인터 배열을 할당
    memory = (unsigned char**)malloc(h * sizeof(unsigned char*));
    
    // 각 포인터가 가리키는 배열(각 행)을 할당
    for (int i = 0; i < h; i++)
        memory[i] = (unsigned char*)malloc(w * sizeof(unsigned char));
    
    // 모든 메모리를 255로 초기화하여 흰색 이미지로 설정
    for (int i = 0; i < h; i++)
        for (int k = 0; k < w; k++)
            memory[i][k] = 255;
    
    return memory; // 할당된 2차원 배열을 반환
}


void CFilmCameraPro2Doc::free2D(unsigned char** memory, int h)
{
	// 2차원 배열의 메모리를 해제하기 위한 함수
    // 각 행에 대해 메모리를 해제하고, 마지막에 전체 배열을 가리키는 포인터도 해제
    if (memory != NULL) {
        for (int i = 0; i < h; i++)
            free(memory[i]); // 각 행에 할당된 메모리 해제
        free(memory); // 배열 전체를 가리키는 포인터 해제
    }
}

double** CFilmCameraPro2Doc::malloc2D_double(int h, int w)
{
    // 2차원 double 배열을 동적으로 할당하기 위한 함수
    // 높이(h)와 폭(w)을 입력으로 받아 각각의 요소를 0으로 초기화
    double** mem;

    // 높이만큼 포인터 배열을 할당
    mem = (double**)malloc(h * sizeof(double*));

    // 각 포인터가 가리키는 배열(각 행)을 할당
    for (int i = 0; i < h; i++)
        mem[i] = (double*)malloc(w * sizeof(double));

    // 모든 메모리를 0으로 초기화
    for (int i = 0; i < h; i++) {
        for (int k = 0; k < w; k++) {
            mem[i][k] = 0; // 각 요소를 0으로 설정
        }
    }
    return mem; // 할당된 2차원 배열을 반환
}


void CFilmCameraPro2Doc::free2D_double(double** memory, int h)
{
    // 2차원 double 배열의 메모리를 해제하기 위한 함수
    // 각 행에 대해 메모리를 해제하고, 마지막에 전체 배열을 가리키는 포인터도 해제
    if (memory != NULL) {
        for (int i = 0; i < h; i++)
            free(memory[i]); // 각 행에 할당된 메모리 해제
        free(memory); // 배열 전체를 가리키는 포인터 해제
    }
}


double CFilmCameraPro2Doc::doubleABS(double x)
{
    // double 타입의 절대값을 계산하는 함수
    // x가 0보다 크거나 같으면 x를 반환하고, 그렇지 않으면 -x를 반환
    if (x >= 0) return x;
    else return -x;
}

// 기존 출력 메모리 해제
void CFilmCameraPro2Doc::memory_free()
{
	// 입력 이미지가 열리지 않았으면 메모리 해제를 수행하지 않고 종료
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}

	// 기존 출력 이미지 메모리 해제 (m_OutputImageR, m_OutputImageG, m_OutputImageB)
    free2D(m_OutputImageR, m_outH);
    free2D(m_OutputImageG, m_outH);
    free2D(m_OutputImageB, m_outH);
    
    // 입력 이미지와 동일한 크기의 출력 이미지 메모리를 할당
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutputImageR = malloc2D(m_outH, m_outW);
    m_OutputImageG = malloc2D(m_outH, m_outW);
    m_OutputImageB = malloc2D(m_outH, m_outW);

    // 기존 2차 출력 이미지 메모리 해제 및 새로운 메모리 할당
    free2D(m_Output2ImageR, m_outH);
    free2D(m_Output2ImageG, m_outH);
    free2D(m_Output2ImageB, m_outH);
    m_Output2ImageR = malloc2D(m_outH, m_outW);
    m_Output2ImageG = malloc2D(m_outH, m_outW);
    m_Output2ImageB = malloc2D(m_outH, m_outW);
}

// 입력값이 0~255 범위를 벗어나지 않도록 제한
unsigned char clamp(int value) {
    if (value < 0) return 0;
    if (value > 255) return 255;
    return static_cast<unsigned char>(value);
}

// 명암조절
void CFilmCameraPro2Doc::pixel_contrast()
{
	float value;

	 // 입력 이미지의 각 픽셀에 대해 명암 조절 수행
	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			//흑백값으로 변환
			value = (m_InputImageR[x][y] + m_InputImageG[x][y] + m_InputImageB[x][y]) / 3;

			// ========== 실제 실행 코드 ===========
			// RGB평균값으로 명암을 구별하였음
			// value가 127 초과면 더 밝게
			 // value가 127 초과이면 밝게 조절
            if (value > 127) {
                value = (value - 127) * 0.1;
                
                // 각 채널에 대해 명암 조절
                m_Input2ImageR[x][y] = clamp(m_InputImageR[x][y] + value);
                m_Input2ImageG[x][y] = clamp(m_InputImageG[x][y] + value);
                m_Input2ImageB[x][y] = clamp(m_InputImageB[x][y] + value);
            }
            // value가 127 이하이면 어둡게 조절
            else {
                value = (127 - value) * 0.3;
                
                // 각 채널에 대해 명암 조절
                m_Input2ImageR[x][y] = clamp(m_InputImageR[x][y] - value);
                m_Input2ImageG[x][y] = clamp(m_InputImageG[x][y] - value);
                m_Input2ImageB[x][y] = clamp(m_InputImageB[x][y] - value);
            }
		}
	}
}

// 색상 필터
void CFilmCameraPro2Doc::pixel_color_filter(float Red_filter, float Green_filter, flaot Blue_filter)
{
	for (int x = 0; x < m_inH; x++) {
		for (int y = 0; y < m_inW; y++) {

			// Red 필터 적용
            m_Output2ImageR[x][y] = clamp(m_Input2ImageR[x][y] + Red_filter);
            // Green 필터 적용
            m_Output2ImageG[x][y] = clamp(m_Input2ImageG[x][y] + Green_filter);
            // Blue 채널은 그대로 유지
            m_Output2ImageB[x][y] = m_Input2ImageB[x][y];
		}
	}
}

// 가우시안 효과 적용
void CFilmCameraPro2Doc::pixel_noise_gaussian()
{
	float num1;
	float num2;

	float value = 0;

	// 입력 이미지의 모든 픽셀에 대해 가우시안 노이즈 적용
	for (int x = 0; x < m_inH; x++)
		for (int y = 0; y < m_inW; y++) {

			// 랜덤한 두 값 생성 (임의의 큰 수로 나누어 작은 값 생성)
			num1 = (float)rand() / 51251; // 51251은 임의의 값으로, 생성되는 num1이 매우 작음
			num2 = (float)rand() / 51251; // 51251은 임의의 값으로, 생성되는 num2가 매우 작음

			// 가우시안 함수
			// sqrt(-2 * 분산 * log(num1)) * cos(2 * PI * num2)
			value = sqrt(-2 * 150 * log(num1)) * cos(2 * 3.141592 * num2); // 분산 400으로 설정
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
		}
}

// 엠보싱 효과를 적용하는 함수
void CFilmCameraPro2Doc::pixel_embos()
{
    // 엠보싱에 사용할 마스크 설정
    double mask[3][3] = { 
                        { -1.,  0.,  0.},  // 왼쪽 상단에서 현재 위치를 강조하고 오른쪽 하단을 약화
                        {  0.,  0.,  0.},  // 중앙을 기준으로 변경 없음
                        {  0.,  0.,  1.}   // 오른쪽 하단을 강조
                        };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); // 입력 이미지를 위한 메모리 (가장자리 확장)
    double** tmpOutput = malloc2D_double(m_outH, m_outW); // 출력 이미지를 위한 메모리

    // 입력 이미지의 RGB 값을 평균하여 그레이스케일 값으로 변환하고, tmpInput 배열에 저장
    for (int x = 0; x < m_inH; x++) {
        for (int y = 0; y < m_inW; y++) {
            tmpInput[x + 1][y + 1] = (unsigned char)((m_InputImageR[x][y] + m_InputImageG[x][y] + m_InputImageB[x][y]) / 3);
        }
    }

    double S; // 마스크와 입력 이미지의 합을 저장할 변수
    // 엠보싱 연산 수행
    for (int x = 0; x < m_inH; x++) {
        for (int y = 0; y < m_inW; y++) {
            S = 0.0; // 누적 합 초기화
            for (int m = 0; m < 3; m++) { // 마스크 3x3 영역 순회
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[x + m][y + n] * mask[m][n]; // 마스크와 입력 이미지의 합을 계산
                }
            }
            tmpOutput[x][y] = S; // 계산된 값을 임시 출력 배열에 저장
        }
    }

    // 엠보싱 효과를 위해 모든 값에 127을 더해 중간 밝기를 맞춤
    for (int x = 0; x < m_outH; x++) {
        for (int y = 0; y < m_outW; y++) {
            tmpOutput[x][y] += 127.0;
        }
    }

    // tmpOutput의 값을 m_OutputImage로 변환 (오버플로우, 언더플로우 방지)
    for (int x = 0; x < m_outH; x++) {
        for (int y = 0; y < m_outW; y++) {
            double v = tmpOutput[x][y]; // 임시 출력 배열의 값을 가져옴
            if (v > 255.0) v = 255.0; // 오버플로우 방지
            if (v < 0.0) v = 0.0; // 언더플로우 방지
            m_OutputImageR[x][y] = m_OutputImageG[x][y] = m_OutputImageB[x][y] = (unsigned char)v; // 최종 출력 이미지에 저장
        }
    }

    // 할당된 메모리 해제
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
}

void CFilmCameraPro2Doc::OnEffect1()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}

	// 기존 출력 이미지 메모리 해제 및 새로운 메모리 할당
	memory_free();

	// 이미지 효과 적용
	pixel_contrast(); // 명암조절
	pixel_color_filter(40,25,0); // 색상필터
	pixel_noise_gaussian(); // 가우시안
}

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
	pixel_color_filter_effect(0,10,10); //색감 조절
	pixel_noise_gaussian_effect(); //가우시안

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
