
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
	afx_msg void OnDestroy();
};
