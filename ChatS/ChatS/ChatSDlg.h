
// ChatSDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "resource.h"

#include "ListenSocket.h"
#include "ChildSocket.h"


// CChatSDlg 대화 상자
class CChatSDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatSDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CListenSocket* m_pListenSocket;		//클라이언트의 접속을 위해 대기하는 서버소켓

	//CString m_strServerIpAddress = _T("192.168.0.75");
	CString m_strServerIpAddress = _T("127.0.0.1");

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
	CListBox m_ListS;
	CButton m_ButtonOpenS;
	CButton m_ButtonCloseS;
	CButton m_ButtonSendS;

	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonOpenS();
	afx_msg void OnBnClickedButtonCloseS();
	afx_msg void OnBnClickedButtonSendS();

	void HandleDisconnectS(int flag);	//0: 출력없음, 1: 서버가 닫음, 2: 클라이언트가 닫음
	void HandleConnectS();
	void HandleEditFlagS(BOOL flag);
	void HandleListMsgS(CString msg);

	CString m_strPortS = _T("9000");
};