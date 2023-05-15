#pragma once

// CListenSocket ��� ����Դϴ�.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	virtual void OnAccept(int nErrorCode);

public:
	CPtrList m_ptrChildSocketList;

	void BroadCast(char* pszBuffer, int len);
	void CloseChildSocket(CSocket* pChild);

};
