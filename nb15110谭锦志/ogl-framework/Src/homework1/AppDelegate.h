#pragma once
#include "../GLWindow/QWndApp.h"

class AppDelegate : public QWndApp
{
public:
	AppDelegate();
	~AppDelegate();

public:

	// ��ʼ������
	virtual BOOL InitInstance();

	// �˳�����
	virtual BOOL ExitInstance();
};