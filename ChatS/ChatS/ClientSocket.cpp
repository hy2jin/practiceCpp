// ClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatSDlg.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��� �Լ�


void CClientSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	CString strChat = L"";
	char szBuffer [1024];
	::ZeroMemory(szBuffer, 1024);

	if (Receive(szBuffer, 1024) > 0)
	{
		CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();	//���� �����͸� ����Ѵ�.

		strChat.Format(L"%s", szBuffer);
		pMain->HandleListMsgC(strChat);

		if (strChat == L"CLOSED BY SERVER")
		{
			pMain->HandleDisconnectC();
			pMain->OnBnClickedButtonConnectC();
		}
	}
	CSocket::OnReceive(nErrorCode);
}
