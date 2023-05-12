// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatCDlg.h"
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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	if (Receive(szBuffer, 1024) > 0)
	//현재 클라이언트 소켓을 이용해 데이터를 받아서
	{
		CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();	//받은 데이터를 출력한다.
		CString receivedMsg = LPCTSTR(szBuffer);
		pMain->m_List.AddString(receivedMsg);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

		if (receivedMsg == "CLOSED BY SERVER")
		{
			pMain->OnBnClickedButtonDisconnect();
		}
	}

	CSocket::OnReceive(nErrorCode);
}
