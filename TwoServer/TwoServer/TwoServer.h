
// TwoServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTwoServerApp:
// �� Ŭ������ ������ ���ؼ��� TwoServer.cpp�� �����Ͻʽÿ�.
//

class CTwoServerApp : public CWinApp
{
public:
	CTwoServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTwoServerApp theApp;