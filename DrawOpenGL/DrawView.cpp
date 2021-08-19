
// DrawView.cpp : implementation of the CDrawView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CDrawView construction/destruction

CDrawView::CDrawView() noexcept
{
	// TODO: add construction code here
	

}

CDrawView::~CDrawView()
{
	m_Doc = NULL;
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDrawView drawing

void CDrawView::OnDraw(CDC* /*pDC*/)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!m_Doc) 
		m_Doc = GetDocument();

	// TODO: add draw code for native data here
}


// CDrawView printing

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDrawView diagnostics

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView message handlers

CPoint oldpoint, newpoint, originpoint;
std::vector<CPoint> polygon_vtx;


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* dc1 = GetDC();

	switch (m_Doc->m_type)
	{
	case 2:
		oldpoint = point;
		newpoint = point;
		
		break;
	case 3:
		oldpoint = point;
		newpoint = point;
		
		break;
	case 41:
		if (m_Doc->is_d_polygon == FALSE && m_Doc->tri_vtx == 1)
		{
			originpoint = point;
			oldpoint = point;
			newpoint = point;
			m_Doc->is_d_polygon = TRUE;
			polygon_vtx.clear();
			polygon_vtx.push_back(originpoint);
		}
		else if (m_Doc->is_d_polygon == TRUE && m_Doc->tri_vtx == 2)
		{
			m_Doc->line_cpen(dc1, m_Doc->m_color, newpoint, originpoint, m_Doc->m_size);
			m_Doc->tri_vtx = 1;
			m_Doc->is_d_polygon = FALSE;
			m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));
		}
		else
		{
			newpoint = point;
			polygon_vtx.push_back(newpoint);
		}
		
		break;
	case 5:
		if (m_Doc->is_d_polygon == FALSE)
		{
			originpoint = point;
			oldpoint = point;
			newpoint = point;
			m_Doc->is_d_polygon = TRUE;
			polygon_vtx.clear();
			polygon_vtx.push_back(originpoint);
		}

		break;
	case 6:
		oldpoint = point;
		newpoint = point;

		break;
	}

	ReleaseDC(dc1);

	CView::OnLButtonDown(nFlags, point);
}


void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* dc1 = GetDC(), * dc2 = GetDC();
	int index = -1;
	dc1->SetROP2(R2_NOT);

	switch (m_Doc->m_type)
	{
	case 2:
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);

		m_Doc->line_cpen(dc2, m_Doc->m_color, oldpoint, point, m_Doc->m_size);
		m_Doc->v_line.push_back(CDrawDoc::d_line(oldpoint, newpoint, m_Doc->m_size, m_Doc->m_color));

		break;
	case 3:
	{
		int radius = std::sqrt((newpoint.x - oldpoint.x) * (newpoint.x - oldpoint.x) + ((newpoint.y - oldpoint.y) * (newpoint.y - oldpoint.y)));

		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y + radius, oldpoint.x + radius, oldpoint.y - radius), CPoint(0, 0), CPoint(0, 0));

		m_Doc->circle_cpen(dc2, m_Doc->m_color, oldpoint, radius, m_Doc->m_size);
		m_Doc->v_circle.push_back(CDrawDoc::d_circle(oldpoint, radius, m_Doc->m_size, m_Doc->m_color));

		break;
	}
	case 41:
		if (m_Doc->tri_vtx == 1 && m_Doc->is_d_polygon == TRUE)
		{
			m_Doc->tri_vtx = 2;

			dc1->MoveTo(oldpoint);
			dc1->LineTo(newpoint);

			m_Doc->dot(dc2, m_Doc->m_color, newpoint.x, newpoint.y, m_Doc->m_size);
			m_Doc->line_cpen(dc2, m_Doc->m_color, oldpoint, newpoint, m_Doc->m_size);
			oldpoint = newpoint;
		}
		
		break;
	case 5:
		if (m_Doc->is_d_polygon == TRUE)
		{
			dc1->MoveTo(oldpoint);
			dc1->LineTo(newpoint);

			m_Doc->dot(dc2, m_Doc->m_color, newpoint.x, newpoint.y, m_Doc->m_size);
			m_Doc->line_cpen(dc2, m_Doc->m_color, oldpoint, newpoint, m_Doc->m_size);
			oldpoint = newpoint;
		}

		break;
	case 6:
		dc1->Arc(CRect(oldpoint.x, oldpoint.y, newpoint.x, newpoint.y), CPoint(0, 0), CPoint(0, 0));
		m_Doc->ellipse_cpen(dc2, m_Doc->m_color, oldpoint, newpoint, m_Doc->m_size);
		m_Doc->v_ellipse.push_back(CDrawDoc::d_ellipse(oldpoint, newpoint, m_Doc->m_size, m_Doc->m_color));

		break;
	}
	


	ReleaseDC(dc2);
	ReleaseDC(dc1);
	CView::OnLButtonUp(nFlags, point);
}


void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* dc1 = GetDC(), * dc2 = GetDC();
	int index = -1;
	dc1->SetROP2(R2_NOT);

	if (nFlags == MK_LBUTTON && m_Doc->m_type == 2)
	{
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
		newpoint = point;
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 3)
	{
		int radius = std::sqrt((newpoint.x - oldpoint.x) * (newpoint.x - oldpoint.x) + (newpoint.y - oldpoint.y) * (newpoint.y - oldpoint.y));
		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y + radius, oldpoint.x + radius, oldpoint.y - radius), CPoint(0, 0), CPoint(0, 0));
		newpoint = point;
		radius = std::sqrt((newpoint.x - oldpoint.x) * (newpoint.x - oldpoint.x) + (newpoint.y - oldpoint.y) * (newpoint.y - oldpoint.y));
		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y + radius, oldpoint.x + radius, oldpoint.y - radius), CPoint(0, 0), CPoint(0, 0));
	}
	else if (m_Doc->is_d_polygon == TRUE && m_Doc->m_type == 41)
	{
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
		newpoint = point;
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
	}
	else if (m_Doc->is_d_polygon == TRUE && m_Doc->m_type == 5)
	{
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
		newpoint = point;
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 6)
	{
		dc1->Arc(CRect(oldpoint.x, oldpoint.y, newpoint.x, newpoint.y), CPoint(0, 0), CPoint(0, 0));
		newpoint = point;
		dc1->Arc(CRect(oldpoint.x, oldpoint.y, newpoint.x, newpoint.y), CPoint(0, 0), CPoint(0, 0));
	}

	ReleaseDC(dc2);
	ReleaseDC(dc1);
	CView::OnMouseMove(nFlags, point);
}


void CDrawView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* dc1 = GetDC();
	if (m_Doc->m_type == 41 || m_Doc->m_type == 5)
	{
		m_Doc->line_cpen(dc1, m_Doc->m_color, newpoint, originpoint, m_Doc->m_size);
		m_Doc->tri_vtx = 1;
		m_Doc->is_d_polygon = FALSE;
		m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));
	}

	ReleaseDC(dc1);
	CView::OnLButtonDblClk(nFlags, point);
}
