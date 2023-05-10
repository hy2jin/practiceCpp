// ChildSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatSDlg.h"
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
//연결된 클라이언트의 소켓주소를 m_ListSocket에 저장
{
	m_pListenSocket = pSocket;
}



void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);

	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString temp = _T("");
	CString strIPAddress = _T("");

	UINT uPortNumber = 0;

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	GetPeerName(strIPAddress, uPortNumber);	//연결된 클라이언트의 IP주소와 포트번호 알아내기

	//실제로 데이터 수신하기
	int len = 0;
	if ((len = Receive(szBuffer, 1024)) > 0)	//받은데이터가 있는 경우에만
	{
		CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();	//데이터 수신했으면 받은 메시지를 리스트에 출력

		temp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);

		pMain->m_List.AddString(temp);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() -1);

		//연결된 모든 클라이언트에 해당 메시지 에코
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->BroadCast(szBuffer, len);
	}

	CSocket::OnReceive(nErrorCode);
}
