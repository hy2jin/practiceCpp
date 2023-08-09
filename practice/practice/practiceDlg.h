
// practiceDlg.h : ��� ����
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


// CpracticeDlg ��ȭ ����
class CpracticeDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CpracticeDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PRACTICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

public:
	enum{
		COUNT_PEOPLE = 2,

	};
	CArray<CPerson> m_people[COUNT_PEOPLE];
	CArray<CPerson> *pPerson;
	CListBox m_list;

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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

