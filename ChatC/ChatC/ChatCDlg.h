
// ChatCDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

#include "ClientSocket.h"
#include "ListenSocket.h"
#include "ChildSocket.h"
#include "resource.h"


// CChatCDlg ��ȭ ����
class CChatCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChatCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

public:

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

	CClientSocket m_ClientSoc;
	CString m_strIpC;	//IP��Ʈ�ѿ� �Է¹��� ������ IP�ּ�
	CString m_strPortC;
	UINT m_TryCount;

public:
	CListBox m_ListS;
	CButton m_ButtonSendS;
	CButton m_ButtonOpenS;
	CButton m_ButtonCloseS;

	afx_msg void OnBnClickedButtonOpenS();
	afx_msg void OnBnClickedButtonCloseS();
	afx_msg void OnBnClickedButtonSendS();

	void HandleListMsgS(CString msg);
	void HandleEditFlagS(BOOL flag);
	void HandleDisconnectS(UINT flag);	//0: �ݾҴ� �ٽ� ����, 1: ������ ����, 2: Ŭ���̾�Ʈ�� ����

	CListenSocket* m_pListenSoc;
	CString m_strIpS = _T("127.0.0.1");
	//CString m_strIpS = _T("192.168.0.75");
	CString m_strPortS = _T("8000");
};
