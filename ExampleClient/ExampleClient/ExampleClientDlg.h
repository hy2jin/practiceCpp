
// ExampleClientDlg.h : ��� ����
//

#pragma once


// CExampleClientDlg ��ȭ ����
class CExampleClientDlg : public CDialogEx
{
private:
	SOCKET mh_socket = INVALID_SOCKET;
	char m_connect_flag = 0;	// 0:��������, 1:������, 2:���ӵ�
// �����Դϴ�.
public:
	CExampleClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EXAMPLECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendButton();
	afx_msg void OnDestroy();
	void CExampleClientDlg::AddEventString(const char *ap_string);
protected:
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
};
