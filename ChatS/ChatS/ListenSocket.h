#pragma once
#include "stdafx.h"

// CListenSocket 명령 대상입니다.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

public:
	CPtrList m_ptrChildSocketList;	//연결된 클라이언트 소켓 객체를 관리하는 리스트 객체 선언

	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pChild);
	void BroadCast(char* pszBuffer, int len);
};


