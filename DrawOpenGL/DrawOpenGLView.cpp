
// DrawOpenGLView.cpp : implementation of the CDrawOpenGLView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DrawOpenGL.h"
#endif

#include "DrawOpenGLDoc.h"
#include "DrawOpenGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawOpenGLView

IMPLEMENT_DYNCREATE(CDrawOpenGLView, CView)

BEGIN_MESSAGE_MAP(CDrawOpenGLView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CDrawOpenGLView construction/destruction

CDrawOpenGLView::CDrawOpenGLView() noexcept
{
	// TODO: add construction code here
	

}

CDrawOpenGLView::~CDrawOpenGLView()
{
	m_Doc = NULL;
}

BOOL CDrawOpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDrawOpenGLView drawing

void CDrawOpenGLView::OnDraw(CDC* /*pDC*/)
{
	CDrawOpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!m_Doc) 
		m_Doc = GetDocument();

	// TODO: add draw code for native data here
}


// CDrawOpenGLView printing

BOOL CDrawOpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawOpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawOpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDrawOpenGLView diagnostics

#ifdef _DEBUG
void CDrawOpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawOpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawOpenGLDoc* CDrawOpenGLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawOpenGLDoc)));
	return (CDrawOpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawOpenGLView message handlers

CPoint oldpoint, newpoint, parentpoint;


void CDrawOpenGLView::OnLButtonDown(UINT nFlags, CPoint point)
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
	}

	ReleaseDC(dc1);

	CView::OnLButtonDown(nFlags, point);
}


void CDrawOpenGLView::OnLButtonUp(UINT nFlags, CPoint point)
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
		m_Doc->v_line.push_back(CDrawOpenGLDoc::d_line(oldpoint, newpoint, m_Doc->m_size, m_Doc->m_color));

		break;
	case 3:
		int radius = std::sqrt((newpoint.x - oldpoint.x) * (newpoint.x - oldpoint.x) + ((newpoint.y - oldpoint.y) * (newpoint.y - oldpoint.y)));

		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y - radius, oldpoint.x + radius, oldpoint.y + radius), CPoint(0, 0), CPoint(0, 0));

		m_Doc->circle_cpen(dc2, m_Doc->m_color, oldpoint, radius, m_Doc->m_size);
		m_Doc->v_circle.push_back(CDrawOpenGLDoc::d_circle(oldpoint, radius, m_Doc->m_size, m_Doc->m_color));
		break;
	}

	ReleaseDC(dc2);
	ReleaseDC(dc1);
	CView::OnLButtonUp(nFlags, point);
}


void CDrawOpenGLView::OnMouseMove(UINT nFlags, CPoint point)
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
		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y - radius, oldpoint.x + radius, oldpoint.y + radius), CPoint(0, 0), CPoint(0, 0));
		newpoint = point;
		radius = std::sqrt((newpoint.x - oldpoint.x) * (newpoint.x - oldpoint.x) + (newpoint.y - oldpoint.y) * (newpoint.y - oldpoint.y));
		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y - radius, oldpoint.x + radius, oldpoint.y + radius), CPoint(0, 0), CPoint(0, 0));
	}

	ReleaseDC(dc2);
	ReleaseDC(dc1);
	CView::OnMouseMove(nFlags, point);
}
