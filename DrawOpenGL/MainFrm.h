
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "DialogLine.h"
#include "DialogCircle.h"
#include "DialogTriangle.h"
#include "DialogPolygon.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	CDrawDoc* m_Doc = NULL;
	afx_msg void OnShapeLine();
	afx_msg void OnShapeCircle();
	afx_msg void OnShapeTriangle();
	afx_msg void OnShapePolygon();
};


