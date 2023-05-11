#pragma once
#include "stdafx.h"

// CListenSocket ��� ����Դϴ�.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

public:
	CPtrList m_ptrChildSocketList;	//����� Ŭ���̾�Ʈ ���� ��ü�� �����ϴ� ����Ʈ ��ü ����
	CAsyncSocket* m_pClientSocket;	//��

	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pChild);
	void BroadCast(char* pszBuffer, int len);
};


