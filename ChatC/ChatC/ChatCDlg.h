
// ChatCDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

#include "ClientSocket.h"
#include "resource.h"


// CChatCDlg 대화 상자
class CChatCDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatCDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

public:
	CClientSocket m_Client;
	CString m_strInputIpAddress;	//IP컨트롤에 입력받은 서버의 IP주소
	CString m_strClientPort;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHATC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CListBox m_ListC;
	CButton m_ButtonSendC;
	CButton m_ButtonConnectC;
	CButton m_ButtonDisconnectC;

	afx_msg void OnBnClickedButtonConnectC();
	afx_msg void OnBnClickedButtonDisconnectC();
	afx_msg void OnBnClickedButtonSendC();

	void HandleConnectC();
	void HandleDisconnectC();
	void HandleEditFlagC(BOOL flag);
	void HandleListMsgC(CString msg);

	UINT m_TryCount;
};
