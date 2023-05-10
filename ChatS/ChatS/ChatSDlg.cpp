
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
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_ButtonOpen);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_ButtonClose);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_ButtonSend);
}

BEGIN_MESSAGE_MAP(CChatSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CChatSDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CChatSDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatSDlg::OnBnClickedButtonSend)
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

	// ☆★TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_List.AddString(_T("STATUS : CLOSE"));
	m_List.SetCurSel(m_List.GetCount() - 1);

	m_strPort = _T("9000");
	SetDlgItemText(IDC_EDIT_PORT, m_strPort);

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



void CChatSDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	POSITION pos;
	pos = m_pListenSocket->m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;

	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_pListenSocket->m_ptrChildSocketList.GetNext(pos);

		if (pChild != NULL)
		{
			pChild->ShutDown();
			pChild->Close();
			delete pChild;
		}
	}

	m_pListenSocket->ShutDown();
	m_pListenSocket->Close();
}


void CChatSDlg::OnBnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pListenSocket = new CListenSocket;	//Listen 소켓 생성

	if (m_pListenSocket->Create(_ttoi(m_strPort), SOCK_STREAM))
		//TCP 소켓을 생성하고 9000번 포트에서 연결대기
	{
		if (m_pListenSocket->Listen())
		{
			m_ButtonOpen.EnableWindow(FALSE);
			m_ButtonClose.EnableWindow(TRUE);
			m_ButtonSend.EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DATA)->EnableWindow(TRUE);

			CString temp;
			temp.Format(_T("STATUS : OPEN (%s/%s)"), m_strIpAddress, m_strPort);
			m_List.AddString(temp);
			m_List.SetCurSel(m_List.GetCount() - 1);
		}
		else
		{
			AfxMessageBox(_T("연결 실패"));
		}
	}
	else
	{
		AfxMessageBox(_T("실패"));
	}
}


void CChatSDlg::OnBnClickedButtonClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pListenSocket->ShutDown();
	m_pListenSocket->Close();

	m_ButtonOpen.EnableWindow(TRUE);
	m_ButtonClose.EnableWindow(FALSE);
	m_ButtonSend.EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DATA)->EnableWindow(FALSE);

	m_List.AddString(_T("STATUS : CLOSE"));
	m_List.SetCurSel(m_List.GetCount() - 1);
}



void CChatSDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}
