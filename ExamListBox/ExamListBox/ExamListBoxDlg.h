
// ExamListBoxDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CExamListBoxDlg ��ȭ ����
class CExamListBoxDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CExamListBoxDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EXAMLISTBOX_DIALOG };

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
private:
	CListBox m_chat_list;
public:
	afx_msg void OnBnClickedInputButton();
	afx_msg void OnLbnSelchangeChatList();
	afx_msg void OnBnClickedResetButton();
};
