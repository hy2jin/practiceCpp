#pragma once

// CListenSocket ��� ����Դϴ�.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();


	virtual void OnAccept(int nErrorCode);
};


