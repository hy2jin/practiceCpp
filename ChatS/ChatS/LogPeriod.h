#pragma once


// CLogPeriod 대화 상자입니다.

class CLogPeriod : public CDialog
{
	DECLARE_DYNAMIC(CLogPeriod)

public:
	CLogPeriod(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLogPeriod();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOGPERIOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSaveperiod();

	CString strServerPeriod, strClientPeriod;
	virtual BOOL OnInitDialog();
};
