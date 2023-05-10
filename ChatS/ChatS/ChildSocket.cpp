// ChildSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatSDlg.h"
#include "ChildSocket.h"
#include "ListenSocket.h"


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
}



void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);

	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString temp = _T("");
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

		temp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);

		pMain->m_List.AddString(temp);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() -1);

		//����� ��� Ŭ���̾�Ʈ�� �ش� �޽��� ����
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->BroadCast(szBuffer, len);
	}

	CSocket::OnReceive(nErrorCode);
}
