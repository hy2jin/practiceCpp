#pragma once

#include "MyUser.h"
// MyServer ��� ����Դϴ�.

class MyServer : public CSocket
{
private:
	MyUser m_user;

public:
	MyServer();
	virtual ~MyServer();
	virtual void OnAccept(int nErrorCode);
};


