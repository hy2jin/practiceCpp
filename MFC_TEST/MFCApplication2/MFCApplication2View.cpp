
// MFCApplication2View.cpp : CMFCApplication2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CMFCApplication2View ����/�Ҹ�

CMFCApplication2View::CMFCApplication2View()
	: CFormView(CMFCApplication2View::IDD)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_Chart.Create(_T("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(10, 50, 1000, 320), this, 1003);
	//m_Chart.SetDrawAsCell(m_Chart.GetBottomAxis(), false);
	m_Thread.RunThread(ThreadVelo, this);

	return 0;
}


BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMFCApplication2View ����

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


#pragma region ������
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
	pThis->m_Thread.bRun = FALSE;//������
	return 0;
}
#pragma endregion


// CMFCApplication2View �޽��� ó����

void CMFCApplication2View::OnBnClickedButton1()
{
	DrawChart();
}


void CMFCApplication2View::OnBnClickedButton2()
{
	if (m_Thread.bONOFF == TRUE)
	{//����
		//KillTimer(10);
		m_Thread.bONOFF = FALSE;
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T("OFF"));
	}
	else
	{//Ų��
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

	//pL->UndockLegend(329, 12);		//���� ��ġ ��ǥ
}


void CMFCApplication2View::OnBnClickedButton4()
{
	TRACE(_T("OnBnClickedButton4\n"));

	//���⼭ ������Ͽ� ����Ʈ �ϳ� ����� �ش�Ǵ� �����潺 �ѹ��� 0, 1, 2�� �α�
	//0 �ȿ���, 1 ����, 2 Ȯ��, 3 ���
	CPopMessageDlg* pDlg = new CPopMessageDlg(this);
	pDlg->ShowWindow(SW_SHOW); // ��ȭ ���ڸ� ���޷� ǥ��

	//SetTimer()�� ���鼭 Ȯ�� �������� ��Ҵ������� �״������ Ȯ���ϱ�
}


void CMFCApplication2View::OnBnClickedButton5()
{
	TRACE(_T("OnBnClickedButton5\n"));
}



void CMFCApplication2View::HandleThread()
{
	 //TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_Thread.bRun == TRUE)
	{
		m_Thread.bRun = FALSE;//������
	}
	else {
		m_Thread.pThread = AfxBeginThread(ThreadVelo, this);
		if (m_Thread.pThread != NULL){
			m_Thread.bRun = TRUE;//������
			m_Thread.pThread->m_bAutoDelete = FALSE;
		}
		else {
			m_Thread.bRun = FALSE;//������
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
	m_Chart.SetBarInterSpace(CRANE_MAX);//����, ��
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
		m_Chart.pBarSeries[cr]->SetName(strSerieName[cr]);//����, ��
		//m_Chart.pLineSeries[cr]->SetName(strSerieName[cr]);//����, ��
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
