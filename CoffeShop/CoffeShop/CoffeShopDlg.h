
// CoffeShopDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


#define MAX_ITEM_COUNT    8

// CCoffeShopDlg ��ȭ ����
class CCoffeShopDlg : public CDialogEx
{
private:
	CCheckListBox m_item_list;
	CRect m_spin_rect;

// �����Դϴ�.
public:
	CCoffeShopDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	void CalcTotalPrice();
	void ChangeText(CListBox *ap_list_box, int a_index, const wchar_t *ap_string);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COFFESHOP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
