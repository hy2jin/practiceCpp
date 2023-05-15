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
	char szBuffer [1024];
	::ZeroMemory(szBuffer, 1024);

	if (Receive(szBuffer, 1024) > 0)
	{
		CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();	//���� �����͸� ����Ѵ�.
		CString receivedMsg = LPCTSTR(szBuffer);
		pMain->HandleListMsgC(receivedMsg);

		if (receivedMsg == "CLOSED BY SERVER")
		{
			pMain->HandleDisconnectC();
			pMain->OnBnClickedButtonConnectC();
		}
	}

	CSocket::OnReceive(nErrorCode);
}
