
// FilmCameraPro2Doc.h: CFilmCameraPro2Doc 클래스의 인터페이스
//


#pragma once


class CFilmCameraPro2Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CFilmCameraPro2Doc() noexcept;
	DECLARE_DYNCREATE(CFilmCameraPro2Doc)

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
	virtual ~CFilmCameraPro2Doc();
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
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	unsigned char** malloc2D(int h, int w);
	void free2D(unsigned char** memory, int h);
	unsigned char** m_InputImageR = NULL;
	unsigned char** m_InputImageG = NULL;
	unsigned char** m_InputImageB = NULL;

	unsigned char** m_Input2ImageR = NULL;
	unsigned char** m_Input2ImageG = NULL;
	unsigned char** m_Input2ImageB = NULL;

	unsigned char** m_OutputImageR = NULL;
	unsigned char** m_OutputImageG = NULL;
	unsigned char** m_OutputImageB = NULL;

	unsigned char** m_Output2ImageR = NULL;
	unsigned char** m_Output2ImageG = NULL;
	unsigned char** m_Output2ImageB = NULL;
	
	unsigned char** m_subImageR = NULL;
	unsigned char** m_subImageG = NULL;
	unsigned char** m_subImageB = NULL;

	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	double doubleABS(double x);
	void free2D_double(double** memory, int h);
	double** malloc2D_double(int h, int w);
	void OnEffect1();
	void pixel_noise_gaussian();
	void memory_free();
	void pixel_contrast();
	void pixel_color_filter();
	void pixel_vignette_sub();
	BOOL LoadFile();
	void OnEffect2();
	void pixel_color_filter_effect2();
	void pixel_noise_gaussian_effect2();
	void OnEffect3();
	void pixel_embos();
	void OnEffect4();
	void pixel_gray();
};
