#pragma once


// CPopMessageDlg ��ȭ �����Դϴ�.

class CPopMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPopMessageDlg)

public:
	CPopMessageDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPopMessageDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_POPMESSAGEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	int m_abc;
};
