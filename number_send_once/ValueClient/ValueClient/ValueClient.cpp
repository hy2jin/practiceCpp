
// ValueClient.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "ValueClient.h"
#include "ValueClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CValueClientApp

BEGIN_MESSAGE_MAP(CValueClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CValueClientApp ����

CValueClientApp::CValueClientApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CValueClientApp ��ü�Դϴ�.

CValueClientApp theApp;


// CValueClientApp �ʱ�ȭ

BOOL CValueClientApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CValueClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

