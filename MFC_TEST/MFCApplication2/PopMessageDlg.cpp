// PopMessageDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "PopMessageDlg.h"
#include "afxdialogex.h"


// CPopMessageDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPopMessageDlg, CDialogEx)

CPopMessageDlg::CPopMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPopMessageDlg::IDD, pParent)
{
	Create(IDD, pParent); //���޷� ��ȭ���� �����
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


// CPopMessageDlg �޽��� ó�����Դϴ�.


void CPopMessageDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	TRACE(_T("okok\n"));

	m_abc = 123;
	UpdateData(FALSE);

	CDialogEx::OnOK();
}


void CPopMessageDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	TRACE(_T("cancel!!\n"));
	CDialogEx::OnCancel();
}
