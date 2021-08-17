
// DrawOpenGL.h : main header file for the DrawOpenGL application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDrawOpenGLApp:
// See DrawOpenGL.cpp for the implementation of this class
//

class CDrawOpenGLApp : public CWinApp
{
public:
	CDrawOpenGLApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawOpenGLApp theApp;
