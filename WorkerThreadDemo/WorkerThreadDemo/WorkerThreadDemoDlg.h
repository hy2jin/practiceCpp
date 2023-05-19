
// WorkerThreadDemoDlg.h : 헤더 파일
//

#pragma once


// CWorkerThreadDemoDlg 대화 상자
class CWorkerThreadDemoDlg : public CDialogEx
{
// 생성입니다.
public:
	CWorkerThreadDemoDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WORKERTHREADDEMO_DIALOG };

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
	afx_msg void OnBnClickedButtonRunnotepad();

public:
	bool m_bExitFlag;	// 스레드 종료를 위한
	static UINT ThreadFunc(LPVOID lParam);	// 스레드에 이용할 함수
	static void Wait(ULONGLONG dwMillisecond);	// Sleep대신에 사용할 함수

	void ExitThread();	// 스레드를 종료하도록 유도하는 함수
	afx_msg void OnBnClickedButtonStoptick();
};
