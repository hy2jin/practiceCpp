
// ValueClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CValueClientApp:
// �� Ŭ������ ������ ���ؼ��� ValueClient.cpp�� �����Ͻʽÿ�.
//

class CValueClientApp : public CWinApp
{
public:
	CValueClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CValueClientApp theApp;