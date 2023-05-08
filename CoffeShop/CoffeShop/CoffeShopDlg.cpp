
// CoffeShopDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CoffeShop.h"
#include "CoffeShopDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoffeShopDlg ��ȭ ����



CCoffeShopDlg::CCoffeShopDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCoffeShopDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoffeShopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COUNT_LIST, m_count_list);
	DDX_Control(pDX, IDC_COUNT_SPIN, m_count_spin);
}

BEGIN_MESSAGE_MAP(CCoffeShopDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, &CCoffeShopDlg::OnLbnSelchangeItemList)
	ON_NOTIFY(UDN_DELTAPOS, IDC_COUNT_SPIN, &CCoffeShopDlg::OnDeltaposCountSpin)
END_MESSAGE_MAP()


// CCoffeShopDlg �޽��� ó����

BOOL CCoffeShopDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_count_spin.GetWindowRect(&m_spin_rect);
	ScreenToClient(&m_spin_rect);

	wchar_t *p_item_name[MAX_ITEM_COUNT] = {
		L"�Ƹ޸�ī��      1900��", L"ī���        2500��",
		L"ī���ī        2800��", L"ī��Ḷ���ƶ�  3200��",
		L"����������      2800��", L"�ٴҶ��      3500��",
		L"īǪġ��        2800��", L"�񿣳�          3500��",
	};

	int price[8] = { 1900, 2500, 2800, 3200, 1800, 3500, 3300, 3500 };

	m_item_list.SubclassDlgItem(IDC_ITEM_LIST, this);
	m_item_list.SetItemHeight(0, 24);
	m_count_list.SetItemHeight(0, 24);

	for (int i = 0; i < MAX_ITEM_COUNT; i++) {
		m_item_list.InsertString(i, p_item_name[i]);
		m_item_list.SetItemData(i, price[i]);
		m_count_list.InsertString(i, L"0");
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCoffeShopDlg::OnPaint()
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
HCURSOR CCoffeShopDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCoffeShopDlg::CalcTotalPrice()
{
	int count = m_item_list.GetCount();
	int total_price = 0;
	CString str;

	for (int i = 0; i < count; i++) {
		if (m_item_list.GetCheck(i)) {
			m_count_list.GetText(i, str);
			total_price += m_item_list.GetItemData(i) * _wtoi(str);
		}
	}

	SetDlgItemInt(IDC_TOTAL_PRICE, total_price);
}

void CCoffeShopDlg::ChangeText(CListBox *ap_list_box, int a_index, const wchar_t *ap_string)
{
	ap_list_box->DeleteString(a_index);
	ap_list_box->InsertString(a_index, ap_string);
	ap_list_box->SetCurSel(a_index);
}

void CCoffeShopDlg::OnLbnSelchangeItemList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_item_list.GetCurSel();

	CString str;
	m_count_list.GetText(index, str);
	int item_count = _wtoi(str);			// L"0" -> 0

	if (m_item_list.GetCheck(index)) {
		if (item_count == 0) ChangeText(&m_count_list, index, L"1");
	}
	else {
		if (item_count != 0) ChangeText(&m_count_list, index, L"0");
	}

	m_count_list.SetCurSel(index);
	m_count_spin.SetWindowPos(NULL, m_spin_rect.left, m_spin_rect.top + index * 24, 0, 0, SWP_NOSIZE);

	CalcTotalPrice();
}


void CCoffeShopDlg::OnDeltaposCountSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	int index = m_item_list.GetCurSel();
	if (LB_ERR != index && m_item_list.GetCheck(index)) {
		CString str;
		m_count_list.GetText(index, str);
		int item_count = _wtoi(str);			// L"0" -> 0

		if (pNMUpDown->iDelta > 0) {
			if (item_count > 1) item_count--;
		}
		else {
			if (item_count < 10) item_count++;
		}

		str.Format(L"%d", item_count);			// 1 -> L"1"
		ChangeText(&m_count_list, index, str);

		CalcTotalPrice();
	}

}
