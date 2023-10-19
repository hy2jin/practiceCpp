// PopMessageDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "PopMessageDlg.h"
#include "afxdialogex.h"


// CPopMessageDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPopMessageDlg, CDialogEx)

CPopMessageDlg::CPopMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPopMessageDlg::IDD, pParent)
{
	Create(IDD, pParent); //비모달로 대화상자 만들기
	m_abc = 1;
}

CPopMessageDlg::~CPopMessageDlg()
{
}

void CPopMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopMessageDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPopMessageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPopMessageDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPopMessageDlg 메시지 처리기입니다.


void CPopMessageDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TRACE(_T("okok\n"));

	m_abc = 123;
	UpdateData(FALSE);

	CDialogEx::OnOK();
}


void CPopMessageDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TRACE(_T("cancel!!\n"));
	CDialogEx::OnCancel();
}
