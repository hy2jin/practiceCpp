// ListenSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatCDlg.h"
#include "ListenSocket.h"
#include "ClientSocket.h"


// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket ��� �Լ�


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CClientSocket* pClient = new CClientSocket();	//������ ������ ������ ���� ��ü ����
	BOOL check = Accept(*pClient);

	if (check == FALSE)
	{
		delete pClient;
		AfxMessageBox(_T("FAIL"));
	}

	CSocket::OnAccept(nErrorCode);
}
