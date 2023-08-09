
// practiceDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "practice.h"
#include "practiceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpracticeDlg 대화 상자



CpracticeDlg::CpracticeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpracticeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpracticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CpracticeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &CpracticeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CpracticeDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CpracticeDlg 메시지 처리기

BOOL CpracticeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CpracticeDlg::OnPaint()
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
HCURSOR CpracticeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CpracticeDlg::PreTranslateMessage(MSG* pMsg)
{
	// 엔터키 종료 막기
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


int CpracticeDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	int i;
	CPerson dump;
	CString strNum;

	pPerson = &m_people[0]; pPerson->RemoveAll();
	for (i = 1; i <= 10; i++)
	{
		strNum.Format(_T("%d"), i);
		dump.reset();

		dump.m_name = _T("이름") + strNum;
		dump.m_age = i;
		dump.m_school[0] = _T("가") + strNum;
		dump.m_school[1] = _T("나") + strNum;
		dump.m_school[2] = _T("다") + strNum;

		pPerson->Add(dump);
	}

	pPerson = &m_people[1]; pPerson->RemoveAll();
	for (i = 1; i <= 5; i++)
	{
		strNum.Format(_T("%d"), i);
		dump.reset();

		dump.m_name = _T("네임") + strNum;
		dump.m_age = i;
		dump.m_school[0] = _T("라") + strNum;
		dump.m_school[1] = _T("마") + strNum;
		dump.m_school[2] = _T("바") + strNum;

		pPerson->Add(dump);
	}

	return 0;
}


void CpracticeDlg::AddPeople()
{
	if (m_list.GetCount() > 0)
		m_list.AddString(_T("========"));

	CString info;
	for (int idx = 0; idx < pPerson->GetSize(); idx++)
	{
		info.Format(_T("%s, %d살, %s, %s, %s")		//두 가지 방법 다 사용 가능함
			, (*pPerson)[idx].m_name
			, (*pPerson)[idx].m_age
			, (*pPerson)[idx].m_school[0]
			, (*pPerson)[idx].m_school[1]
			, (*pPerson)[idx].m_school[2]
			);
		/*info.Format(_T("%s, %d살, %s, %s, %s")
		, pPerson->GetAt(idx).m_name
		, pPerson->GetAt(idx).m_age
		, pPerson->GetAt(idx).m_school[0]
		, pPerson->GetAt(idx).m_school[1]
		, pPerson->GetAt(idx).m_school[2]
		);*/

		m_list.AddString(info);
	}

	m_list.SetAnchorIndex(m_list.GetCount() - 1);		//스크롤 아래로 내리기
}

void CpracticeDlg::OnBnClickedButton1()
{
	pPerson = &m_people[0];
	AddPeople();
}


void CpracticeDlg::OnBnClickedButton2()
{
	pPerson = &m_people[1];
	AddPeople();
}
