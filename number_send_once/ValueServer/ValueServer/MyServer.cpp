// MyServer.cpp : ���� �����Դϴ�.
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


// MyServer ��� �Լ�
void MyServer::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	Accept(m_user);

	CSocket::OnAccept(nErrorCode);
}
