
// ExamServer.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "ExamServer.h"
#include "ExamServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamServerApp

BEGIN_MESSAGE_MAP(CExamServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExamServerApp ����

CExamServerApp::CExamServerApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CExamServerApp ��ü�Դϴ�.

CExamServerApp theApp;


// CExamServerApp �ʱ�ȭ

BOOL CExamServerApp::InitInstance()
{
	CWinApp::InitInstance();

	WSADATA temp;
	WSAStartup(0x0202, &temp);	// ���� ��� ����, 0x0202 : 2.2version

	CExamServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	WSACleanup();				// ���� ����
	
	return FALSE;
}

