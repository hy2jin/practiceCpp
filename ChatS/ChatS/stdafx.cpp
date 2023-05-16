
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ChatS.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
#include "ChatSDlg.h"
#include <locale.h>

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
	CString logFolderPath = HandleGetThisPath() + L"Log";
	if (GetFileAttributes((LPCTSTR)logFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(logFolderPath, NULL);
	}
	logFolderPath = HandleGetThisPath() + L"Log\\server";
	if (GetFileAttributes((LPCTSTR)logFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(logFolderPath, NULL);
	}
	logFolderPath = HandleGetThisPath() + L"Log\\client";
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
		currentTime.Format(_T("[%02d:%02d:%02d]"), st.wHour, st.wMinute, st.wSecond);
	}

	return currentTime;
}


void HandleGetLogFileName()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	serverLogFile.Format(L"%sLog\\server\\%s.log", HandleGetThisPath(), HandleGetCurrentTime(TRUE));
	clientLogFile.Format(L"%sLog\\client\\%s.log", HandleGetThisPath(), HandleGetCurrentTime(TRUE));
}


void LogMsg(CString msg, CString logFileName)
{
	CString strData;
	strData.Format(_T("%s %s \n"), HandleGetCurrentTime(), msg);

	FILE *file = NULL;
	_wfopen_s(&file, logFileName, _T("r+"));
	if (file == NULL){
		_wfopen_s(&file, logFileName, _T("ab"));
		if (file != NULL){
			WORD mark = 0xFEFF;
			fwrite(&mark, sizeof(WORD), 1, file);
		}
	}
	else{
		fclose(file);
		_wfopen_s(&file, logFileName, _T("ab"));
	}
	if (file != NULL){
		fwprintf(file, strData);
		fclose(file);
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