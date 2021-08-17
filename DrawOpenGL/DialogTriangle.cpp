// DialogTriangle.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogTriangle.h"
#include "afxdialogex.h"


// DialogTriangle dialog

IMPLEMENT_DYNAMIC(DialogTriangle, CDialogEx)

DialogTriangle::DialogTriangle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TRIANGLE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogTriangle::~DialogTriangle()
{
	m_Doc = NULL;
}

void DialogTriangle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogTriangle, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RANDOM_TRIANGLE, &DialogTriangle::OnClickedButtonRandomTriangle)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogTriangle::OnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// DialogTriangle message handlers


void DialogTriangle::OnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_color = line_color.GetColor();
}


void DialogTriangle::OnClickedButtonRandomTriangle()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 41;
	m_Doc->m_size = GetDlgItemInt(IDC_EDIT1);
	if (m_Doc->m_size <= 0)
	{
		m_Doc->m_size = 1;
	}

	EndDialog(0);
}

