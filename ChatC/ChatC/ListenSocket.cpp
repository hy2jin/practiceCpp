// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatCDlg.h"
#include "ListenSocket.h"
#include "ChildSocket.h"


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
	CChildSocket* pChild = new CChildSocket();

	BOOL check = Accept(*pChild);

	if (check == FALSE)
	{
		delete pChild;
		AfxMessageBox(_T("접속 허용 실패"));
		return;
	}

	pChild->SetListenSocket(this);
	m_ptrChildSocketList.AddTail(pChild);

	CSocket::OnAccept(nErrorCode);
}

void CListenSocket::BroadCast(char* pszBuffer, int len)
{
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;

	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos);
		if (pChild != NULL) pChild->Send(pszBuffer, len * 2);
	}
}

void CListenSocket::CloseChildSocket(CSocket* pChild)
{
	POSITION pos;
	pos = m_ptrChildSocketList.Find(pChild);

	if (pos != NULL)
	{
		pChild->ShutDown();
		pChild->Close();
	}
	m_ptrChildSocketList.RemoveAt(pos);
	delete pChild;
}