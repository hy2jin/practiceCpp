
// ChatSDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "resource.h"

#include "ListenSocket.h"
#include "ChildSocket.h"
#include "ClientSocket.h"

#include "SettingIpPort.h"

// CChatSDlg 대화 상자
class CChatSDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatSDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

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

//SETTING
public:
	void GetThisPath();
	void ReadIniFile();
	void CreateIniFile();

	CString thisPath;

public:
	void CreateLogFolder();
	CString serverLogFolderPath, clientLogFolderPath;

	CString m_strLogPeriodS, m_strLogPeriodC;

	CString GetLogFileName();

	void LogMsg(CString msg, CString logFileName);
	void LogMsgServer(CString msg);
	void LogMsgClient(CString msg);
	void DeleteOldFiles(CString folderPath, CString period);




//SERVER
public:
	CListBox m_ListS;
	CButton m_ButtonOpenS;
	CButton m_ButtonCloseS;
	CButton m_ButtonSendS;

	afx_msg void OnBnClickedButtonOpenS();
	afx_msg void OnBnClickedButtonCloseS();
	afx_msg void OnBnClickedButtonSendS();

	void HandleListMsgS(CString msg, BOOL isLog = TRUE);
	void HandleEditFlagS(BOOL flag, BOOL all = FALSE);
	void HandleDisconnectS(int flag);

	BOOL m_isWaitting = FALSE;
	CListenSocket* m_pListenSoc;		//클라이언트의 접속을 위해 대기하는 서버소켓
	CString m_strIpS;
	CString m_strPortS;



//CLIENT
public:
	CListBox m_ListC;
	CButton m_ButtonSendC;
	CButton m_ButtonConnectC;
	CButton m_ButtonDisconnectC;

	afx_msg void OnBnClickedButtonConnectC();
	afx_msg void OnBnClickedButtonDisconnectC();
	afx_msg void OnBnClickedButtonSendC();

	void HandleListMsgC(CString msg, BOOL isLog = TRUE);
	void HandleEditFlagC(BOOL flag, BOOL all = FALSE);
	void HandleConnectC();
	void HandleDisconnectC();

	CClientSocket m_ClientSoc;
	UINT m_TryCount;
	CString m_strIpC, m_strPortC;

public:
	afx_msg void OnMenuLogPeriod();
	afx_msg void OnMenuServerClient();

	BOOL m_isServerBlock = FALSE;
	BOOL m_isClientBlock = FALSE;

};

extern BOOL m_isServerBlock, m_isClientBlock;