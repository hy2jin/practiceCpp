
// ExamServerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CExamServerDlg ��ȭ ����
class CExamServerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CExamServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EXAMSERVER_DIALOG };

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
	void AddEventString(const char *ap_string);
	DECLARE_MESSAGE_MAP()
private:
	CListBox m_event_list;
};
