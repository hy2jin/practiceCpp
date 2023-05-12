
// ChatCDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

#include "ClientSocket.h"
#include "resource.h"


// CChatCDlg ��ȭ ����
class CChatCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChatCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

public:
	CClientSocket m_Client;
	CString m_strInputIpAddress;	//IP��Ʈ�ѿ� �Է¹��� ������ IP�ּ�
	CString m_strClientPort;

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
	CListBox m_ListC;
	CButton m_ButtonSendC;
	CButton m_ButtonConnectC;
	CButton m_ButtonDisconnectC;

	afx_msg void OnBnClickedButtonConnectC();
	afx_msg void OnBnClickedButtonDisconnectC();
	afx_msg void OnBnClickedButtonSendC();

	void HandleConnectC();
	void HandleDisconnectC();
	void HandleEditFlagC(BOOL flag);
	void HandleListMsgC(CString msg);

	UINT m_TryCount;
};
