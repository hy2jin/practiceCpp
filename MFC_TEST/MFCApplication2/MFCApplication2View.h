
// MFCApplication2View.h : CMFCApplication2View Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CMFCApplication2View();
	DECLARE_DYNCREATE(CMFCApplication2View)

public:
	enum{ IDD = IDD_MFCAPPLICATION2_FORM };
	enum{
		THREAD_IDD = 5000,
		THREAD_REDRAW_MSG,
	};
// Ư���Դϴ�.
public:
	CMFCApplication2Doc* GetDocument() const;

// �۾��Դϴ�.
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

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

	enum
	{
		CRANE_MAX = 3,
		MAX_BAR_COUNT = 1,
		TIME_INIT = 100,
	};

// �����Դϴ�.
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

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void HandleThread();
	CImBarChart m_Chart;	//����, ��
	//CImLineChart m_Chart;	//����, ��
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

#ifndef _DEBUG  // MFCApplication2View.cpp�� ����� ����
inline CMFCApplication2Doc* CMFCApplication2View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument); }
#endif

