#pragma once

// MyUser ��� ����Դϴ�.

class MyUser : public CSocket
{
public:
	MyUser();
	virtual ~MyUser();
	virtual void OnReceive(int nErrorCode);
};


