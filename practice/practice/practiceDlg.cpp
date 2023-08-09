
// practiceDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "practice.h"
#include "practiceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpracticeDlg ��ȭ ����



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


// CpracticeDlg �޽��� ó����

BOOL CpracticeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CpracticeDlg::OnPaint()
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
HCURSOR CpracticeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CpracticeDlg::PreTranslateMessage(MSG* pMsg)
{
	// ����Ű ���� ����
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

		dump.m_name = _T("�̸�") + strNum;
		dump.m_age = i;
		dump.m_school[0] = _T("��") + strNum;
		dump.m_school[1] = _T("��") + strNum;
		dump.m_school[2] = _T("��") + strNum;

		pPerson->Add(dump);
	}

	pPerson = &m_people[1]; pPerson->RemoveAll();
	for (i = 1; i <= 5; i++)
	{
		strNum.Format(_T("%d"), i);
		dump.reset();

		dump.m_name = _T("����") + strNum;
		dump.m_age = i;
		dump.m_school[0] = _T("��") + strNum;
		dump.m_school[1] = _T("��") + strNum;
		dump.m_school[2] = _T("��") + strNum;

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
		info.Format(_T("%s, %d��, %s, %s, %s")		//�� ���� ��� �� ��� ������
			, (*pPerson)[idx].m_name
			, (*pPerson)[idx].m_age
			, (*pPerson)[idx].m_school[0]
			, (*pPerson)[idx].m_school[1]
			, (*pPerson)[idx].m_school[2]
			);
		/*info.Format(_T("%s, %d��, %s, %s, %s")
		, pPerson->GetAt(idx).m_name
		, pPerson->GetAt(idx).m_age
		, pPerson->GetAt(idx).m_school[0]
		, pPerson->GetAt(idx).m_school[1]
		, pPerson->GetAt(idx).m_school[2]
		);*/

		m_list.AddString(info);
	}

	m_list.SetAnchorIndex(m_list.GetCount() - 1);		//��ũ�� �Ʒ��� ������
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
