// ClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatCDlg.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��� �Լ�


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	if (Receive(szBuffer, 1024) > 0)
	//���� Ŭ���̾�Ʈ ������ �̿��� �����͸� �޾Ƽ�
	{
		CChatCDlg* pMain = (CChatCDlg*)AfxGetMainWnd();	//���� �����͸� ����Ѵ�.
		CString receivedMsg = LPCTSTR(szBuffer);
		pMain->m_List.AddString(receivedMsg);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

		if (receivedMsg == "CLOSED BY SERVER")
		{
			pMain->OnBnClickedButtonDisconnect();
		}
	}

	CSocket::OnReceive(nErrorCode);
}
