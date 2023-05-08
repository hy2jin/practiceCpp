
// CoffeShopDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CoffeShop.h"
#include "CoffeShopDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoffeShopDlg 대화 상자



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


// CCoffeShopDlg 메시지 처리기

BOOL CCoffeShopDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_count_spin.GetWindowRect(&m_spin_rect);
	ScreenToClient(&m_spin_rect);

	wchar_t *p_item_name[MAX_ITEM_COUNT] = {
		L"아메리카노      1900원", L"카페라떼        2500원",
		L"카페모카        2800원", L"카라멜마끼아또  3200원",
		L"에스프레소      2800원", L"바닐라라떼      3500원",
		L"카푸치노        2800원", L"비엔나          3500원",
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCoffeShopDlg::OnPaint()
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
