
// ExampleClient.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "ExampleClient.h"
#include "ExampleClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExampleClientApp

BEGIN_MESSAGE_MAP(CExampleClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExampleClientApp ����

CExampleClientApp::CExampleClientApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CExampleClientApp ��ü�Դϴ�.

CExampleClientApp theApp;


// CExampleClientApp �ʱ�ȭ

BOOL CExampleClientApp::InitInstance()
{
	CWinApp::InitInstance();
	WSADATA temp;
	WSAStartup(0x0202, &temp);	// ���� ���ڴٰ� ����

	CExampleClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	WSACleanup();

	return FALSE;
}

