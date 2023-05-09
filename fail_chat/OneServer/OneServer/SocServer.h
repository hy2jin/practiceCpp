#pragma once

#include "SocCom.h"
#define UM_ACCEPT WM_USER+1

// CSocServer 명령 대상입니다.

class CSocServer : public CSocket
{
public:
	CSocServer();
	virtual ~CSocServer();

	CSocCom m_socCom;
	CSocCom* GetAcceptSocCom();

	HWND m_hWnd;
	void CSocServer::Init(HWND hWnd);
	virtual void OnAccept(int nErrorCode);
};


