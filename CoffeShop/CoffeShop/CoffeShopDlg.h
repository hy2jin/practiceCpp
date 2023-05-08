
// CoffeShopDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


#define MAX_ITEM_COUNT    8

// CCoffeShopDlg 대화 상자
class CCoffeShopDlg : public CDialogEx
{
private:
	CCheckListBox m_item_list;
	CRect m_spin_rect;

// 생성입니다.
public:
	CCoffeShopDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	void CalcTotalPrice();
	void ChangeText(CListBox *ap_list_box, int a_index, const wchar_t *ap_string);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COFFESHOP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeItemList();
	CListBox m_count_list;
	CSpinButtonCtrl m_count_spin;
	afx_msg void OnDeltaposCountSpin(NMHDR *pNMHDR, LRESULT *pResult);
};
