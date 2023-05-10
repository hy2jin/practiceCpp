
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
	CListBox m_List;
	CEdit m_Edit;
	CButton m_ButtonSend;
	CButton m_ButtonConnect;

	CString m_strData;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
};
