
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// ChatS.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"


CString GetThisPath() {
	CString strThisPath;
	TCHAR szPath[1024];
	GetModuleFileName(NULL, szPath, 1024);

	strThisPath.Format(_T("%s"), szPath);
	strThisPath = strThisPath.Left(strThisPath.ReverseFind('\\') + 1);
	return strThisPath;
}