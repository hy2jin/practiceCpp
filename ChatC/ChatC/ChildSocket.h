#pragma once

// CChildSocket 명령 대상입니다.

class CChildSocket : public CSocket
{
public:
	CChildSocket();
	virtual ~CChildSocket();

public:
	CAsyncSocket *m_pListenSoc;
	void SetListenSocket(CAsyncSocket* pSocket);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


