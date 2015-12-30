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

#pragma once
#include "QWnd.h"

class GLWindow : public QWnd
{
public:
	GLWindow();
	~GLWindow();

	BOOL CreateGlWnd(const char* title, int x, int y, int width, int height);

	HRESULT OnClose(WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);

	// �ı�opengl���ڴ�С
	GLvoid ResizeGLScene(GLsizei width, GLsizei height);

	// �ṩ�����opengl�ĳ�ʼ������
	virtual BOOL initGL(GLvoid);

	// �ṩ����opengl���ƺ���
	virtual BOOL DrawGL(GLvoid);

	virtual BOOL UpdateGL(GLvoid);

	// �ṩ�����opengl����ʱ�Ĵ���
	virtual GLvoid DestroyGL(GLvoid);

	virtual void ViewMode();

	GLsizei GetWidth();
	GLsizei GetHeight();

	BOOL keyDown(int key);  // ��ʱ����keyUp�ķ�װ

	virtual HRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnKeyUp(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnSize(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	virtual HRESULT OnPaint(WPARAM wParam, LPARAM lParam);

private:
	HGLRC m_hRc;		 // ������ɫ��������
	HDC   m_hDc;		 // opengl��Ⱦ�������
	BOOL  m_keys[256];   // ������̰�������
	GLuint m_timerFrame; // ��ͼ��ʱ��
	GLsizei m_width;
	GLsizei m_height;
};