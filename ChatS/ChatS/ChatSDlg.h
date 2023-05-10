
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
};
