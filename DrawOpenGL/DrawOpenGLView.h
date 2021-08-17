
// DrawOpenGLView.h : interface of the CDrawOpenGLView class
//

#pragma once

#include "DrawOpenGLDoc.h"

class CDrawOpenGLView : public CView
{
protected: // create from serialization only
	CDrawOpenGLView() noexcept;
	DECLARE_DYNCREATE(CDrawOpenGLView)

// Attributes
public:
	CDrawOpenGLDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDrawOpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	
	
	
protected:
	CDrawOpenGLDoc* m_Doc = NULL;
};

#ifndef _DEBUG  // debug version in DrawOpenGLView.cpp
inline CDrawOpenGLDoc* CDrawOpenGLView::GetDocument() const
   { return reinterpret_cast<CDrawOpenGLDoc*>(m_pDocument); }
#endif

