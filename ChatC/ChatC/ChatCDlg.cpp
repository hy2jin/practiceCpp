
// ChatCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ChatC.h"
#include "ChatCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CChatCDlg 대화 상자



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


// CChatCDlg 메시지 처리기

BOOL CChatCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_IPADDRESS_C, _T("127.0.0.1"));	//루프백으로 초기화
	//SetDlgItemText(IDC_IPADDRESS_C, _T("192.168.0.75"));
	SetDlgItemText(IDC_EDIT_PORT_C, _T("9000"));
	m_TryCount = 0;

	HandleListMsgS(_T("STATUS : CLOSED"));
	SetDlgItemText(IDC_EDIT_PORT_S, m_strPortS);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatCDlg::OnBnClickedButtonConnectC()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_IPADDRESS_C, m_strIpC);
	GetDlgItemText(IDC_EDIT_PORT_C, m_strPortC);

	if (m_ClientSoc.Create())	//클라이언트 소켓 생성
	{
		HandleConnectC();
	}
	else
	{
		AfxMessageBox(_T("생성 실패"));
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	//사용자가 UI에서 입력한 메시지를 전송하여
	//해당 메시지가 제대로 송신되어 서버가 수신하면
	//에코형식으로 다시 재전송 받아 리스트에 출력한다.
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
	//서버의 IP주소와 포트 번호를 설정하여 서버에 연결 시도
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
		connectedMsg.Format(_T("%d회 실패! 안돼 돌아가"), ++m_TryCount);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		else HandleListMsgS(_T("연결 실패"));
	}
	else HandleListMsgS(_T("실패"));
}


void CChatCDlg::OnBnClickedButtonCloseS()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CChatCDlg::OnBnClickedButtonSendS()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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