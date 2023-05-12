
// ChatSDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "resource.h"

#include "ListenSocket.h"
#include "ChildSocket.h"


// CChatSDlg ��ȭ ����
class CChatSDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChatSDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CListenSocket* m_pListenSocket;		//Ŭ���̾�Ʈ�� ������ ���� ����ϴ� ��������

	//CString m_strServerIpAddress = _T("192.168.0.75");
	CString m_strServerIpAddress = _T("127.0.0.1");

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

	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonOpenS();
	afx_msg void OnBnClickedButtonCloseS();
	afx_msg void OnBnClickedButtonSendS();

	void HandleDisconnectS(int flag);	//0: ��¾���, 1: ������ ����, 2: Ŭ���̾�Ʈ�� ����
	void HandleConnectS();
	void HandleEditFlagS(BOOL flag);
	void HandleListMsgS(CString msg);

	CString m_strPortS = _T("9000");
};