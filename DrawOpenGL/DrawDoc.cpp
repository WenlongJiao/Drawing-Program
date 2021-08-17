
// DrawDoc.cpp : implementation of the CDrawDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDrawDoc

IMPLEMENT_DYNCREATE(CDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawDoc, CDocument)
END_MESSAGE_MAP()


// CDrawDoc construction/destruction

CDrawDoc::CDrawDoc() noexcept
{
	// TODO: add one-time construction code here

}

CDrawDoc::~CDrawDoc()
{
}

BOOL CDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CDrawDoc serialization

void CDrawDoc::Serialize(CArchive& ar)
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
void CDrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CDrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDrawDoc::SetSearchContent(const CString& value)
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

// CDrawDoc diagnostics

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrawDoc commands


void CDrawDoc::line_cpen(CDC* pDC, COLORREF color, CPoint p1, CPoint p2, int size)
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

	pDC->MoveTo(p1);
	pDC->LineTo(p2);

	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
}




void CDrawDoc::circle_cpen(CDC* pDC, COLORREF color, CPoint p0, int radius, int size) 
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
	pDC->Arc(CRect(p0.x - radius, p0.y - radius, p0.x + radius, p0.y + radius), CPoint(0, 0), CPoint(0, 0));
	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
}



// draw a dot (CPen)
void CDrawDoc::dot(CDC* pDC, COLORREF color, int x, int y, int size)
{
	// TODO: Add your implementation code here.
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
	pDC->MoveTo(x, y);
	pDC->LineTo(x, y);
	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
	return;
}
