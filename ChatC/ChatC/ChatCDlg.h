
// ChatCDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CChatCDlg ��ȭ ����
class CChatCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChatCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHATC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	CEdit m_Edit;
	CButton m_ButtonSend;
	CButton m_ButtonConnect;
};
