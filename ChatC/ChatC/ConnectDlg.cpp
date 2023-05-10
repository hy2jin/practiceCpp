// ConnectDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatC.h"
#include "ConnectDlg.h"
#include "afxdialogex.h"


// CConnectDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConnectDlg, CDialogEx)

CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConnectDlg::IDD, pParent)
{

}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_OK, &CConnectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConnectDlg 메시지 처리기입니다.


void CConnectDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_IPADDRESS1, m_strIPAddress);

	CDialogEx::OnOK();
}


BOOL CConnectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_IPADDRESS1, _T("127.0.0.1"));	//루프백으로 초기화

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
