
// practiceDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


class CPerson
{
public:
	CPerson(){
		reset();
	}
	virtual ~CPerson() {}
	enum {
		MAX_NUM = 3,
	};
	CString m_name;
	int m_age;
	CString m_school[MAX_NUM];

	void reset() {
		m_name.Format(_T(""));
		m_age = 0;
		for (int i = 0; i < MAX_NUM; i++) m_school[i].Format(_T(""));
	}
};


// CpracticeDlg 대화 상자
class CpracticeDlg : public CDialogEx
{
// 생성입니다.
public:
	CpracticeDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PRACTICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public:
	enum{
		COUNT_PEOPLE = 2,

	};
	CArray<CPerson> m_people[COUNT_PEOPLE];
	CArray<CPerson> *pPerson;
	CListBox m_list;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void AddPeople();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};

