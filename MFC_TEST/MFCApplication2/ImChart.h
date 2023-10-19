#pragma once


// CImChart

#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartBarSerie.h"

class CImChart : public CWnd
{
	DECLARE_DYNAMIC(CImChart)

public:
	CImChart();
	virtual ~CImChart();
	enum {
		MAX_BOTTOM_COUNT = 31,
		CRANE_MAX = 3,
	};

	CChartCtrl m_ChartCtrl;
	CChartAxis* GetBottomAxis() const { return m_ChartCtrl.GetBottomAxis(); }

	void HandleLegend();

	void HandleLabel(CChartAxis* pAxis);
	void HandleLabel(CChartAxis* pAxis, CString *Str, int StrCount);
	void HandleLabel(CChartAxis* pAxis, CStringArray &Str);

	void SetDrawAsCell(CChartAxis* pAxis, bool drawAsCell = true);

	void ResetMaxY() { m_MaxY = 0; }
	void Refresh() { m_ChartCtrl.RefreshCtrl(); };

protected:
	BOOL isMakeChart;
	int m_Width;
	double m_MaxY;
	void MakeChart();
	void Init_Chart();

protected:
	DECLARE_MESSAGE_MAP()

};


//////////////////////// CImBarChart

class CImBarChart : public CImChart
{
	DECLARE_DYNAMIC(CImBarChart)

public:
	CImBarChart();
	virtual ~CImBarChart();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CChartBarSerie* pBarSeries[CRANE_MAX];

	void Init_Chart();
	void Draw_Chart(int Line, double* pY, int Count);
	void SetAxisMinMax(CChartAxis* pAxis, int MaxCnt, int MinCnt = 0);
	void SetYValue(int Line, unsigned xIndex, double newVal);
	void SetBarInterSpace(int BarCount);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


//////////////////////// CImLineChart

class CImLineChart : public CImChart
{
	DECLARE_DYNAMIC(CImLineChart)

public:
	CImLineChart();
	virtual ~CImLineChart();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CChartLineSerie* pLineSeries[CRANE_MAX];

	void Init_Chart();
	void Draw_Chart(int Line, double* pY, int Count);
	void SetAxisMinMax(CChartAxis* pAxis, int MaxCnt, int MinCnt = 0);
	void SetYValue(int Line, unsigned xIndex, double newVal);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};