#pragma once
#include "stdafx.h"

// CChildSocket ��� ����Դϴ�.

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


