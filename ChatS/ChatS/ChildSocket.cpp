// ChildSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatSDlg.h"
#include "ChildSocket.h"
#include "ListenSocket.h"

#include "ChatS.h"

// CChildSocket

CChildSocket::CChildSocket()
{
}

CChildSocket::~CChildSocket()
{
}


// CChildSocket ��� �Լ�
void CChildSocket::SetListenSocket(CAsyncSocket* pSocket)
//����� Ŭ���̾�Ʈ�� �����ּҸ� m_ListSocket�� ����
{
	m_pListenSocket = pSocket;

	//Ŭ���̾�Ʈ�� �����ؿ��� ����Ʈ�� ���
	CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();
	CString strIPAddress = _T("");
	UINT uPortNumber = 0;
	GetPeerName(strIPAddress, uPortNumber);	//����� Ŭ���̾�Ʈ�� IP�ּҿ� ��Ʈ��ȣ �˾Ƴ���

	pMain->m_List.AddString(strIPAddress + _T(" ����"));
	pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
}



void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
	pServerSocket->ShutDown();
	pServerSocket->Close();

	CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();
	pMain->HandleCloseConnection(2);
	//Sleep(1000);
	pMain->HandleOpenConnection();

	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString strChat = _T("");
	CString strIPAddress = _T("");

	UINT uPortNumber = 0;

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	GetPeerName(strIPAddress, uPortNumber);	//����� Ŭ���̾�Ʈ�� IP�ּҿ� ��Ʈ��ȣ �˾Ƴ���

	//������ ������ �����ϱ�
	int len = 0;
	if ((len = Receive(szBuffer, 1024)) > 0)	//���������Ͱ� �ִ� ��쿡��
	{
		CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();	//������ ���������� ���� �޽����� ����Ʈ�� ���

		strChat.Format(_T("[%s] : %s"), strIPAddress, szBuffer);
		memcpy(szBuffer, strChat, strChat.GetLength() * sizeof(TCHAR));

		pMain->m_List.AddString(strChat);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() -1);

		//�ؿ���� ��� Ŭ���̾�Ʈ�� �ش� �޽��� ����
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->BroadCast(szBuffer, strChat.GetLength() * sizeof(TCHAR));
	}

	CSocket::OnReceive(nErrorCode);
}
