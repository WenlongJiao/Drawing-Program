
// DrawOpenGLDoc.h : interface of the CDrawOpenGLDoc class
//


#pragma once


class CDrawOpenGLDoc : public CDocument
{
protected: // create from serialization only
	CDrawOpenGLDoc() noexcept;
	DECLARE_DYNCREATE(CDrawOpenGLDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDrawOpenGLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
// Custom data structure
	
	// data structure of drawing directly
	struct d_line
	{
		CPoint p1, p2;
		int size;
		COLORREF color;

		d_line() {}
		d_line(CPoint p1, CPoint p2, int size, COLORREF color) 
		{
			this->p1 = p1;
			this->p2 = p2;
			this->size = size;
			this->color = color;
		}

	};

	struct d_circle
	{
		CPoint p0;
		int radius;
		int size;
		COLORREF color;

		d_circle() {}
		d_circle(CPoint p0, int radius, int size, COLORREF color) 
		{
			this->p0 = p0;
			this->radius = radius;
			this->size = size;
			this->color = color;
		}
	};

public:
	
	// Store all drawing content

	std::vector<d_line> v_line;
	std::vector<d_circle> v_circle;

	// 1 = point, 2 = line
	int m_type;

	COLORREF m_color;
	int m_size;



	// cpen function
	void line_cpen(CDC* pDC, COLORREF color, CPoint p1, CPoint p2, int size);
	void circle_cpen(CDC* pDC, COLORREF color, CPoint p0, int radius, int size);



	

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
