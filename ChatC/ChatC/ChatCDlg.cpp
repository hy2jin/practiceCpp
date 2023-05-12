
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
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EDIT_DATA, m_Edit);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_ButtonSend);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_ButtonConnect);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT, m_ButtonDisconnect);
}

BEGIN_MESSAGE_MAP(CChatCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CChatCDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatCDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CChatCDlg::OnBnClickedButtonDisconnect)
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
	SetDlgItemText(IDC_IPADDRESS1, _T("127.0.0.1"));	//루프백으로 초기화
	//SetDlgItemText(IDC_IPADDRESS1, _T("192.168.0.75"));
	SetDlgItemText(IDC_EDIT_PORT, _T("9000"));

	m_TryCount = 0;

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



void CChatCDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_IPADDRESS1, m_strIPAddress);
	GetDlgItemText(IDC_EDIT_PORT, m_strPort);

	if (m_Client.Create())	//클라이언트 소켓 생성
	{
		HandleConnect();
	}
	else
	{
		AfxMessageBox(_T("생성 실패"));
	}

}


void CChatCDlg::OnBnClickedButtonDisconnect()
{
	HandleDisconnect();
	m_TryCount = 0;
	HandleEditInputFlag(FALSE);
}

void CChatCDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	//사용자가 UI에서 입력한 메시지를 전송하여
	//해당 메시지가 제대로 송신되어 서버가 수신하면
	//에코형식으로 다시 재전송 받아 리스트에 출력한다.
	CString m_strData;
	GetDlgItemText(IDC_EDIT_DATA, m_strData);
	SetDlgItemText(IDC_EDIT_DATA, _T(""));

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	memcpy(szBuffer, m_strData, m_strData.GetLength() * sizeof(TCHAR));

	m_Client.Receive(szBuffer, 1024, 0x40);
	m_Client.Send((LPCTSTR)m_strData, m_strData.GetLength() * 2);
	//m_Client.Send(szBuffer, m_strData.GetLength() * 2);
	
	UpdateData(FALSE);
}

void CChatCDlg::HandleConnect()
{
	CString connectedMsg;
	//서버의 IP주소와 포트 번호를 설정하여 서버에 연결 시도
	if (m_Client.Connect(m_strIPAddress, _ttoi(m_strPort)))
	{
		connectedMsg.Format(_T("Try-%d : SUCCESS"), ++m_TryCount);
		HandleListMsg(connectedMsg);

		m_TryCount = 0;
		HandleEditInputFlag(TRUE);
	}
	else if (m_TryCount < 4)
	{
		connectedMsg.Format(_T("Try-%d : FAIL"), ++m_TryCount);
		HandleListMsg(connectedMsg);

		HandleConnect();
	}
	else
	{
		connectedMsg.Format(_T("%d회 실패! 안돼 돌아가"), ++m_TryCount);
		HandleListMsg(connectedMsg);

		OnBnClickedButtonDisconnect();
	}
}

void CChatCDlg::HandleDisconnect()
{
	m_Client.ShutDown();
	m_Client.Close();
}

void CChatCDlg::HandleEditInputFlag(BOOL flag)
{
	m_ButtonConnect.EnableWindow(!flag);

	m_ButtonSend.EnableWindow(flag);
	m_ButtonDisconnect.EnableWindow(flag);
	GetDlgItem(IDC_EDIT_DATA)->EnableWindow(flag);
}

void CChatCDlg::HandleListMsg(CString msg)
{
	m_List.AddString(msg);
	m_List.SetCurSel(m_List.GetCount() - 1);
}