
// ValueServerDlg.h : ��� ����
//

#pragma once
#include "MyServer.h"

// CValueServerDlg ��ȭ ����
class CValueServerDlg : public CDialogEx
{
// �����Դϴ�.
private:
	MyServer m_server;

public:
	CValueServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VALUESERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
