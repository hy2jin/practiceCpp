
// ChatS.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CChatSApp:
// 이 클래스의 구현에 대해서는 ChatS.cpp을 참조하십시오.
//

class CChatSApp : public CWinApp
{
public:
	CChatSApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	CString m_strPortS;
	CString m_strLogPeriodS, m_strLogPeriodC;

// 구현입니다.
	DECLARE_MESSAGE_MAP()
};

extern CChatSApp theApp;

//extern CString m_strPortS;
//extern CString m_strLogPeriodS, m_strLogPeriodC;