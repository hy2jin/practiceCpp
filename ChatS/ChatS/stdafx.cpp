
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

	// ���� ���� ��� ���� �˻�
	BOOL bWorking = finder.FindFile(folderPath + _T("\\*.*"));

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
