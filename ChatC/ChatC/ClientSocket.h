#pragma once
#include "stdafx.h"

// CClientSocket 명령 대상입니다.

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


