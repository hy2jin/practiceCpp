// ListenSocket.cpp : 구현 파일입니다.
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


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CClientSocket* pClient = new CClientSocket();	//서버와 연결할 데이터 소켓 객체 생성
	BOOL check = Accept(*pClient);

	if (check == FALSE)
	{
		delete pClient;
		AfxMessageBox(_T("FAIL"));
	}

	CSocket::OnAccept(nErrorCode);
}
