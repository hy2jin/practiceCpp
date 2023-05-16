
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ChatS.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

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


void HandleCreateLogFolder()
{
	CString logFolderPath = HandleGetThisPath() + _T("Log\\server");
	if (GetFileAttributes((LPCTSTR)logFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(logFolderPath, NULL);
	}
	logFolderPath = HandleGetThisPath() + _T("Log\\client");
	if (GetFileAttributes((LPCTSTR)logFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(logFolderPath, NULL);
	}

	HandleGetLogFileName();
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
		currentTime.Format(_T("%04d-%02d-%02d[%02d:%02d]"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
	}

	return currentTime;
}


void HandleGetLogFileName()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	serverLogFile.Format(_T("%sLog\\server\\%s.log"), HandleGetThisPath(), HandleGetCurrentTime(TRUE));
	clientLogFile.Format(_T("%sLog\\client\\%s.log"), HandleGetThisPath(), HandleGetCurrentTime(TRUE));
}


void LogMsg(CString msg, CString logFileName)
{
	CStdioFile logFile;
	if (logFile.Open(logFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite, NULL))
	{
		logFile.SeekToEnd();  // 로그 파일의 끝으로 이동
		CStringW logMsg;
		logMsg.Format(L"%s %s \n", HandleGetCurrentTime(), msg);
		logFile.WriteString(logMsg);

		logFile.Close();
	}
}


void LogMsgServer(CString msg)
{
	LogMsg(msg, serverLogFile);
}

void LogMsgClient(CString msg)
{
	LogMsg(msg, clientLogFile);
}