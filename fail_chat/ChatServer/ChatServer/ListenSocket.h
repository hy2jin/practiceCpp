#pragma once

// CListenSocket 명령 대상입니다.

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	CPtrList m_ListenSocket;
	virtual void OnAccept(int nErrorCode);
};


