#pragma once

#include "MyUser.h"
// MyServer 명령 대상입니다.

class MyServer : public CSocket
{
private:
	MyUser m_user;

public:
	MyServer();
	virtual ~MyServer();
	virtual void OnAccept(int nErrorCode);
};


