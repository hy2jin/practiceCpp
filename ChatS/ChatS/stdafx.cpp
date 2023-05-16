
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// ChatS.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"
#include "ChatSDlg.h"

CString HandleGetThisPath()
{
	CString strThisPath;
	TCHAR szPath[1024];
	GetModuleFileName(NULL, szPath, 1024);

	strThisPath.Format(_T("%s"), szPath);
	strThisPath = strThisPath.Left(strThisPath.ReverseFind('\\') + 1);
	return strThisPath;
}


void HandleCreateLogFolder(CString path)
{
	CString logFolderPath = HandleGetThisPath() + _T("Log\\") + path;
	if (GetFileAttributes((LPCTSTR)logFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(logFolderPath, NULL);
	}
}


CString HandleGetCurrentTime(BOOL isFileName)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString currentTime;
	if (isFileName) {
		currentTime.Format(_T("%04d%02d%02d-%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
	}
	else {
		currentTime.Format(_T("%04d-%02d-%02d [%02d:%02d]"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
	}

	return currentTime;
}


CString HandleGetLogFileName(CString path)
{
	HandleCreateLogFolder(path);

	SYSTEMTIME st;
	GetLocalTime(&st);

	CString logFileName;
	logFileName.Format(_T("%sLog\\%s\\%s.txt"), HandleGetThisPath(), path, HandleGetCurrentTime(TRUE));

	return logFileName;
}


void LogMsg(CString msg, CString logFileName)
{
	CStdioFile logFile;
	if (logFile.Open(logFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText))
	{
		logFile.SeekToEnd();  // �α� ������ ������ �̵�
		CString tmp;
		tmp.Format(_T("%s  %s \n"), HandleGetCurrentTime(), msg);
		logFile.WriteString(tmp);

		logFile.Close();
	}
}
