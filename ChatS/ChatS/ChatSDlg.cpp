
// ChatSDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ChatS.h"
#include "ChatSDlg.h"
#include "afxdialogex.h"

#include "ListenSocket.h"
#include "ChildSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatSDlg ��ȭ ����



CChatSDlg::CChatSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatSDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_S, m_ListS);
	DDX_Control(pDX, IDC_BUTTON_OPEN_S, m_ButtonOpenS);
	DDX_Control(pDX, IDC_BUTTON_CLOSE_S, m_ButtonCloseS);
	DDX_Control(pDX, IDC_BUTTON_SEND_S, m_ButtonSendS);
	DDX_Control(pDX, IDC_LIST_C, m_ListC);
	DDX_Control(pDX, IDC_BUTTON_SEND_C, m_ButtonSendC);
	DDX_Control(pDX, IDC_BUTTON_CONNECT_C, m_ButtonConnectC);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT_C, m_ButtonDisconnectC);
}

BEGIN_MESSAGE_MAP(CChatSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_S, &CChatSDlg::OnBnClickedButtonOpenS)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_S, &CChatSDlg::OnBnClickedButtonCloseS)
	ON_BN_CLICKED(IDC_BUTTON_SEND_S, &CChatSDlg::OnBnClickedButtonSendS)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_C, &CChatSDlg::OnBnClickedButtonConnectC)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_C, &CChatSDlg::OnBnClickedButtonDisconnectC)
	ON_BN_CLICKED(IDC_BUTTON_SEND_C, &CChatSDlg::OnBnClickedButtonSendC)
END_MESSAGE_MAP()


// CChatSDlg �޽��� ó����

BOOL CChatSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.


	//SERVER
	HandleListMsgS(_T("STATUS : CLOSED"));
	SetDlgItemText(IDC_EDIT_PORT_S, m_strPortS);

	//CLIENT
	SetDlgItemText(IDC_IPADDRESS_C, _T("127.0.0.1"));
	SetDlgItemText(IDC_EDIT_PORT_C, _T("8000"));
	m_TryCount = 0;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CChatSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CChatSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CChatSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatSDlg::OnBnClickedButtonOpenS()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_EDIT_PORT_S, m_strPortS);

	m_pListenSoc = new CListenSocket;	//Listen ���� ����
	if (m_pListenSoc->Create(_ttoi(m_strPortS), SOCK_STREAM))	//TCP ������ �����ϰ� ��Ʈ���� ������
	{
		if (m_pListenSoc->Listen())
		{
			HandleEditFlagS(TRUE);

			CString temp;
			temp.Format(_T("STATUS : OPEN (%s/%s)"), m_strIpS, m_strPortS);
			HandleListMsgS(temp);
		}
		else HandleListMsgS(_T("���� ����"));
	}
	else HandleListMsgS(_T("����"));
}


void CChatSDlg::OnBnClickedButtonCloseS()
{
	HandleDisconnectS(1);
	HandleEditFlagS(FALSE);

	HandleListMsgS(_T("STATUS : CLOSE"));
}


void CChatSDlg::OnBnClickedButtonSendS()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strData;
	GetDlgItemText(IDC_EDIT_S, m_strData);

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	int len = 0;
	if ((len = m_strData.GetLength()) > 0)
	{
		SetDlgItemText(IDC_EDIT_S, _T(""));

		CString strChat = _T("");
		strChat.Format(_T("SERVER : %s"), m_strData);

		memcpy(szBuffer, strChat, strChat.GetLength() * sizeof(TCHAR));
		m_pListenSoc->BroadCast(szBuffer, strChat.GetLength() * sizeof(TCHAR));

		HandleListMsgS(strChat);

	}
}


void CChatSDlg::HandleDisconnectS(int flag)
{
	CString msg = _T("CLOSED BY SERVER");

	if (flag == 1) {
		m_pListenSoc->Send(msg, msg.GetLength() * 2);
	}
	else if (flag == 2)
	{
		HandleListMsgS(_T("CLOSED BY CLIENT"));
	}

	POSITION pos;
	pos = m_pListenSoc->m_ptrChildSocketList.GetHeadPosition();

	CChildSocket* pChild = NULL;
	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_pListenSoc->m_ptrChildSocketList.GetNext(pos);

		if (pChild != NULL)
		{
			pChild->Send(msg, msg.GetLength() * 2);

			pChild->ShutDown();
			pChild->Close();
			delete pChild;
		}
	}

	m_pListenSoc->ShutDown();
	m_pListenSoc->Close();
}


void CChatSDlg::HandleEditFlagS(BOOL flag)
{
	GetDlgItem(IDC_EDIT_S)->EnableWindow(flag);
	m_ButtonSendS.EnableWindow(flag);
	m_ButtonCloseS.EnableWindow(flag);

	m_ButtonOpenS.EnableWindow(!flag);
	GetDlgItem(IDC_EDIT_PORT_S)->EnableWindow(!flag);
}


void CChatSDlg::HandleListMsgS(CString msg)
{
	m_ListS.AddString(msg);
	m_ListS.SetCurSel(m_ListS.GetCount() - 1);
}

///////////////////////////////////////////////////////////

void CChatSDlg::OnBnClickedButtonConnectC()
{
	GetDlgItemText(IDC_IPADDRESS_C, m_strIpC);
	GetDlgItemText(IDC_EDIT_PORT_C, m_strPortC);

	if (m_ClientSoc.Create())
	{
		HandleConnectC();
	}
	else
	{
		HandleListMsgC(_T("���� ����"));
	}
}


void CChatSDlg::HandleConnectC()
{
	CString connectedMsg;
	
	if (m_ClientSoc.Connect(m_strIpC, _ttoi(m_strPortC)))
	{	//����
		connectedMsg.Format(_T("Try-%d : SUCCESS"), ++m_TryCount);
		HandleListMsgC(connectedMsg);

		HandleEditFlagC(TRUE);
		m_TryCount = 0;
	}
	else if (m_TryCount < 2)
	{	//���������� �ٽ� �õ�
		connectedMsg.Format(_T("Try-%d : FAIL"), ++m_TryCount);
		HandleListMsgC(connectedMsg);

		HandleConnectC();
	}
	else
	{	//������ �õ� ����(3ȸ��)
		connectedMsg.Format(_T("%dȸ ����! �ٽ� �����ϼ���"), ++m_TryCount);
		HandleListMsgC(connectedMsg);

		OnBnClickedButtonDisconnectC();
	}
}


void CChatSDlg::OnBnClickedButtonDisconnectC()
{
	HandleDisconnectC();
	m_TryCount = 0;
	HandleEditFlagC(FALSE);
}


void CChatSDlg::HandleDisconnectC()
{
	m_ClientSoc.ShutDown();
	m_ClientSoc.Close();
}


void CChatSDlg::OnBnClickedButtonSendC()
{
	UpdateData(TRUE);

	CString m_strData;
	GetDlgItemText(IDC_EDIT_C, m_strData);
	SetDlgItemText(IDC_EDIT_C, _T(""));

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	memcpy(szBuffer, m_strData, m_strData.GetLength() * sizeof(TCHAR));

	m_ClientSoc.Receive(szBuffer, 1024, 0x40);
	m_ClientSoc.Send((LPCTSTR)m_strData, m_strData.GetLength() * 2);

	UpdateData(FALSE);
}


void CChatSDlg::HandleListMsgC(CString msg)
{
	m_ListC.AddString(msg);
	m_ListC.SetCurSel(m_ListC.GetCount() - 1);
}


void CChatSDlg::HandleEditFlagC(BOOL flag)
{
	GetDlgItem(IDC_EDIT_C)->EnableWindow(flag);
	m_ButtonSendC.EnableWindow(flag);
	m_ButtonDisconnectC.EnableWindow(flag);

	m_ButtonConnectC.EnableWindow(!flag);
	GetDlgItem(IDC_IPADDRESS_C)->EnableWindow(!flag);
	GetDlgItem(IDC_EDIT_PORT_C)->EnableWindow(!flag);
}