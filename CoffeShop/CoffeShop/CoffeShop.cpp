
// CoffeShop.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CCoffeShopApp 생성

CCoffeShopApp::CCoffeShopApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CCoffeShopApp 개체입니다.

CCoffeShopApp theApp;


// CCoffeShopApp 초기화

BOOL CCoffeShopApp::InitInstance()
{
	CWinApp::InitInstance();

	CCoffeShopDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

