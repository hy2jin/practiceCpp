
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// ChatS.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

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

	serverLogPath = thisPath + _T("Log\\server");
	if (GetFileAttributes((LPCTSTR)serverLogPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(serverLogPath, NULL);
	}

	clientLogPath = thisPath + _T("Log\\client");
	if (GetFileAttributes((LPCTSTR)clientLogPath) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectory(clientLogPath, NULL);
	}
}


CString GetLogFileName()
{
	DeleteOldFiles(serverLogPath, 60);
	DeleteOldFiles(clientLogPath, 60);

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

	CString logFileName = folderPath + GetLogFileName();

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
	LogMsg(msg, serverLogPath);
}


void LogMsgClient(CString msg)
{
	LogMsg(msg, clientLogPath);
}



void DeleteOldFiles(CString logPath, UINT minFlag)
{
	CFileFind finder;
	CString filePath;

	// ���� ���� ��� ���� �˻�
	BOOL bWorking = finder.FindFile(logPath + _T("\\*.*"));

	// ���� �ð� ��������
	CTime currentTime = CTime::GetCurrentTime();

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		// ������ ��쿡�� ó��
		if (!finder.IsDirectory())
		{
			// ������ ���� �ð� ��������
			CTime fileCreationTime;
			finder.GetCreationTime(fileCreationTime);

			// ���� �ð����� ���� ��� (�� ����)
			LONGLONG minutesDifference = (currentTime - fileCreationTime).GetTotalMinutes();

			// ������ minFlag�� ������ �����Ǿ��ٸ� ����
			if (minutesDifference > minFlag)
			{
				filePath = finder.GetFilePath();
				CFile::Remove(filePath);
			}
		}
	}

	finder.Close();
}
