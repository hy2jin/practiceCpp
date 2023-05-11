// ListenSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatSDlg.h"
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

	CChildSocket* pChild = new CChildSocket();	//Ŭ���̾�Ʈ�� ������ ������ ���� ��ü ����

	BOOL check = Accept(*pChild);	//Ŭ���̾�Ʈ�� ������ ����ϰ� ������ ���ϰ� �����Ѵ�

	if (check == FALSE)
	{
		delete pChild;
		AfxMessageBox(_T("���� ��� ����"));
		return;
	}

	//CListenSocket ��ü�� �ּҸ� CChildSocket��ü�� �˷��ֱ� ���� �Լ��� ȣ��
	pChild->SetListenSocket(this);	//CChildSocket Ŭ������ ����ڰ� ������ �Լ�
	m_ptrChildSocketList.AddTail(pChild);
	//m_pClientSocket = pChild;	//��

	//Ŭ���̾�Ʈ�� �����ؿ��� ����Ʈ�� ���
	CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();

	pMain->m_List.AddString(_T("���� ���� ���"));
	pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

	CSocket::OnAccept(nErrorCode);
}

void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	POSITION pos;
	pos = m_ptrChildSocketList.Find(pChild);

	pChild->ShutDown();	//Ŭ���̾�Ʈ�� ����� ������ ������ ����
	pChild->Close();

	if (pos != NULL)
	{
		pChild->ShutDown();	//Ŭ���̾�Ʈ�� ����� ������ ������ ����
		pChild->Close();
	}

	m_ptrChildSocketList.RemoveAt(pos);	//����Ʈ���� �����ϰ�
	delete pChild;	//�޸𸮿��� ����
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