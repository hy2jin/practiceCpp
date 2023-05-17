
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ChatS.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
#include "ChatSDlg.h"
#include <locale.h>

CString GetThisPath()
{
	if (!thisPath.GetLength())
	{
		TCHAR szPath[1024];
		GetModuleFileName(NULL, szPath, 1024);

		thisPath.Format(_T("%s"), szPath);
		thisPath = thisPath.Left(thisPath.ReverseFind('\\') + 1);
	}

	return thisPath;
}


void CreateLogFolder()
{
	CString logFolderPath = thisPath + _T("Log");
	if (GetFileAttributes((LPCTSTR)logFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(logFolderPath, NULL);
	}

	serverLogFolderPath = thisPath + _T("Log\\server");
	if (GetFileAttributes((LPCTSTR)serverLogFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(serverLogFolderPath, NULL);
	}

	clientLogFolderPath = thisPath + _T("Log\\client");
	if (GetFileAttributes((LPCTSTR)clientLogFolderPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(clientLogFolderPath, NULL);
	}
}


CString GetLogFileName()
{
	DeleteOldFiles(serverLogFolderPath, 30);
	DeleteOldFiles(clientLogFolderPath, 30);

	SYSTEMTIME st;
	GetLocalTime(&st);

	CString logFileName;
	logFileName.Format(_T("\\%04d%02d%02d-%02d%02d.log"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);

	return logFileName;
}


void LogMsg(CString msg, CString folderPath)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString strData;
	strData.Format(_T("[%02d:%02d:%02d] %s\n"), st.wHour, st.wMinute, st.wSecond, msg);

	CString logFilePath = folderPath + GetLogFileName();

	FILE *file = NULL;
	_wfopen_s(&file, logFilePath, _T("r+"));
	if (file == NULL){
		_wfopen_s(&file, logFilePath, _T("ab"));
		if (file != NULL){
			WORD mark = 0xFEFF;
			fwrite(&mark, sizeof(WORD), 1, file);
		}
	}
	else{
		fclose(file);
		_wfopen_s(&file, logFilePath, _T("ab"));
	}
	if (file != NULL){
		fwprintf(file, strData);
		fclose(file);
	}
}




void LogMsgServer(CString msg)
{
	LogMsg(msg, serverLogFolderPath);
}


void LogMsgClient(CString msg)
{
	LogMsg(msg, clientLogFolderPath);
}



void DeleteOldFiles(CString folderPath, UINT minFlag)
{
	CFileFind finder;
	CString filePath;

	// 폴더 내의 모든 파일 검색
	BOOL bWorking = finder.FindFile(folderPath + _T("\\*.*"));

	// 현재 시간 가져오기
	CTime currentTime = CTime::GetCurrentTime();

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		// 파일인 경우에만 처리
		if (!finder.IsDirectory())
		{
			// 파일의 생성 시간 가져오기
			CTime fileCreationTime;
			finder.GetCreationTime(fileCreationTime);

			// 현재 시간과의 차이 계산 (분 단위)
			LONGLONG minutesDifference = (currentTime - fileCreationTime).GetTotalMinutes();

			// 파일이 minFlag분 이전에 생성되었다면 삭제
			if (minutesDifference > minFlag)
			{
				filePath = finder.GetFilePath();
				CFile::Remove(filePath);
			}
		}
	}

	finder.Close();
}
