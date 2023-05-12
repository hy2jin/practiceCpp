
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
	DDX_Control(pDX, IDC_LIST1, m_ListS);
	DDX_Control(pDX, IDC_BUTTON_OPEN_S, m_ButtonOpenS);
	DDX_Control(pDX, IDC_BUTTON_CLOSE_S, m_ButtonCloseS);
	DDX_Control(pDX, IDC_BUTTON_SEND_S, m_ButtonSendS);
}

BEGIN_MESSAGE_MAP(CChatSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_S, &CChatSDlg::OnBnClickedButtonOpenS)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_S, &CChatSDlg::OnBnClickedButtonCloseS)
	ON_BN_CLICKED(IDC_BUTTON_SEND_S, &CChatSDlg::OnBnClickedButtonSendS)
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


	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	HandleListMsgS(_T("STATUS : CLOSE"));
	SetDlgItemText(IDC_EDIT_PORT, m_strPortS);

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



void CChatSDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	HandleDisconnectS(0);
}


void CChatSDlg::OnBnClickedButtonOpenS()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_EDIT_PORT, m_strPortS);
	HandleConnectS();
}


void CChatSDlg::OnBnClickedButtonCloseS()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HandleDisconnectS(1);
	HandleEditFlagS(FALSE);

	HandleListMsgS(_T("STATUS : CLOSE"));
}


void CChatSDlg::OnBnClickedButtonSendS()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strData;
	GetDlgItemText(IDC_EDIT_DATA, m_strData);

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	int len = 0;
	if ((len = m_strData.GetLength()) > 0)
	{
		CString strChat = _T("");
		strChat.Format(_T("SERVER : %s"), m_strData);

		memcpy(szBuffer, strChat, strChat.GetLength() * sizeof(TCHAR));
		m_pListenSocket->BroadCast(szBuffer, strChat.GetLength() * sizeof(TCHAR));

		HandleListMsgS(strChat);

		SetDlgItemText(IDC_EDIT_DATA, _T(""));
	}
}


void CChatSDlg::HandleConnectS()
{
	m_pListenSocket = new CListenSocket;	//Listen ���� ����
	if (m_pListenSocket->Create(_ttoi(m_strPortS), SOCK_STREAM))
		//TCP ������ �����ϰ� 9000�� ��Ʈ���� ������
	{
		if (m_pListenSocket->Listen())
		{
			HandleEditFlagS(TRUE);

			CString temp;
			temp.Format(_T("STATUS : OPEN (%s/%s)"), m_strServerIpAddress, m_strPortS);
			HandleListMsgS(temp);

		}
		else
		{
			AfxMessageBox(_T("���� ����"));
		}
	}
	else
	{
		AfxMessageBox(_T("����"));
	}
}


void CChatSDlg::HandleDisconnectS(int flag)
{
	CString msg = _T("CLOSED BY SERVER");
	if (flag == 1) m_pListenSocket->Send(msg, msg.GetLength() * 2);
	else if (flag == 2) HandleListMsgS(_T("CLOSED BY CLIENT"));

	POSITION pos;
	pos = m_pListenSocket->m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;

	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_pListenSocket->m_ptrChildSocketList.GetNext(pos);

		if (pChild != NULL)
		{
			pChild->Send(msg, msg.GetLength() * 2);

			pChild->ShutDown();
			pChild->Close();
			delete pChild;
		}
	}

	m_pListenSocket->ShutDown();
	m_pListenSocket->Close();
}


void CChatSDlg::HandleEditFlagS(BOOL flag)
{
	m_ButtonOpenS.EnableWindow(!flag);
	m_ButtonCloseS.EnableWindow(flag);
	m_ButtonSendS.EnableWindow(flag);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(!flag);
	GetDlgItem(IDC_EDIT_DATA)->EnableWindow(flag);
}


void CChatSDlg::HandleListMsgS(CString msg)
{
	m_ListS.AddString(msg);
	m_ListS.SetCurSel(m_ListS.GetCount() - 1);
}