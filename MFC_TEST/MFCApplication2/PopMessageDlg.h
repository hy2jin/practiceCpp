#pragma once


// CPopMessageDlg 대화 상자입니다.

class CPopMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPopMessageDlg)

public:
	CPopMessageDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPopMessageDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_POPMESSAGEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	int m_abc;
};
