
// OneServerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "stdafx.h"


// COneServerDlg 대화 상자
class COneServerDlg : public CDialogEx
{
// 생성입니다.
public:
	COneServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CSocServer m_socServer;
	CSocCom* m_socCom;

	// CEdit m_strSend;
	CString m_strSend;
	CListBox m_list;
	// CStatic m_strStatus;
	CString m_strStatus;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ONESERVER_DIALOG };

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
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM IParam);	// 클라이언트 접속 요청이 왔을 때 실행되는 메세지 함수
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM IParam);	// 클라이언트에서 오는 데이터 수신할 때 실행되는 메세지 함수
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClickedButtonSend();
};
