/*
*  author : ̷��־
*  email  : apanoo@126.com
*  time   : 2014 07 20
*  ps     : ����win32 API��װ
*			֧��win32��׼�ؼ���ȫ�Ի�
*			֧��opengl
*  �ο�    : MFCʵ�ֻ���
*  use     : �����дwindows��ͼ��Ӧ�ü����
*/

/************************************************************************/
/* Ӧ�ó������                                                           */
/************************************************************************/
#pragma once
#include "stdafx.h"

class QWndApp
{
public:
	QWndApp();
	~QWndApp();

public:
	virtual BOOL InitInstance();   // ��ʼ�� app
	virtual BOOL ExitInstance();   // �˳� app
	virtual void run();			   // ����

protected:
	LPVOID m_pMainWnd;
};
