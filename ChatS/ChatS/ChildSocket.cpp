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
//����� Ŭ���̾�Ʈ�� �����ּҸ� m_ListSSocket�� ����
{
	m_pListenSoc = pSocket;

	//Ŭ���̾�Ʈ�� �����ؿ��� ����Ʈ�� ���
	CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();
	CString strIPAddress = _T("");
	UINT uPortNumber = 0;
	GetPeerName(strIPAddress, uPortNumber);	//����� Ŭ���̾�Ʈ�� IP�ּҿ� ��Ʈ��ȣ �˾Ƴ���

	pMain->HandleListMsgS(strIPAddress + _T(" ����"), FALSE);
	pMain->LogMsgServer(_T("ACCESS ") + strIPAddress);
}



void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSoc;
	pServerSocket->CloseChildSocket(this);
	pServerSocket->ShutDown();
	pServerSocket->Close();

	CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();
	pMain->HandleDisconnectS(2);
	pMain->OnBnClickedButtonOpenS();

	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CStringW strChat = _T("");
	CString strIPAddress = _T("");

	UINT uPortNumber = 0;

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	GetPeerName(strIPAddress, uPortNumber);	//����� Ŭ���̾�Ʈ�� IP�ּҿ� ��Ʈ��ȣ �˾Ƴ���

	//������ ������ �����ϱ�
	if (Receive(szBuffer, 1024) > 0)	//���������Ͱ� �ִ� ��쿡��
	{
		CChatSDlg* pMain = (CChatSDlg*)AfxGetMainWnd();	//������ ���������� ���� �޽����� ����Ʈ�� ���

		strChat.Format(_T("%s : %s"), strIPAddress, szBuffer);
		memcpy(szBuffer, strChat, strChat.GetLength() * sizeof(TCHAR));

		pMain->HandleListMsgS(strChat, FALSE);
		pMain->LogMsgServer(_T("RECEIVE ") + strChat);

		//�ؿ���� ��� Ŭ���̾�Ʈ�� �ش� �޽��� ����
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSoc;
		pServerSocket->BroadCast(szBuffer, strChat.GetLength() * sizeof(TCHAR));
	}

	CSocket::OnReceive(nErrorCode);
}
