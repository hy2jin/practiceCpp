// MyUser.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ValueServer.h"
#include "MyUser.h"


// MyUser

MyUser::MyUser()
{
}

MyUser::~MyUser()
{
}


// MyUser ��� �Լ�


void MyUser::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	int value;
	Receive(&value, sizeof(int));

	AfxGetMainWnd()->SetDlgItemInt(IDC_VALUE_EDIT, value);

	CSocket::OnReceive(nErrorCode);
}
