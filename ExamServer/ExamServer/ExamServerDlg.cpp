
// ExamServerDlg.cpp : ���� ����
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


// CExamServerDlg ��ȭ ����



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


// CExamServerDlg �޽��� ó����

BOOL CExamServerDlg::OnInitDialog()
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
	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);		// Address Family, SOCK-STREAM : TCP���, 0: 2��° ���ڸ� ����
	sockaddr_in srv_addr;
	srv_addr.sin_family = AF_INET;
	// srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// char ip4[INET_ADDRSTRLEN];
	inet_pton(AF_INET, "1270.0.01", &(srv_addr.sin_addr));
	srv_addr.sin_port = htons(18000);
	bind(mh_listen_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));

	AddEventString("���񽺸� �����մϴ� :)");
	listen(mh_listen_socket, 1);
	// WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);
	WSAEventSelect(mh_listen_socket, m_hWnd, FD_ACCEPT);
	// h_socket�� FD_ACCEPT�޽����� �߻��ϸ� m_hWnd�� 25001�� ��û��. ��������� ������ �ʱ� ����

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CExamServerDlg::OnPaint()
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
		str.Format(_T("%s���� �����߽��ϴ�."), m_user_list[i].ip_address);
		CStringA strA(str);
		const char* myChar = strA.GetString();
		AddEventString(myChar);
	}
	else
	{
		AddEventString("���� �ִ� �ο� �ʰ� :(");
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
{// (� �������� ��������, �޽���ID, ���� �������� ũ��, ���� ������)
	char *p_send_data = new char[4 + a_body_size];	// ���� ������ ũ�⸸ŭ �����Ҵ�
	*p_send_data = 27;
	*(p_send_data + 1) = a_message_id;
	*(unsigned short *)(p_send_data + 2) = a_body_size;	// 1����Ʈ�� �Ҵ�� �迭�� ĳ�����Ͽ� 2����Ʈ���� ����Ҽ��ֵ��� ��
	memcpy(p_send_data + 4, ap_send_data, a_body_size);	// ���� �޽��� p_send_data ���ۿ� ����

	send(ah_socket, p_send_data, a_body_size + 4, 0);	// ���� �Լ�

	delete[] p_send_data;							// ���� �Ҵ� �迭 ����
}

afx_msg LRESULT CExamServerDlg::On25002(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTEVENT(lParam) == FD_READ)
	{
		// WSAAsyncSelect(wParam, m_hWnd, 25002, FD_CLOSE);
		WSAEventSelect(wParam, m_hWnd, FD_CLOSE);

		char key;
		recv(wParam, &key, 1, 0);	// ���Ź��۸� 1byte�� ����
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
						Sleep(50);	// ms������ ó���Ǵ� ������ �Լ�
						retry++;
						if (retry > 5) break;
					}
				}
			}

			// ���� �³�??
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

				for (i = 0; i < MAX_USER_COUNT; i++)	// ������ client�鿡�� ä��â�� �����ֱ� ����
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
				str.Format(_T("����ڰ� �����߽��ϴ�. : %s"), m_user_list[i].ip_address);
				CStringA strA(str);
				const char* myChar = strA.GetString();
				AddEventString(myChar);
				break;
			}
		}
	}

	return 0;
}
