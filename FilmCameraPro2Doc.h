// FilmCameraPro2Doc.h: CFilmCameraPro2Doc 클래스의 인터페이스
// CFilmCameraPro2Doc: 문서(Document) 관련 기능을 담당하는 클래스

#pragma once

// CDocument 클래스는 MFC에서 문서-뷰 구조의 문서 역할을 수행하는 기본 클래스입니다.
class CFilmCameraPro2Doc : public CDocument
{
protected: 
    // serialization에서만 사용되는 생성자 (객체를 파일로 저장하거나 파일에서 로드할 때 사용)
	CFilmCameraPro2Doc() noexcept; 
	DECLARE_DYNCREATE(CFilmCameraPro2Doc) // 동적 생성 및 런타임 클래스 정보 제공 매크로

// 특성입니다. (Attributes)
public:

// 작업입니다. (Operations)
public:

// 재정의입니다. (Overrides)
public:
	// 새로운 문서를 생성할 때 호출되는 함수
	virtual BOOL OnNewDocument();
	// 문서 데이터를 저장 또는 로드할 때 호출되는 함수
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	// 검색 핸들러 초기화 (파일 미리보기 등에서 사용)
	virtual void InitializeSearchContent();
	// 썸네일 이미지를 그릴 때 호출되는 함수
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다. (Implementation)
public:
	// 소멸자 (클래스 객체가 삭제될 때 호출)
	virtual ~CFilmCameraPro2Doc();
#ifdef _DEBUG
	// 디버깅을 위한 함수 (유효성 검사)
	virtual void AssertValid() const;
	// 디버깅을 위한 함수 (객체 상태 덤프)
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수 (Generated message map functions)
protected:
	DECLARE_MESSAGE_MAP() // 메시지 맵 선언

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	// 문서를 열 때 호출되는 함수
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	// 문서를 저장할 때 호출되는 함수
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	// 문서를 닫을 때 호출되는 함수
	virtual void OnCloseDocument();

	// 2차원 배열 메모리 할당 함수 (unsigned char 타입)
	unsigned char** malloc2D(int h, int w);
	// 2차원 배열 메모리 해제 함수 (unsigned char 타입)
	void free2D(unsigned char** memory, int h);

	// 입력 이미지(R, G, B 채널)의 데이터를 저장하는 포인터
	unsigned char** m_InputImageR = NULL;
	unsigned char** m_InputImageG = NULL;
	unsigned char** m_InputImageB = NULL;

	// 추가 입력 이미지(R, G, B 채널)의 데이터를 저장하는 포인터
	unsigned char** m_Input2ImageR = NULL;
	unsigned char** m_Input2ImageG = NULL;
	unsigned char** m_Input2ImageB = NULL;

	// 출력 이미지(R, G, B 채널)의 데이터를 저장하는 포인터
	unsigned char** m_OutputImageR = NULL;
	unsigned char** m_OutputImageG = NULL;
	unsigned char** m_OutputImageB = NULL;

	// 추가 출력 이미지(R, G, B 채널)의 데이터를 저장하는 포인터
	unsigned char** m_Output2ImageR = NULL;
	unsigned char** m_Output2ImageG = NULL;
	unsigned char** m_Output2ImageB = NULL;

	// 이미지의 높이 및 너비를 저장하는 변수 (입력 및 출력 이미지)
	int m_inH = 0; // 입력 이미지 높이
	int m_inW = 0; // 입력 이미지 너비
	int m_outH = 0; // 출력 이미지 높이
	int m_outW = 0; // 출력 이미지 너비

	// 절대값을 반환하는 함수 (double 타입)
	double doubleABS(double x);
	// 2차원 배열 메모리 해제 함수 (double 타입)
	void free2D_double(double** memory, int h);
	// 2차원 배열 메모리 할당 함수 (double 타입)
	double** malloc2D_double(int h, int w);

	// 이미지 효과 관련 함수들
	void OnEffect1(); // 효과 1 적용 함수
	void pixel_noise_gaussian(); // 가우시안 노이즈 효과 함수
	void memory_free(); // 할당된 메모리 해제 함수
	void pixel_contrast(); // 명암 조절 효과 함수
	void pixel_color_filter(); // 색상 필터 효과 함수
	BOOL LoadFile(); // 파일 로드 함수
	void OnEffect2(); // 효과 2 적용 함수
	void OnEffect3(); // 효과 3 적용 함수
	void pixel_embos(); // 엠보싱 효과 함수
	void OnEffect4(); // 효과 4 적용 함수
	void pixel_gray(); // 그레이스케일 변환 함수
};
