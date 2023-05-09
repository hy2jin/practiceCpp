
// OneServerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "stdafx.h"


// COneServerDlg ��ȭ ����
class COneServerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	COneServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CSocServer m_socServer;
	CSocCom* m_socCom;

	// CEdit m_strSend;
	CString m_strSend;
	CListBox m_list;
	// CStatic m_strStatus;
	CString m_strStatus;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ONESERVER_DIALOG };

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
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM IParam);	// Ŭ���̾�Ʈ ���� ��û�� ���� �� ����Ǵ� �޼��� �Լ�
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM IParam);	// Ŭ���̾�Ʈ���� ���� ������ ������ �� ����Ǵ� �޼��� �Լ�
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClickedButtonSend();
};
