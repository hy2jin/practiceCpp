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