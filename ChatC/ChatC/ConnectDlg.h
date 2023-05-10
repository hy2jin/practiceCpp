#pragma once


// CConnectDlg 대화 상자입니다.

class CConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConnectDlg();

public:
	CString m_strIPAddress;	//IP컨트롤에 입력받은 서버의 IP주소
	CString m_strPort;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONNECTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
