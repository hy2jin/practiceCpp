// ImChart.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImChart.h"


// CImChart

IMPLEMENT_DYNAMIC(CImChart, CWnd)

CImChart::CImChart()
{
	isMakeChart = FALSE;
}

CImChart::~CImChart()
{
}

BEGIN_MESSAGE_MAP(CImChart, CWnd)
END_MESSAGE_MAP()


// CImChart �޽��� ó�����Դϴ�.


void CImChart::MakeChart()
{
	CChartStandardAxis* pBottomAxis;
	CChartStandardAxis* pLeftAxis;

	if (!isMakeChart)
	{
		CRect m_Rect;
		GetClientRect(&m_Rect);
		isMakeChart = m_ChartCtrl.Create(this, m_Rect, 1000, 0x52010000);//0x52010000
		pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
		pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	}

	pBottomAxis = (CChartStandardAxis*)m_ChartCtrl.GetBottomAxis();
	pLeftAxis = (CChartStandardAxis*)m_ChartCtrl.GetLeftAxis();

	pLeftAxis->SetAutomaticMode(CChartAxis::FullAutomatic);
	pBottomAxis->SetAutomaticMode(CChartAxis::FullAutomatic);
	//pBottomAxis->SetAutomaticMode(CChartAxis::NotAutomatic);
	//pBottomAxis->SetMinMax(0, 17);

	pBottomAxis->SetTickIncrement(false, 1);	// ����
	//pBottomAxis->SetDiscrete(true);				//��(false), ĭ(true)
	SetDrawAsCell(pBottomAxis, true);
	m_ChartCtrl.ShowMouseCursor(true);
	//CChartCrossHairCursor* pCrossHair = m_ChartCtrl.CreateCrossHairCursor();
	m_ChartCtrl.SetPanEnabled(false);
	m_ChartCtrl.SetZoomEnabled(false);
	m_ChartCtrl.SetBackColor(RGB(235, 235, 235));
	m_ChartCtrl.SetBorderColor(RGB(235, 235, 235));	//������, ���� �׵θ� ����
}


void CImChart::HandleLegend()
{
	CChartLegend *pL = m_ChartCtrl.GetLegend();
	//pL->SetHorizontalMode(true);	//���� �Ѹ��
	pL->EnableShadow(false);		//�׸��� ����
	pL->SetTransparent(true);		//��� ����
	pL->DockLegend(CChartLegend::dsDockRight);	//���� ��ġ
	//pL->UndockLegend(329, 12);		//���� ��ġ ��ǥ

	pL->SetVisible(true);
}


void CImChart::HandleLabel(CChartAxis* pAxis)
{
	CString lab[50];
	for (int i = 0; i < 50; i++) {
		CString temp;
		temp.Format(_T("%04d"), i + 1);
		lab[i] = temp;
	}

	pAxis->m_RowText.RemoveAll();
	for (int la = 0; la < MAX_BOTTOM_COUNT; la++) {
		pAxis->m_RowText.Add(lab[la]);
	}
}

void CImChart::HandleLabel(CChartAxis* pAxis, CString *Str, int StrCount)
{
	pAxis->m_RowText.RemoveAll();

	for (int la = 0; la < MAX_BOTTOM_COUNT; la++) {
		if (la >= StrCount) continue;
		pAxis->m_RowText.Add(Str[la]);
	}
}

void CImChart::HandleLabel(CChartAxis* pAxis, CStringArray &Str)
{
	pAxis->m_RowText.RemoveAll();

	for (int la = 0; la < MAX_BOTTOM_COUNT; la++) {
		if (la >= Str.GetCount()) continue;
		pAxis->m_RowText.Add(Str[la]);
	}
}

void CImChart::SetDrawAsCell(CChartAxis* pAxis, bool drawAsCell)
{
	pAxis->SetDiscrete(drawAsCell);		//��(false), ĭ(true)
	pAxis->SetCellCenter(drawAsCell);	//������� �� ����(true)
}



// CImBarChart

IMPLEMENT_DYNAMIC(CImBarChart, CImChart)

CImBarChart::CImBarChart()
{
	isMakeChart = FALSE;
	m_Width = 12;
}

CImBarChart::~CImBarChart()
{
}

BEGIN_MESSAGE_MAP(CImBarChart, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CImChart �޽��� ó�����Դϴ�.

int CImBarChart::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	MakeChart();
	Init_Chart();

	return 0;
}

void CImBarChart::Init_Chart()
{
	CChartBarSerie* pSeries = NULL;

	COLORREF clr[CRANE_MAX] = { RGB(72, 134, 226), RGB(115, 223, 31), RGB(244, 189, 80) };
	COLORREF bclr[CRANE_MAX] = { RGB(49, 79, 183), RGB(21, 151, 0), RGB(235, 121, 16) };


	for (int i = 0; i < CRANE_MAX; i++)
	{
		pBarSeries[i] = m_ChartCtrl.CreateBarSerie();
		//���밡 3���� �ƴ� ��� -1�� �ƴ� -> SetBarInterSpace()�� �и�
		//pBarSeries[i]->SetInterSpace((i - 1) * m_Width);// LIMJI ����

		//pBarSeries[i]->SetInterSpace((-CRANE_MAX * BarWidth / CRANE_MAX) + i * BarWidth);// LIMJI ����
		pSeries = pBarSeries[i];
		//pBarSeries->SetWidth(3);		//������
		pSeries->SetSeriesOrdering(PointsOrdering::poNoOrdering);//���ı���? ���� ���Ѱ��� �𸣰���
		pSeries->SetBorderWidth(0);			//���� �׵θ� ����
		pSeries->SetBarWidth(m_Width);	//���� ���� 20->m_Width


		//pSeries->SetName(crName[i]);

		pSeries->SetColor(clr[i]);	//�׶��̼�ver
		pSeries->ShowGradient(true);
		pSeries->SetGradient(bclr[i], gtVertical);
	}
}

void CImBarChart::SetBarInterSpace(int BarCount)
{
	int mid = BarCount / 2;

	for (int i = 0; i < BarCount; i++)
	{
		pBarSeries[i]->SetInterSpace((i - mid) * m_Width);
	}
}


void CImBarChart::Draw_Chart(int Line, double* pY, int Count)
{
	CChartBarSerie* pSeries = NULL;

	double XVal[50];
	for (int i = 0; i < Count; i++)
	{
		XVal[i] = i;

		double y = pY[i];
		m_MaxY = y > m_MaxY ? y : m_MaxY;
	}

	pSeries = pBarSeries[Line];
	pSeries->ClearSerie();
	pSeries->SetPoints(XVal, pY, Count);

	CChartAxis* pLAxis = m_ChartCtrl.GetLeftAxis();
	pLAxis->SetMinMax(0, m_MaxY);
}

void CImBarChart::SetAxisMinMax(CChartAxis* pAxis, int MaxCnt, int MinCnt)
{
	pAxis->SetAutomaticMode(CChartAxis::NotAutomatic);
	pAxis->SetMinMax(MinCnt, MaxCnt);
}

void CImBarChart::SetYValue(int Line, unsigned xIndex, double newVal)
{
	CChartBarSerie* pSeries = NULL;
	pSeries = pBarSeries[Line];
	pSeries->SetYPointValue(xIndex, newVal);

	m_MaxY = newVal > m_MaxY ? newVal : m_MaxY;
	CChartAxis* pLAxis = m_ChartCtrl.GetLeftAxis();
	pLAxis->SetMinMax(0, m_MaxY);
}





// CImLineChart

IMPLEMENT_DYNAMIC(CImLineChart, CImChart)

CImLineChart::CImLineChart()
{
	isMakeChart = FALSE;
	m_Width = 3;
}

CImLineChart::~CImLineChart()
{
}

BEGIN_MESSAGE_MAP(CImLineChart, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CImChart �޽��� ó�����Դϴ�.

int CImLineChart::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CImChart::OnCreate(lpCreateStruct) == -1)
		return -1;

	MakeChart();
	Init_Chart();

	return 0;
}

void CImLineChart::Init_Chart()
{
	CChartLineSerie* pSeries = NULL;

	COLORREF clr[CRANE_MAX] = { RGB(72, 134, 226), RGB(115, 223, 31), RGB(244, 189, 80) };
	COLORREF bclr[CRANE_MAX] = { RGB(49, 79, 183), RGB(21, 151, 0), RGB(235, 121, 16) };
	//int lineWidth[CRANE_MAX] = { 4, 2, 2 };

	for (int i = 0; i < CRANE_MAX; i++)
	{
		pLineSeries[i] = m_ChartCtrl.CreateLineSerie();
		pSeries = pLineSeries[i];
		pLineSeries[i]->SetWidth(m_Width);		//������
		//pLineSeries[i]->SetWidth(lineWidth[i]);		//������
		pSeries->SetSeriesOrdering(PointsOrdering::poNoOrdering);//���ı���? ���� ���Ѱ��� �𸣰���
		//pSeries->SetBorderWidth(0);	//���� �׵θ� ����
		//pSeries->SetBarWidth(10);	//���� ���� 20->10

		//pSeries->SetName(crName[i]);

		pSeries->SetColor(bclr[i]);
	}
}


void CImLineChart::Draw_Chart(int Line, double* pY, int Count)
{
	CChartLineSerie* pSeries = NULL;

	double XVal[50];
	for (int i = 0; i < Count; i++)
	{
		XVal[i] = i;

		double y = pY[i];
		m_MaxY = y > m_MaxY ? y : m_MaxY;
	}
	
	pSeries = pLineSeries[Line];
	pSeries->ClearSerie();
	pSeries->SetPoints(XVal, pY, Count);

	CChartAxis* pLAxis = m_ChartCtrl.GetLeftAxis();
	pLAxis->SetMinMax(0, m_MaxY);

}

void CImLineChart::SetAxisMinMax(CChartAxis* pAxis, int MaxCnt, int MinCnt)
{
	pAxis->SetAutomaticMode(CChartAxis::NotAutomatic);
	pAxis->SetMinMax(MinCnt, MaxCnt - 1);	//LineChart ������ �����Ŵϱ� -1����
}

void CImLineChart::SetYValue(int Line, unsigned xIndex, double newVal)
{
	CChartLineSerie* pSeries = NULL;
	pSeries = pLineSeries[Line];
	pSeries->SetYPointValue(xIndex, newVal);

	m_MaxY = newVal > m_MaxY ? newVal : m_MaxY;
	CChartAxis* pLAxis = m_ChartCtrl.GetLeftAxis();
	pLAxis->SetMinMax(0, m_MaxY);
}

