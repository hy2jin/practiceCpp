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
	, m_bServer(TRUE)
	, m_bClient(TRUE)
{

}

CSettingIpPort::~CSettingIpPort()
{
}

void CSettingIpPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SERVER_SETTING, m_bServer);
	DDX_Check(pDX, IDC_CHECK_CLIENT_SETTING, m_bClient);
}


BEGIN_MESSAGE_MAP(CSettingIpPort, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SETTING, &CSettingIpPort::OnBnClickedButtonSaveSetting)
	ON_BN_CLICKED(IDC_CHECK_SERVER_SETTING, &CSettingIpPort::OnBnClickedCheckServerSetting)
	ON_BN_CLICKED(IDC_CHECK_CLIENT_SETTING, &CSettingIpPort::OnBnClickedCheckClientSetting)
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

	return TRUE;
}


void CSettingIpPort::OnBnClickedCheckServerSetting()
{
	UpdateData();
	GetDlgItem(IDC_EDIT_PORT_S)->EnableWindow(m_bServer);
}


void CSettingIpPort::OnBnClickedCheckClientSetting()
{
	UpdateData();
	GetDlgItem(IDC_EDIT_PORT_C)->EnableWindow(m_bClient);
	GetDlgItem(IDC_IPADDRESS_C)->EnableWindow(m_bClient);
}
