#pragma once


// CLogPeriod ��ȭ �����Դϴ�.

class CLogPeriod : public CDialog
{
	DECLARE_DYNAMIC(CLogPeriod)

public:
	CLogPeriod(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLogPeriod();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOGPERIOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSaveperiod();

	CString strServerPeriod, strClientPeriod;
	virtual BOOL OnInitDialog();
};
