
// DrawOpenGLDoc.cpp : implementation of the CDrawOpenGLDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DrawOpenGL.h"
#endif

#include "DrawOpenGLDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDrawOpenGLDoc

IMPLEMENT_DYNCREATE(CDrawOpenGLDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawOpenGLDoc, CDocument)
END_MESSAGE_MAP()


// CDrawOpenGLDoc construction/destruction

CDrawOpenGLDoc::CDrawOpenGLDoc() noexcept
{
	// TODO: add one-time construction code here

}

CDrawOpenGLDoc::~CDrawOpenGLDoc()
{
}

BOOL CDrawOpenGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CDrawOpenGLDoc serialization

void CDrawOpenGLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDrawOpenGLDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
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

// Support for Search Handlers
void CDrawOpenGLDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDrawOpenGLDoc::SetSearchContent(const CString& value)
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

// CDrawOpenGLDoc diagnostics

#ifdef _DEBUG
void CDrawOpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawOpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrawOpenGLDoc commands


void CDrawOpenGLDoc::line_cpen(CDC* pDC, COLORREF color, CPoint p1, CPoint p2, int size)
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

	pDC->MoveTo(p1);
	pDC->LineTo(p2);

	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
}




void CDrawOpenGLDoc::circle_cpen(CDC* pDC, COLORREF color, CPoint p0, int radius, int size) 
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
	pDC->Arc(CRect(p0.x - radius, p0.y - radius, p0.x + radius, p0.y + radius), CPoint(0, 0), CPoint(0, 0));
	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
}
