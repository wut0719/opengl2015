#include "AppDelegate.h"
#include "MainScene.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

BOOL AppDelegate::InitInstance()
{
	MainScene *pMainWnd = new MainScene();
	if (NULL == pMainWnd)
	{
		return 0; // ���ڴ���ʧ��
	}
	m_pMainWnd = (LPVOID)pMainWnd;  // ��������

	pMainWnd->CreateGlWnd("ogl-framework", 200, 100, 800, 600); 
	pMainWnd->ShowWindow(SW_SHOW);
	pMainWnd->UpdateWindow();

	return TRUE;
}

BOOL AppDelegate::ExitInstance()
{
	if (m_pMainWnd)
	{
		delete m_pMainWnd;  // �˳�ǰ����
		m_pMainWnd = NULL;
	}
	return true;
}

