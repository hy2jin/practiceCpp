
// MFCApplication2View.cpp : CMFCApplication2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CFormView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CFormView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2View::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2View::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2View::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2View::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2View::OnBnClickedButton5)

	//ON_NOTIFY(THREAD_REDRAW_MSG, THREAD_IDD, &ThreadTest)
	ON_MESSAGE(THREAD_REDRAW_MSG, &ThreadTest)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCApplication2View 생성/소멸

CMFCApplication2View::CMFCApplication2View()
	: CFormView(CMFCApplication2View::IDD)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_Hour	= TIME_INIT;
	m_Day	= TIME_INIT;
	m_Month = TIME_INIT;

	bValChange = false;
}

CMFCApplication2View::~CMFCApplication2View()
{
}

void CMFCApplication2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
}


int CMFCApplication2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_Chart.Create(_T("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(10, 50, 1000, 320), this, 1003);
	//m_Chart.SetDrawAsCell(m_Chart.GetBottomAxis(), false);
	m_Thread.RunThread(ThreadVelo, this);

	return 0;
}


BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMFCApplication2View 진단

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


#pragma region 쓰레드
static UINT ThreadVelo(LPVOID pParam){


	CMFCApplication2View* pThis = (CMFCApplication2View*)pParam;
	int jkl = 0;
	while (pThis->m_Thread.bRun)
	{
		if (pThis->m_Thread.bONOFF)
		{
			SendMessage(pThis->GetSafeHwnd(), CMFCApplication2View::THREAD_REDRAW_MSG, 0, 0);

		}
		Sleep(1000);
	}
	pThis->m_Thread.bRun = FALSE;//쓰레드
	return 0;
}
#pragma endregion


// CMFCApplication2View 메시지 처리기

void CMFCApplication2View::OnBnClickedButton1()
{
	DrawChart();
}


void CMFCApplication2View::OnBnClickedButton2()
{
	if (m_Thread.bONOFF == TRUE)
	{//끈다
		//KillTimer(10);
		m_Thread.bONOFF = FALSE;
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T("OFF"));
	}
	else
	{//킨다
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T("ON"));
		m_Thread.bONOFF = TRUE;
	}
}

void CMFCApplication2View::OnBnClickedButton3()
{
	CChartLegend* pL = m_Chart.m_ChartCtrl.GetLegend();
	bool isVisible = pL->IsVisible();
	if (isVisible) {
		pL->SetVisible(SW_HIDE);
	}
	else {
		pL->SetVisible(SW_SHOW);
	}

	//pL->UndockLegend(329, 12);		//범례 위치 좌표
}


void CMFCApplication2View::OnBnClickedButton4()
{
	TRACE(_T("OnBnClickedButton4\n"));

	//여기서 헤더파일에 리스트 하나 만들고 해당되는 안전펜스 넘버를 0, 1, 2로 두기
	//0 안열림, 1 열림, 2 확인, 3 취소
	CPopMessageDlg* pDlg = new CPopMessageDlg(this);
	pDlg->ShowWindow(SW_SHOW); // 대화 상자를 비모달로 표시

	//SetTimer()로 돌면서 확인 눌렀는지 취소눌렀는지 그대로인지 확인하기
}


void CMFCApplication2View::OnBnClickedButton5()
{
	TRACE(_T("OnBnClickedButton5\n"));
}



void CMFCApplication2View::HandleThread()
{
	 //TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Thread.bRun == TRUE)
	{
		m_Thread.bRun = FALSE;//쓰레드
	}
	else {
		m_Thread.pThread = AfxBeginThread(ThreadVelo, this);
		if (m_Thread.pThread != NULL){
			m_Thread.bRun = TRUE;//쓰레드
			m_Thread.pThread->m_bAutoDelete = FALSE;
		}
		else {
			m_Thread.bRun = FALSE;//쓰레드
		}
	}
}


void CMFCApplication2View::CountSet(int i)
{
	CString ads;
	ads.Format(_T("%d"), i);
	GetDlgItem(IDC_EDIT1)->SetWindowText(ads);
}

void CMFCApplication2View::DrawChart()
{
	m_Chart.SetBarInterSpace(CRANE_MAX);//막대, 선
	TChartString strSerieName[CRANE_MAX] = {
		_T("CR01"), _T("CR02"), _T("CR03")
	};
	for (int cr = 0; cr < CRANE_MAX; cr++)
	{
		double YVal[50];
		for (int j = 0; j < MAX_BAR_COUNT; j++)
		{
			double temp = rand() % 10;
			if (cr == 0 && j == 0){
				temp = 0.2;
			}
			YVal[j] = temp;
		}
		m_Chart.Draw_Chart(cr, YVal, MAX_BAR_COUNT);
		m_Chart.pBarSeries[cr]->SetName(strSerieName[cr]);//막대, 선
		//m_Chart.pLineSeries[cr]->SetName(strSerieName[cr]);//막대, 선
	}

	CChartAxis* pAxis = m_Chart.GetBottomAxis();
	m_Chart.HandleLabel(pAxis);
	m_Chart.SetAxisMinMax(pAxis, MAX_BAR_COUNT);
	m_Chart.HandleLegend();
	m_Chart.ShowWindow(SW_SHOW);

	//CChartAxis* pAxis = m_Chart.m_ChartCtrl.GetBottomAxis();
	//m_Chart.HandleLabel(pAxis);
	//m_Chart.ShowWindow(SW_SHOW);
}



void CMFCApplication2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 10)
	{
		static int jkl = 0;
		DrawChart();
		CountSet(jkl);
		jkl++;
	}
	CFormView::OnTimer(nIDEvent);
}

//LRESULT afx_msg ThreadTest(WPARAM wParam, LPARAM lParam/*pResult*/);
LRESULT CMFCApplication2View::ThreadTest(WPARAM wParam, LPARAM lParam)
{
	static int jkl = 0;
	DrawChart();
	CountSet(jkl);
	jkl++;
	return 0;
}
