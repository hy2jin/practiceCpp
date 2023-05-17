// LogPeriod.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatSDlg.h"
#include "LogPeriod.h"
#include "afxdialogex.h"


// CLogPeriod ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLogPeriod, CDialog)

CLogPeriod::CLogPeriod(CWnd* pParent /*=NULL*/)
	: CDialog(CLogPeriod::IDD, pParent)
{

}

CLogPeriod::~CLogPeriod()
{
}

void CLogPeriod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogPeriod, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPERIOD, &CLogPeriod::OnBnClickedButtonSaveperiod)
END_MESSAGE_MAP()


// CLogPeriod �޽��� ó�����Դϴ�.


void CLogPeriod::OnBnClickedButtonSaveperiod()
{

	GetDlgItemText(IDC_EDIT_PERIOD_S, strServerPeriod);
	GetDlgItemText(IDC_EDIT_PERIOD_C, strClientPeriod);

	CDialog::OnOK();
}


BOOL CLogPeriod::OnInitDialog()
{
	CDialog::OnInitDialog();

	CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();

	SetDlgItemText(IDC_EDIT_PERIOD_S, pMain->m_strLogPeriodS);
	SetDlgItemText(IDC_EDIT_PERIOD_C, pMain->m_strLogPeriodC);

	return TRUE;
}
