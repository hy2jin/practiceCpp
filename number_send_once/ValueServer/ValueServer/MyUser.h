#pragma once

// MyUser 명령 대상입니다.

class MyUser : public CSocket
{
public:
	MyUser();
	virtual ~MyUser();
	virtual void OnReceive(int nErrorCode);
};


