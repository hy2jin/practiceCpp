
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// ChatS.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"
#include "ChatSDlg.h"

CString GetThisPath()
{
	CString strThisPath;
	TCHAR szPath[1024];
	GetModuleFileName(NULL, szPath, 1024);

	strThisPath.Format(_T("%s"), szPath);
	strThisPath = strThisPath.Left(strThisPath.ReverseFind('\\') + 1);
	return strThisPath;
}

CString GetDateTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString strDate;
	strDate.Format(_T("%04d%02d%02d_%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);

	return strDate;
}

CString GetLogPath()
{
	CString strFileName = GetThisPath() + _T("\Log");
	return strFileName;
}

void CreateLogFolder()
{
	CString logFolderPath = GetLogPath();

	if (GetFileAttributes((LPCTSTR)logFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(logFolderPath, NULL);
	}
	else
	{
		return;
	}
}