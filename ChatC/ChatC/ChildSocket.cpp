// ChildSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatCDlg.h"
#include "ChildSocket.h"
#include "ListenSocket.h"

// CChildSocket

CChildSocket::CChildSocket()
{
}

CChildSocket::~CChildSocket()
{
}


// CChildSocket 멤버 함수
void CChildSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSoc = pSocket;

	//클라이언트가 접속해옴을 리스트에 출력
	CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();
	CString strIPAddress = _T("");
	UINT uPortNumber = 0;
	GetPeerName(strIPAddress, uPortNumber);

	pMain->HandleListMsgS(strIPAddress + _T(" 접속"));
}

void CChildSocket::OnClose(int nErrorCode)
{
	//해당 child socket 끊기
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSoc;
	pServerSocket->CloseChildSocket(this);

	//listen socket
	pServerSocket->ShutDown();
	pServerSocket->Close();
	
	CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();
	pMain->HandleDisconnectS(2);
	pMain->OnBnClickedButtonOpenS();

	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	CString strRecIp = _T("");
	UINT uPortNumber = 0;
	GetPeerName(strRecIp, uPortNumber);

	int len = 0;
	if ((len = Receive(szBuffer, 1024)) > 0)
	{
		//받은 메시지 리스트에 출력
		CString strRecData = _T("");
		strRecData.Format(_T("[%s] : %s"), strRecIp, szBuffer);
		memcpy(szBuffer, strRecData, strRecData.GetLength() * sizeof(TCHAR));

		CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();
		pMain->HandleListMsgS(strRecData);

		//연결된 모든 클라이언트에 메시지 에코
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSoc;
		pServerSocket->BroadCast(szBuffer, strRecData.GetLength() * sizeof(TCHAR));
	}

	CSocket::OnReceive(nErrorCode);
}
