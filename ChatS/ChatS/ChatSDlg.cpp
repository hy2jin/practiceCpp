
// ChatSDlg.cpp : 구현 파일
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


// CChatSDlg 대화 상자



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


// CChatSDlg 메시지 처리기

BOOL CChatSDlg::OnInitDialog()
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

	ReadIniFile();
	HandleCreateLogFolder();

	//SERVER
	HandleListMsgS(_T("STATE: CLOSED"));
	if (!m_strIpS.GetLength()) m_strIpS = _T("127.0.0.1");
	if (!m_strPortS.GetLength()) m_strPortS = _T("1000");
	SetDlgItemText(IDC_EDIT_PORT_S, m_strPortS);

	//CLIENT
	if (!m_strIpC.GetLength()) m_strIpC = _T("127.0.0.1");
	if (!m_strPortC.GetLength()) m_strPortC = _T("1000");
	SetDlgItemText(IDC_IPADDRESS_C, m_strIpC);
	SetDlgItemText(IDC_EDIT_PORT_C, m_strPortC);
	m_TryCount = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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
		CreateIniFile();
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatSDlg::OnPaint()
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
HCURSOR CChatSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatSDlg::CreateIniFile()
{

	CString strFilePath = HandleGetThisPath() + _T("SETTINGFILE.ini");
	
	
	CString strSection, strKey;
	
	CFile file(strFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Close();

	strSection = _T("SERVER_INFO");
	strKey = _T("IP_ADDRESS");
	WritePrivateProfileString(strSection, strKey, m_strIpS, strFilePath);
	strKey = _T("PORT");
	WritePrivateProfileString(strSection, strKey, m_strPortS, strFilePath);

	strSection = _T("CLIENT_INFO");
	strKey = _T("IP_ADDRESS");
	WritePrivateProfileString(strSection, strKey, m_strIpC, strFilePath);
	strKey = _T("PORT");
	WritePrivateProfileString(strSection, strKey, m_strPortC, strFilePath);
}


void CChatSDlg::ReadIniFile()
{
	CString strFilePath = HandleGetThisPath() + _T("SETTINGFILE.ini");
	TCHAR inBuffer[100];

	CString strSection = _T("SERVER_INFO");
	GetPrivateProfileString(strSection, _T("IP_ADDRESS"), _T("127.0.0.1"), inBuffer, 100, strFilePath);
	m_strIpS.Format(_T("%s"), inBuffer);

	GetPrivateProfileString(strSection, _T("PORT"), _T("1000"), inBuffer, 100, strFilePath);
	m_strPortS.Format(_T("%s"), inBuffer);

	strSection = _T("CLIENT_INFO");
	GetPrivateProfileString(strSection, _T("IP_ADDRESS"), _T("127.0.0.1"), inBuffer, 100, strFilePath);
	m_strIpC.Format(_T("%s"), inBuffer);

	GetPrivateProfileString(strSection, _T("PORT"), _T("1000"), inBuffer, 100, strFilePath);
	m_strPortC.Format(_T("%s"), inBuffer);

}


void CChatSDlg::OnBnClickedButtonOpenS()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT_PORT_S, m_strPortS);

	m_pListenSoc = new CListenSocket;	//Listen 소켓 생성
	if (m_pListenSoc->Create(_ttoi(m_strPortS), SOCK_STREAM))	//TCP 소켓을 생성하고 포트에서 연결대기
	{
		if (m_pListenSoc->Listen())
		{
			HandleEditFlagS(TRUE);

			CString temp;
			temp.Format(_T("STATE: OPEN (%s/%s)"), m_strIpS, m_strPortS);
			HandleListMsgS(temp);
		}
		else HandleListMsgS(_T("연결 실패"));
	}
	else HandleListMsgS(_T("실패"));
}


void CChatSDlg::OnBnClickedButtonCloseS()
{
	HandleDisconnectS(1);
	HandleEditFlagS(FALSE);

	HandleListMsgS(_T("STATE: CLOSE"));
}


void CChatSDlg::OnBnClickedButtonSendS()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

		HandleListMsgS(strChat, FALSE);
		LogMsgServer(_T("SEND ") + m_strData);
	}
}


void CChatSDlg::HandleDisconnectS(int flag)	//0: 출력없음, 1: 서버가 닫음, 2: 클라이언트가 닫음
{
	CString msg = _T("CLOSED BY SERVER");

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

	if (flag == 1) {
		m_pListenSoc->Send(msg, msg.GetLength() * 2);
	}
	else if (flag == 2)
	{
		HandleListMsgS(_T("CLOSED BY CLIENT"));
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


void CChatSDlg::HandleListMsgS(CString msg, BOOL isLog)
{
	m_ListS.AddString(msg);
	m_ListS.SetCurSel(m_ListS.GetCount() - 1);

	if (isLog)
	{
		LogMsgServer(msg);
	}
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
		HandleListMsgC(_T("생성 실패"));
	}
}


void CChatSDlg::HandleConnectC()
{
	CString connectedMsg;
	
	if (m_ClientSoc.Connect(m_strIpC, _ttoi(m_strPortC)))
	{	//성공
		connectedMsg.Format(_T("Try-%d : SUCCESS"), ++m_TryCount);
		HandleListMsgC(connectedMsg);

		HandleEditFlagC(TRUE);
		m_TryCount = 0;
	}
	else if (m_TryCount < 2)
	{	//실패했지만 다시 시도
		connectedMsg.Format(_T("Try-%d : FAIL"), ++m_TryCount);
		HandleListMsgC(connectedMsg);

		HandleConnectC();
	}
	else
	{	//마지막 시도 실패(3회차)
		connectedMsg.Format(_T("Try-%d : FAIL"), ++m_TryCount);
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


void CChatSDlg::HandleListMsgC(CString msg, BOOL isLog)
{
	m_ListC.AddString(msg);
	m_ListC.SetCurSel(m_ListC.GetCount() - 1);

	if (isLog)
	{
		LogMsgClient(msg);
	}
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