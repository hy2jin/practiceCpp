
// MFCApplication2View.h : CMFCApplication2View 클래스의 인터페이스
//

#pragma once

#include "resource.h"

#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartBarSerie.h"

#include "ImChart.h"
#include "PopMessageDlg.h"

static UINT ThreadVelo(LPVOID pParam);
class CMFCApplication2View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication2View();
	DECLARE_DYNCREATE(CMFCApplication2View)

public:
	enum{ IDD = IDD_MFCAPPLICATION2_FORM };
	enum{
		THREAD_IDD = 5000,
		THREAD_REDRAW_MSG,
	};
// 특성입니다.
public:
	CMFCApplication2Doc* GetDocument() const;

// 작업입니다.
public:
	struct _thread{
		CWinThread *pThread;
		BOOL bRun;
		BOOL bONOFF;

		_thread() {
			pThread = NULL;
			bRun = FALSE;
		}
		~_thread() {
			StopThread();
		}

		void RunThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
			int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
			DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
		{
			bRun = TRUE;
			bONOFF = FALSE;
			pThread = AfxBeginThread(pfnThreadProc, pParam);
			pThread->m_bAutoDelete = FALSE;
		}

		void StopThread()
		{
			if (pThread) {
				bRun = FALSE;
				pThread->SuspendThread();
				DWORD dwRes;
				::GetExitCodeThread(pThread, &dwRes);
				delete pThread;
				pThread = NULL;
			}
		}

	}m_Thread;

	void CountSet(int i);

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

	enum
	{
		CRANE_MAX = 3,
		MAX_BAR_COUNT = 1,
		TIME_INIT = 100,
	};

// 구현입니다.
public:
	virtual ~CMFCApplication2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	int m_Hour, m_Day, m_Month;
	bool bValChange;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void HandleThread();
	CImBarChart m_Chart;	//막대, 선
	//CImLineChart m_Chart;	//막대, 선
	void DrawChart();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	LRESULT afx_msg ThreadTest(WPARAM wParam, LPARAM lParam/*pResult*/);
};

#ifndef _DEBUG  // MFCApplication2View.cpp의 디버그 버전
inline CMFCApplication2Doc* CMFCApplication2View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument); }
#endif

