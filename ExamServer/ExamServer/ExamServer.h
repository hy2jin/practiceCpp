
// ExamServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CExamServerApp:
// �� Ŭ������ ������ ���ؼ��� ExamServer.cpp�� �����Ͻʽÿ�.
//

class CExamServerApp : public CWinApp
{
public:
	CExamServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CExamServerApp theApp;