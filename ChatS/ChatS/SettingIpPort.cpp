// SettingIpPort.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatSDlg.h"
#include "SettingIpPort.h"
#include "afxdialogex.h"


// CSettingIpPort ��ȭ �����Դϴ�.

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


// CSettingIpPort �޽��� ó�����Դϴ�.


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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
