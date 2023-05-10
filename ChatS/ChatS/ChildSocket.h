#pragma once
#include "stdafx.h"

// CChildSocket 명령 대상입니다.

class CChildSocket : public CSocket
{
public:
	CChildSocket();
	virtual ~CChildSocket();

public:
	CAsyncSocket *m_pListenSocket;
	void SetListenSocket(CAsyncSocket* pSocket);
	void OnClose(int nErrorCode);
	void OnReceive(int nErrorCode);
};


