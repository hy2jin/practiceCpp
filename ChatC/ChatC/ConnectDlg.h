#pragma once


// CConnectDlg ��ȭ �����Դϴ�.

class CConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConnectDlg();

public:
	CString m_strIPAddress;	//IP��Ʈ�ѿ� �Է¹��� ������ IP�ּ�
	CString m_strPort;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONNECTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
