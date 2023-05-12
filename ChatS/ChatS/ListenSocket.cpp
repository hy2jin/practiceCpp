// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatSDlg.h"
#include "ListenSocket.h"
#include "ChildSocket.h"

#include "ChatS.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수
void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CChildSocket* pChild = new CChildSocket();	//클라이언트와 연결할 데이터 소켓 객체 생성

	BOOL check = Accept(*pChild);	//클라이언트의 접속을 허용하고 데이터 소켓과 연결한다

	if (check == FALSE)
	{
		delete pChild;
		AfxMessageBox(_T("접속 허용 실패"));
		return;
	}

	//CListenSocket 객체의 주소를 CChildSocket객체에 알려주기 위한 함수를 호출
	pChild->SetListenSocket(this);	//CChildSocket 클래스에 사용자가 정의한 함수
	m_ptrChildSocketList.AddTail(pChild);

	CSocket::OnAccept(nErrorCode);
}

void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	POSITION pos;
	pos = m_ptrChildSocketList.Find(pChild);

	if (pos != NULL)
	{
		pChild->ShutDown();	//클라이언트와 연결된 데이터 소켓을 닫음
		pChild->Close();
	}

	m_ptrChildSocketList.RemoveAt(pos);	//리스트에서 제거하고
	delete pChild;	//메모리에서 해제

	//CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();
	//pMain->HandleCloseConnection(2);
	//Sleep(1000);
	//pMain->HandleOpenConnection();
}

void CListenSocket::BroadCast(char* pszBuffer, int len)
{
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;

	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos);

		if (pChild != NULL) pChild->Send(pszBuffer, len*2);
	}
}