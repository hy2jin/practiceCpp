
// ExamServerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

#define MAX_USER_COUNT 100

struct UserData
{
	SOCKET h_socket;
	char ip_address[16];
};


// CExamServerDlg 대화 상자
class CExamServerDlg : public CDialogEx
{
private:
	SOCKET mh_listen_socket;
	UserData m_user_list[MAX_USER_COUNT];

// 생성입니다.
public:
	CExamServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EXAMSERVER_DIALOG };

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
	void AddEventString(const char *ap_string);
	DECLARE_MESSAGE_MAP()
private:
	CListBox m_event_list;
protected:
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
protected:
	void SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char *ap_send_data);
	afx_msg LRESULT On25002(WPARAM wParam, LPARAM lParam);
};
