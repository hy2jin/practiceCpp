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
	//�ش� child socket ����
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSoc;
	pServerSocket->CloseChildSocket(this);

	//listen socket
	pServerSocket->ShutDown();
	pServerSocket->Close();
	
	CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();
	pMain->HandleDisconnectS(2);
	pMain->OnBnClickedButtonOpenS();

	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	CString strRecIp = _T("");
	UINT uPortNumber = 0;
	GetPeerName(strRecIp, uPortNumber);

	int len = 0;
	if ((len = Receive(szBuffer, 1024)) > 0)
	{
		//���� �޽��� ����Ʈ�� ���
		CString strRecData = _T("");
		strRecData.Format(_T("[%s] : %s"), strRecIp, szBuffer);
		memcpy(szBuffer, strRecData, strRecData.GetLength() * sizeof(TCHAR));

		CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();
		pMain->HandleListMsgS(strRecData);

		//����� ��� Ŭ���̾�Ʈ�� �޽��� ����
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSoc;
		pServerSocket->BroadCast(szBuffer, strRecData.GetLength() * sizeof(TCHAR));
	}

	CSocket::OnReceive(nErrorCode);
}
