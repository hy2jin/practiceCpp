// MyServer.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ValueServer.h"
#include "MyServer.h"


// MyServer

MyServer::MyServer()
{
}

MyServer::~MyServer()
{
}


// MyServer 멤버 함수
void MyServer::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Accept(m_user);

	CSocket::OnAccept(nErrorCode);
}
