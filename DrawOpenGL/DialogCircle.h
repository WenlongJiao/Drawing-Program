#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogCircle dialog

class DialogCircle : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCircle)

public:
	DialogCircle(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogCircle();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CIRCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CDrawDoc* m_Doc = NULL;

public:
	CMFCColorButton circle_color;
	afx_msg void OnClickedMfccolorbutton1();
	afx_msg void OnClickedButtonDrawCircle();
};
