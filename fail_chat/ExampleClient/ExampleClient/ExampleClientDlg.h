
// ExampleClientDlg.h : 헤더 파일
//

#pragma once


// CExampleClientDlg 대화 상자
class CExampleClientDlg : public CDialogEx
{
private:
	SOCKET mh_socket = INVALID_SOCKET;
	char m_connect_flag = 0;	// 0:접속해제, 1:접속중, 2:접속됨
// 생성입니다.
public:
	CExampleClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EXAMPLECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
