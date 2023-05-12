
// ChatCDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ChatC.h"
#include "ChatCDlg.h"
#include "afxdialogex.h"

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


// CChatCDlg ��ȭ ����



CChatCDlg::CChatCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_C, m_ListC);
	DDX_Control(pDX, IDC_BUTTON_SEND_C, m_ButtonSendC);
	DDX_Control(pDX, IDC_BUTTON_CONNECT_C, m_ButtonConnectC);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT_C, m_ButtonDisconnectC);
	DDX_Control(pDX, IDC_LIST_S, m_ListS);
	DDX_Control(pDX, IDC_BUTTON_SEND_S, m_ButtonSendS);
	DDX_Control(pDX, IDC_BUTTON_OPEN_S, m_ButtonOpenS);
	DDX_Control(pDX, IDC_BUTTON_CLOSE_S, m_ButtonCloseS);
}

BEGIN_MESSAGE_MAP(CChatCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_C, &CChatCDlg::OnBnClickedButtonConnectC)
	ON_BN_CLICKED(IDC_BUTTON_SEND_C, &CChatCDlg::OnBnClickedButtonSendC)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_C, &CChatCDlg::OnBnClickedButtonDisconnectC)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_S, &CChatCDlg::OnBnClickedButtonOpenS)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_S, &CChatCDlg::OnBnClickedButtonCloseS)
	ON_BN_CLICKED(IDC_BUTTON_SEND_S, &CChatCDlg::OnBnClickedButtonSendS)
END_MESSAGE_MAP()


// CChatCDlg �޽��� ó����

BOOL CChatCDlg::OnInitDialog()
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

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetDlgItemText(IDC_IPADDRESS_C, _T("127.0.0.1"));	//���������� �ʱ�ȭ
	//SetDlgItemText(IDC_IPADDRESS_C, _T("192.168.0.75"));
	SetDlgItemText(IDC_EDIT_PORT_C, _T("9000"));
	m_TryCount = 0;

	HandleListMsgS(_T("STATUS : CLOSED"));
	SetDlgItemText(IDC_EDIT_PORT_S, m_strPortS);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CChatCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatCDlg::OnPaint()
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
HCURSOR CChatCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatCDlg::OnBnClickedButtonConnectC()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_IPADDRESS_C, m_strIpC);
	GetDlgItemText(IDC_EDIT_PORT_C, m_strPortC);

	if (m_ClientSoc.Create())	//Ŭ���̾�Ʈ ���� ����
	{
		HandleConnectC();
	}
	else
	{
		AfxMessageBox(_T("���� ����"));
	}

}


void CChatCDlg::OnBnClickedButtonDisconnectC()
{
	HandleDisconnectC();
	m_TryCount = 0;
	HandleEditFlagC(FALSE);
}


void CChatCDlg::OnBnClickedButtonSendC()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	//����ڰ� UI���� �Է��� �޽����� �����Ͽ�
	//�ش� �޽����� ����� �۽ŵǾ� ������ �����ϸ�
	//������������ �ٽ� ������ �޾� ����Ʈ�� ����Ѵ�.
	CString m_strData;
	GetDlgItemText(IDC_EDIT_C, m_strData);
	SetDlgItemText(IDC_EDIT_C, _T(""));

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	memcpy(szBuffer, m_strData, m_strData.GetLength() * sizeof(TCHAR));

	m_ClientSoc.Receive(szBuffer, 1024, 0x40);
	m_ClientSoc.Send((LPCTSTR)m_strData, m_strData.GetLength() * 2);
	//m_ClientSoc.Send(szBuffer, m_strData.GetLength() * 2);
	
	UpdateData(FALSE);
}


void CChatCDlg::HandleConnectC()
{
	CString connectedMsg;
	//������ IP�ּҿ� ��Ʈ ��ȣ�� �����Ͽ� ������ ���� �õ�
	if (m_ClientSoc.Connect(m_strIpC, _ttoi(m_strPortC)))
	{
		connectedMsg.Format(_T("Try-%d : SUCCESS"), ++m_TryCount);
		HandleListMsgC(connectedMsg);

		m_TryCount = 0;
		HandleEditFlagC(TRUE);
	}
	else if (m_TryCount < 4)
	{
		connectedMsg.Format(_T("Try-%d : FAIL"), ++m_TryCount);
		HandleListMsgC(connectedMsg);

		HandleConnectC();
	}
	else
	{
		connectedMsg.Format(_T("%dȸ ����! �ȵ� ���ư�"), ++m_TryCount);
		HandleListMsgC(connectedMsg);

		OnBnClickedButtonDisconnectC();
	}
}


void CChatCDlg::HandleDisconnectC()
{
	m_ClientSoc.ShutDown();
	m_ClientSoc.Close();
}


void CChatCDlg::HandleEditFlagC(BOOL flag)
{
	GetDlgItem(IDC_EDIT_C)->EnableWindow(flag);
	m_ButtonSendC.EnableWindow(flag);
	m_ButtonDisconnectC.EnableWindow(flag);

	m_ButtonConnectC.EnableWindow(!flag);
	GetDlgItem(IDC_IPADDRESS_C)->EnableWindow(!flag);
	GetDlgItem(IDC_EDIT_PORT_C)->EnableWindow(!flag);
}


void CChatCDlg::HandleListMsgC(CString msg)
{
	m_ListC.AddString(msg);
	m_ListC.SetCurSel(m_ListC.GetCount() - 1);
}



void CChatCDlg::OnBnClickedButtonOpenS()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_EDIT_PORT_S, m_strPortS);

	m_pListenSoc = new CListenSocket;
	if (m_pListenSoc->Create(_ttoi(m_strPortS), SOCK_STREAM))
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


void CChatCDlg::OnBnClickedButtonCloseS()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CChatCDlg::OnBnClickedButtonSendS()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CChatCDlg::HandleListMsgS(CString msg)
{
	m_ListS.AddString(msg);
	m_ListS.SetCurSel(m_ListS.GetCount() - 1);
}

void CChatCDlg::HandleEditFlagS(BOOL flag)
{
	GetDlgItem(IDC_EDIT_C)->EnableWindow(flag);
	m_ButtonSendS.EnableWindow(flag);
	m_ButtonCloseS.EnableWindow(flag);

	m_ButtonOpenS.EnableWindow(!flag);
	GetDlgItem(IDC_EDIT_PORT_S)->EnableWindow(!flag);
}