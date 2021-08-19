
// DrawDoc.h : interface of the CDrawDoc class
//


#pragma once


class CDrawDoc : public CDocument
{
protected: // create from serialization only
	CDrawDoc() noexcept;
	DECLARE_DYNCREATE(CDrawDoc)

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
	virtual ~CDrawDoc();
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


	// vertex of polygon
	struct vertex
	{
		int x, y;
		vertex() {}
		vertex(int xx, int yy)
		{
			this->x = xx;
			this->y = yy;
		}
	};


	// polygon
	struct polygon
	{
		int vertex_num;
		std::vector<vertex> vertexes;

		polygon() {}
		polygon(int n, std::vector<vertex> v)
		{
			this->vertex_num = n;
			this->vertexes = v;
		}
	};


	
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

	struct d_polygon
	{
		std::vector<CPoint> ps;
		int size;
		COLORREF color;

		d_polygon() {}
		d_polygon(std::vector<CPoint> ps, int size, COLORREF color)
		{
			this->ps = ps;
			this->size = size;
			this->color = color;
		}
	};

	struct d_ellipse
	{
		CPoint x0, y0;
		COLORREF color;
		int size;

		d_ellipse() {};
		d_ellipse(CPoint x0, CPoint y0, int size, COLORREF color)
		{
			this->x0 = x0;
			this->y0 = y0;
			this->size = size;
			this->color = color;
		}
	};



public:
	
	double pi = acos(-1.0);

	// Store all drawing content

	std::vector<d_line> v_line;
	std::vector<d_circle> v_circle;
	std::vector<d_polygon> v_polygon;
	std::vector<d_ellipse> v_ellipse;

	// 1 = point, 2 = line, 3 = line, 41 = random triangle
	// 5 = polygon, 6 = ellipse
	int m_type;

	// color
	COLORREF m_color;

	// thickness
	int m_size;

	// is drawing polygon?
	BOOL is_d_polygon = FALSE;

	// vertex num of triangle
	int tri_vtx = 1;

	// cpen function
	void line_cpen(CDC* pDC, COLORREF color, CPoint p1, CPoint p2, int size);
	void circle_cpen(CDC* pDC, COLORREF color, CPoint p0, int radius, int size);
	void ellipse_cpen(CDC* pDC, COLORREF color, CPoint x0, CPoint y0, int size);



	

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	void dot(CDC* pDC, COLORREF color, int x, int y, int size);
};
