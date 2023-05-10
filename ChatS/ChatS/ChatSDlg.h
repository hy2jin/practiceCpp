
// ChatSDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

#include "ListenSocket.h"
#include "resource.h"


// CChatSDlg 대화 상자
class CChatSDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatSDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	//클라이언트의 접속을 위해 대기하는 서버소켓
	CListenSocket* m_pListenSocket;

	CString m_strIpAddress = _T("192.168.0.75");
	//CString m_strIpAddress = _T("127.0.0.1");
	CString m_strPort;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHATS_DIALOG };

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
	CButton m_ButtonOpen;
	CButton m_ButtonClose;
	CButton m_ButtonSend;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonSend();
};
