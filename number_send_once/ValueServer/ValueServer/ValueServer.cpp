
// ValueServer.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "ValueServer.h"
#include "ValueServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CValueServerApp

BEGIN_MESSAGE_MAP(CValueServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CValueServerApp ����

CValueServerApp::CValueServerApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CValueServerApp ��ü�Դϴ�.

CValueServerApp theApp;


// CValueServerApp �ʱ�ȭ

BOOL CValueServerApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CValueServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

