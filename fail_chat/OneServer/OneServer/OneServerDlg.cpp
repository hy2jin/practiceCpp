
// OneServerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "OneServer.h"
#include "OneServerDlg.h"
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


// COneServerDlg 대화 상자



COneServerDlg::COneServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COneServerDlg::IDD, pParent)
	, m_strSend(_T(""))
	, m_strStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COneServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON_SEND, m_strSend);
	DDX_Control(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_strStatus);
}

BEGIN_MESSAGE_MAP(COneServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_MESSAGE(UM_ACCEPT, OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &COneServerDlg::OnClickedButtonSend)
END_MESSAGE_MAP()


// COneServerDlg 메시지 처리기

BOOL COneServerDlg::OnInitDialog()
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
	m_socCom = NULL;
	m_socServer.Create(50000);
	m_socServer.Listen();
	m_socServer.Init(this->m_hWnd);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COneServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COneServerDlg::OnPaint()
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
HCURSOR COneServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LPARAM COneServerDlg::OnAccept(UINT wParam, LPARAM lParam) {
	// 클라이언트에서 접속 요청이 왔을 때
	m_strStatus = "접속성공";

	// 통신용 소켓을 생선한 뒤
	m_socCom = new CSocCom;
	// 서버소켓과 통신소켓을 연결한다.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);

	m_socCom->Send("접속성공", 256);    // 소켓이 연결되었다는 것을 클라이언트에 알리기 위해 Send 함수로“접속성공”이라는 문자열을 보냄

	UpdateData(FALSE);
	return TRUE;
}

LPARAM COneServerDlg::OnReceive(UINT wParam, LPARAM lParam) {
	// 접속된 곳에서 데이터가 도착했을 때
	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);

	// 데이터를 pTmp에 받는다.
	m_socCom->Receive(pTmp, 256);
	strTmp.Format("%s", pTmp);

	// 리스트박스에 보여준다.
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
	return TRUE;
}

void COneServerDlg::OnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	char pTmp[256];
	CString strTmp;

	// pTmp에 전송할 데이터 입력
	memset(pTmp, '\0', 256);
	strcpy_s(pTmp, m_strSend);
	m_strSend = "";

	// 전송
	m_socCom->Send(pTmp, 256);

	// 전송한 데이터도 리스트박스에 보여준다.
	strTmp.Format("%s", pTmp);
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);

	UpdateData(FALSE);
}
