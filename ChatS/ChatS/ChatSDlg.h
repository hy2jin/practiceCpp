
// ChatSDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "resource.h"

#include "ListenSocket.h"
#include "ChildSocket.h"
#include "ClientSocket.h"

// CChatSDlg ��ȭ ����
class CChatSDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChatSDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHATS_DIALOG };

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
	CListBox m_ListS;
	CButton m_ButtonOpenS;
	CButton m_ButtonCloseS;
	CButton m_ButtonSendS;

	afx_msg void OnBnClickedButtonOpenS();
	afx_msg void OnBnClickedButtonCloseS();
	afx_msg void OnBnClickedButtonSendS();

	void HandleListMsgS(CString msg);
	void HandleEditFlagS(BOOL flag);
	void HandleDisconnectS(int flag);	//0: ��¾���, 1: ������ ����, 2: Ŭ���̾�Ʈ�� ����

	CListenSocket* m_pListenSoc;		//Ŭ���̾�Ʈ�� ������ ���� ����ϴ� ��������
	CString m_strIpS = _T("127.0.0.1");
	//CString m_strIpS = _T("192.168.0.75");
	CString m_strPortS = _T("9000");


public:
	CListBox m_ListC;
	CButton m_ButtonSendC;
	CButton m_ButtonConnectC;
	CButton m_ButtonDisconnectC;

	afx_msg void OnBnClickedButtonConnectC();
	afx_msg void OnBnClickedButtonDisconnectC();
	afx_msg void OnBnClickedButtonSendC();

	void HandleListMsgC(CString msg);
	void HandleEditFlagC(BOOL flag);
	void HandleConnectC();
	void HandleDisconnectC();

	CClientSocket m_ClientSoc;
	UINT m_TryCount;
	CString m_strIpC;
	CString m_strPortC;
};