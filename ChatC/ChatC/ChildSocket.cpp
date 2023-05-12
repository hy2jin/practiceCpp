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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	CString strRecData = _T("");
	CString strRecIp = _T("");
	UINT uPortNumber = 0;

	GetPeerName(strRecIp, uPortNumber);

	int len = 0;
	if ((len = Receive(szBuffer, 1024)) > 0)
	{
		CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();

		strRecData.Format(_T("[%s] : %s"), strRecIp, szBuffer);
		memcpy(szBuffer, strRecData, strRecData.GetLength() * sizeof(TCHAR));

		pMain->HandleListMsgS(strRecData);

		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSoc;
		//※TODO : BroadCast 만들기!
	}

	CSocket::OnReceive(nErrorCode);
}
