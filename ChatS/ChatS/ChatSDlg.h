
// ChatSDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

#include "ListenSocket.h"
#include "resource.h"


// CChatSDlg ��ȭ ����
class CChatSDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChatSDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	//Ŭ���̾�Ʈ�� ������ ���� ����ϴ� ��������
	CListenSocket* m_pListenSocket;

	CString m_strIpAddress = _T("127.0.0.1");
	CString m_strPort;

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
	CListBox m_List;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonOpen();
	CButton m_ButtonOpen;
	CButton m_ButtonClose;
	afx_msg void OnBnClickedButtonClose();
};
