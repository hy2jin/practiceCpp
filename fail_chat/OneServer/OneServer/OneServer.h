
// OneServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// COneServerApp:
// �� Ŭ������ ������ ���ؼ��� OneServer.cpp�� �����Ͻʽÿ�.
//

class COneServerApp : public CWinApp
{
public:
	COneServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern COneServerApp theApp;