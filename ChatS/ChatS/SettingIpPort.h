#pragma once


// CSettingIpPort ��ȭ �����Դϴ�.

class CSettingIpPort : public CDialog
{
	DECLARE_DYNAMIC(CSettingIpPort)

public:
	CSettingIpPort(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSettingIpPort();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETTINGIPPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSaveSetting();

	CString strIPS, strPortS, strIPC, strPortC;
	virtual BOOL OnInitDialog();
};
