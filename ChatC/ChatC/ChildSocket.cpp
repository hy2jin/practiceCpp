// ChildSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatCDlg.h"
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
{
	m_pListenSoc = pSocket;

	//Ŭ���̾�Ʈ�� �����ؿ��� ����Ʈ�� ���
	CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();
	CString strIPAddress = _T("");
	UINT uPortNumber = 0;
	GetPeerName(strIPAddress, uPortNumber);

	pMain->HandleListMsgS(strIPAddress + _T(" ����"));
}

void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	CString strRecData = _T("");
	CString strRecIp = _T("");
	UINT uPortNumber = 0;

	GetPeerName(strRecIp, uPortNumber);

	int len = 0;
	if ((len = Receive(szBuffer, 1024)) > 0)
	{
		CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();

		strRecData.Format(_T("[%s] : %s"), strRecIp, szBuffer);
		memcpy(szBuffer, strRecData, strRecData.GetLength() * sizeof(TCHAR));

		pMain->HandleListMsgS(strRecData);

		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSoc;
		//��TODO : BroadCast �����!
	}

	CSocket::OnReceive(nErrorCode);
}
