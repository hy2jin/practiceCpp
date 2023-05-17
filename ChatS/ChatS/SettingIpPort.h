#pragma once


// CSettingIpPort 대화 상자입니다.

class CSettingIpPort : public CDialog
{
	DECLARE_DYNAMIC(CSettingIpPort)

public:
	CSettingIpPort(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSettingIpPort();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETTINGIPPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSaveSetting();

	CString strIPS, strPortS, strIPC, strPortC;
	virtual BOOL OnInitDialog();
};
