// ClientSocket.cpp : 구현 파일입니다.
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


// CClientSocket 멤버 함수


void CClientSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	CString strChat = _T("");
	char szBuffer [1024];
	::ZeroMemory(szBuffer, 1024);

	if (Receive(szBuffer, 1024) > 0)
	{
		CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();	//받은 데이터를 출력한다.

		strChat.Format(_T("%s"), szBuffer);
		pMain->HandleListMsgC(strChat);

		if (strChat == _T("CLOSED BY SERVER"))
		{
			pMain->HandleDisconnectC();
			pMain->OnBnClickedButtonConnectC();
		}
	}
	CSocket::OnReceive(nErrorCode);
}
