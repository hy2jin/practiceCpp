
// CoffeShop.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "CoffeShop.h"
#include "CoffeShopDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoffeShopApp

BEGIN_MESSAGE_MAP(CCoffeShopApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCoffeShopApp ����

CCoffeShopApp::CCoffeShopApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CCoffeShopApp ��ü�Դϴ�.

CCoffeShopApp theApp;


// CCoffeShopApp �ʱ�ȭ

BOOL CCoffeShopApp::InitInstance()
{
	CWinApp::InitInstance();

	CCoffeShopDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

