
// ValueServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CValueServerApp:
// �� Ŭ������ ������ ���ؼ��� ValueServer.cpp�� �����Ͻʽÿ�.
//

class CValueServerApp : public CWinApp
{
public:
	CValueServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CValueServerApp theApp;