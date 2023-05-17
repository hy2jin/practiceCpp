// SettingIpPort.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatSDlg.h"
#include "SettingIpPort.h"
#include "afxdialogex.h"


// CSettingIpPort 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSettingIpPort, CDialog)

CSettingIpPort::CSettingIpPort(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingIpPort::IDD, pParent)
{

}

CSettingIpPort::~CSettingIpPort()
{
}

void CSettingIpPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingIpPort, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SETTING, &CSettingIpPort::OnBnClickedButtonSaveSetting)
END_MESSAGE_MAP()


// CSettingIpPort 메시지 처리기입니다.


void CSettingIpPort::OnBnClickedButtonSaveSetting()
{
	GetDlgItemText(IDC_IPADDRESS_C, strIPC);
	GetDlgItemText(IDC_EDIT_PORT_C, strPortC);
	GetDlgItemText(IDC_EDIT_PORT_S, strPortS);

	CDialog::OnOK();
}



BOOL CSettingIpPort::OnInitDialog()
{
	CDialog::OnInitDialog();

	CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();

	SetDlgItemText(IDC_IPADDRESS_C, pMain->m_strIpC);
	SetDlgItemText(IDC_EDIT_PORT_C, pMain->m_strPortC);
	SetDlgItemText(IDC_EDIT_PORT_S, pMain->m_strPortS);

	return FALSE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
