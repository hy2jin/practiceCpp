// ListenSocket.cpp : ���� �����Դϴ�.
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


// CListenSocket ��� �Լ�


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CChildSocket* pChild = new CChildSocket();

	BOOL check = Accept(*pChild);

	if (check == FALSE)
	{
		delete pChild;
		AfxMessageBox(_T("���� ��� ����"));
		return;
	}

	pChild->SetListenSocket(this);
	m_ptrChlidSocketList.AddTail(pChild);

	CSocket::OnAccept(nErrorCode);
}
