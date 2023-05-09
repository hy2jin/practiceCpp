
// ExamServerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ExamServer.h"
#include "ExamServerDlg.h"
#include "afxdialogex.h"

#include <Winsock2.h>
#include <Ws2tcpip.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS


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


// CExamServerDlg 대화 상자



CExamServerDlg::CExamServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExamServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTV_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CExamServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(25001, &CExamServerDlg::On25001)
	ON_WM_DESTROY()
	ON_MESSAGE(25002, &CExamServerDlg::On25002)
END_MESSAGE_MAP()


// CExamServerDlg 메시지 처리기

BOOL CExamServerDlg::OnInitDialog()
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
	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);		// Address Family, SOCK-STREAM : TCP방식, 0: 2번째 인자를 따라감
	sockaddr_in srv_addr;
	srv_addr.sin_family = AF_INET;
	// srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// char ip4[INET_ADDRSTRLEN];
	inet_pton(AF_INET, "1270.0.01", &(srv_addr.sin_addr));
	srv_addr.sin_port = htons(18000);
	bind(mh_listen_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));

	AddEventString("서비스를 시작합니다 :)");
	listen(mh_listen_socket, 1);
	// WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);
	WSAEventSelect(mh_listen_socket, m_hWnd, FD_ACCEPT);
	// h_socket에 FD_ACCEPT메시지가 발생하면 m_hWnd에 25001번 요청함. 응답없음에 빠지지 않기 위해

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CExamServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExamServerDlg::OnPaint()
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
HCURSOR CExamServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExamServerDlg::AddEventString(const char *ap_string)
{
	while (m_event_list.GetCount() > 20) {
		m_event_list.DeleteString(0);
	}

	int index = m_event_list.InsertString(-1, CString(ap_string));
	m_event_list.SetCurSel(index);
}

afx_msg LRESULT CExamServerDlg::On25001(WPARAM wParam, LPARAM lParam)
{
	sockaddr_in client_addr;
	int sockaddr_in_size = sizeof(sockaddr_in);
	SOCKET h_socket = accept(mh_listen_socket, (LPSOCKADDR)&client_addr, &sockaddr_in_size);

	int i;
	for (i = 0; i < MAX_USER_COUNT; i++) {
		if (m_user_list[i].h_socket = INVALID_SOCKET) break;
	}
	if (i < MAX_UCSCHAR)
	{
		m_user_list[i].h_socket = h_socket;
		// strcpy_s(m_user_list[i].ip_address, inet_ntoa(client_addr.sin_addr));
		inet_ntop(AF_INET, &(client_addr.sin_addr), m_user_list[i].ip_address, INET_ADDRSTRLEN);
		// WSAAsyncSelect(m_user_list[i].h_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		WSAEventSelect(m_user_list[i].h_socket, m_hWnd, FD_READ | FD_CLOSE);

		CString str;
		str.Format(_T("%s에서 접속했습니다."), m_user_list[i].ip_address);
		CStringA strA(str);
		const char* myChar = strA.GetString();
		AddEventString(myChar);
	}
	else
	{
		AddEventString("관리 최대 인원 초과 :(");
		closesocket(h_socket);
	}

	return 0;
}


void CExamServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	for (int i = 0; i < MAX_USER_COUNT; i++) {
		if (m_user_list[i].h_socket != INVALID_SOCKET)
		{
			closesocket(m_user_list[i].h_socket);
		}
	}
}

void CExamServerDlg::SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char *ap_send_data)
{// (어떤 소켓으로 전송할지, 메시지ID, 보낼 데이터의 크기, 보낼 데이터)
	char *p_send_data = new char[4 + a_body_size];	// 보낼 데이터 크기만큼 동적할당
	*p_send_data = 27;
	*(p_send_data + 1) = a_message_id;
	*(unsigned short *)(p_send_data + 2) = a_body_size;	// 1바이트로 할당된 배열을 캐스팅하여 2바이트까지 사용할수있도록 함
	memcpy(p_send_data + 4, ap_send_data, a_body_size);	// 보낼 메시지 p_send_data 버퍼에 저장

	send(ah_socket, p_send_data, a_body_size + 4, 0);	// 전송 함수

	delete[] p_send_data;							// 동적 할당 배열 제거
}

afx_msg LRESULT CExamServerDlg::On25002(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTEVENT(lParam) == FD_READ)
	{
		// WSAAsyncSelect(wParam, m_hWnd, 25002, FD_CLOSE);
		WSAEventSelect(wParam, m_hWnd, FD_CLOSE);

		char key;
		recv(wParam, &key, 1, 0);	// 수신버퍼를 1byte로 저장
		if (key == 27)
		{
			char message_id;
			recv(wParam, &message_id, 1, 0);
			unsigned short int body_size;
			recv(wParam, (char *)&body_size, 2, 0);

			char *p_body_data = NULL;
			if (body_size > 0)
			{
				p_body_data = new char[body_size];

				int total = 0, x, retry = 0;
				while (total < body_size)
				{
					x = recv(wParam, p_body_data, body_size, 0);
					if (x == SOCKET_ERROR) break;
					total = total + x;
					if (total < body_size)
					{
						Sleep(50);	// ms단위로 처리되는 딜레이 함수
						retry++;
						if (retry > 5) break;
					}
				}
			}

			// 여기 맞나??
			if (message_id == 1)
			{
				int i;
				for (i = 0; i < MAX_USER_COUNT; i++) {
					if (m_user_list[i].h_socket == wParam) break;
				}
				CString str;
				str.Format(_T("%s : %s"), m_user_list[i].ip_address, p_body_data);
				CStringA strA(str);
				const char* myChar = strA.GetString();
				AddEventString(myChar);

				for (i = 0; i < MAX_USER_COUNT; i++)	// 접속한 client들에게 채팅창을 보여주기 위함
				{
					if (m_user_list[i].h_socket != INVALID_SOCKET)
					{
						SendFrameData(m_user_list[i].h_socket, 1, str.GetLength() + 1, (char *)(const char *)myChar);
					}
				}
			}

			if (p_body_data != NULL) delete[] p_body_data;

			// WSAAsyncSelect(wParam, m_hWnd, 25002, FD_READ | FD_CLOSE);
			WSAEventSelect(wParam, m_hWnd, FD_CLOSE);
		}
	}
	else
	{
		closesocket(wParam);
		CString str;
		for (int i = 0; i < MAX_USER_COUNT; i++)
		{
			if (m_user_list[i].h_socket == wParam)
			{
				m_user_list[i].h_socket = INVALID_SOCKET;
				str.Format(_T("사용자가 종료했습니다. : %s"), m_user_list[i].ip_address);
				CStringA strA(str);
				const char* myChar = strA.GetString();
				AddEventString(myChar);
				break;
			}
		}
	}

	return 0;
}
