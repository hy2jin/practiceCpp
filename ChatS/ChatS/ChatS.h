
// ChatS.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CChatSApp:
// �� Ŭ������ ������ ���ؼ��� ChatS.cpp�� �����Ͻʽÿ�.
//

class CChatSApp : public CWinApp
{
public:
	CChatSApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	CString m_strPortS;
	CString m_strLogPeriodS, m_strLogPeriodC;

// �����Դϴ�.
	DECLARE_MESSAGE_MAP()
};

extern CChatSApp theApp;

//extern CString m_strPortS;
//extern CString m_strLogPeriodS, m_strLogPeriodC;