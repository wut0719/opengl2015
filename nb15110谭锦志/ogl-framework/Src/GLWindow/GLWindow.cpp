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

#include "GLWindow.h"

GLWindow::GLWindow()
{
	m_hRc = 0;
	::ZeroMemory(m_keys, sizeof(m_keys)); // ��ռ��̻���
}

GLWindow::~GLWindow()
{

}

// ����opengl����
BOOL GLWindow::CreateGlWnd(const char* title, int x, int y, int width, int height)
{
	m_width = width;
	m_height = height;

	RECT windowRect = { 0, 0, width, height };
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;   // Ԥ����ȫ��
	DWORD windowExStyle = WS_EX_APPWINDOW;     // ��չ��ʽ

	// ȫ������ - Ԥ��
	
	// ������ʽ
	windowStyle = WS_POPUP;
	windowExStyle |= WS_EX_TOPMOST;

	::AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExStyle); // ��������

	CreateEx(0, "OpenGL", title, WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL);

	if (!(m_hDc = GetDC(m_hWnd)))  // ��ȡDC
	{
		DestroyGL();		  // ����
		return FALSE;		  // ���ܻ�ȡDC
	}

	m_timerFrame = 1000;      // ��ʼ��
	

	GLuint PixelFormat;
	static PIXELFORMATDESCRIPTOR pdf = {
		sizeof(PIXELFORMATDESCRIPTOR),  // �ṹ���С
		1,					  // �汾��
		PFD_DRAW_TO_WINDOW |  // ֧�ִ���
		PFD_SUPPORT_OPENGL |  // ֧��opengl
		PFD_DOUBLEBUFFER,     // ֧��˫����
		PFD_TYPE_RGBA,        // ����RGBA��ʽ
		32,					  // ɫ�����
		0, 0, 0, 0, 0, 0,     // ���Ե�ɫ��λ
		0,					  // ��alpha����
		0,					  // ��shift Bit
		0,					  // ���ۼӻ���
		0, 0, 0, 0,			  // ���Ծۼ�λ
		24,					  // 16λZ-����
		8,					  // ���ɰ滺��
		0,					  // �޸�������
		PFD_MAIN_PLANE,		  // ����ͼ��
		0,					  // Reserved
		0, 0, 0				  // ���Բ�����
	};
	if (!(PixelFormat = ChoosePixelFormat(m_hDc, &pdf)))  // Ѱ����Ӧ���ظ�ʽ
	{
		DestroyGL();  // ����
		// printf("1====error choose====");
		return FALSE;
	}
	if (!SetPixelFormat(m_hDc, PixelFormat, &pdf))
	{
		DestroyGL();
		// printf("1====error choose====");
		return FALSE;
		// �����������ظ�ʽ
	}

	HGLRC tempContext;
	if (!(tempContext = wglCreateContext(m_hDc)))
	{
		DestroyGL();
		// printf("2====error create context====");
		return FALSE;      // ���ܻ����ɫ������
	}
	if (!wglMakeCurrent(m_hDc, tempContext))  // �����Ͱ汾opengl
	{
		DestroyGL();
		// printf("3========");
		return FALSE;      // ���ܼ��ǰopengl��Ⱦ������
	}

	if (GLEW_OK != glewInit())
	{
		DestroyGL();
		return FALSE;      // glew��ʼ��ʧ��
	}

	// ���� opengl 4.3 ֧��
	GLint attribs[] = { WGL_CONTEXT_MAJOR_VERSION_ARB,  4,  // ���汾4
		WGL_CONTEXT_MINOR_VERSION_ARB,  3,					// �ΰ汾��3
		WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,//Ҫ�󷵻ؼ���ģʽ����,�����ָ����ָ��ΪWGL_CONTEXT_CORE_PROFILE_BIT_ARB�᷵��ֻ�������Ĺ��ܵĻ���
		0 };

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hRc = wglCreateContextAttribsARB(m_hDc, 0, attribs);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);
		int result = wglMakeCurrent(m_hDc, m_hRc); // ����opengl 4.3
		if (result != 1)
		{
			return FALSE;
		}
	}
	else
	{    // ��֧��opengl4.X ��ԭΪopengl 2.1
		m_hRc = tempContext;
	}
	RECT rect;		 // �ͻ�����С
	::GetClientRect(m_hWnd, &rect);
	ResizeGLScene(rect.right - rect.left, rect.bottom - rect.top);  // ����GL��Ļ (ע�⣬����ֻʹ�ÿͻ�������)

	if (!initGL())   // ��ʼ��opengl
	{
		DestroyGL();
		return FALSE;
	}

	// �趨��ʱ�� ÿ��ˢ��60��
	SetTimer(m_hWnd, m_timerFrame, 1000 / 60, NULL);

	return TRUE;
}

HRESULT GLWindow::OnClose(WPARAM wParam, LPARAM lParam)
{
	return DestroyWindow();
}

LRESULT GLWindow::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	DestroyGL();     // �˳�����ǰ����opengl
	PostQuitMessage(0);
	return 0;
}

GLvoid GLWindow::ResizeGLScene(GLsizei width, GLsizei height)
{
	if (0 == height)
	{
		height = 1;  // ��ֹ��0��
	}
	m_width = width;
	m_height = height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);  
	ViewMode();      // ������ʾģʽ
}

BOOL GLWindow::initGL(GLvoid)
{
	return TRUE;
}

BOOL GLWindow::DrawGL(GLvoid)
{
	return TRUE;
}

BOOL GLWindow::UpdateGL(GLvoid)
{
	return TRUE;
}

GLvoid GLWindow::DestroyGL(GLvoid)
{
	// ע����ʱ��
	::KillTimer(m_hWnd, m_timerFrame);

	if (m_hRc)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			// �ͷ�DC��RCʧ��
		}
		if (!wglDeleteContext(m_hRc))
		{
			// �ͷ�RCʧ��
		}
		m_hRc = NULL;
	}
	if (m_hDc && !ReleaseDC(m_hWnd, m_hDc))
	{
		// �ͷ�DCʧ��
		m_hDc = NULL;
	}
	if (m_hWnd && !DestroyWindow())
	{
		// �ͷŴ��ھ��ʧ��
		m_hWnd = NULL;
	}
}

void GLWindow::ViewMode()
{

}

GLsizei GLWindow::GetWidth()
{
	return m_width;
}

GLsizei GLWindow::GetHeight()
{
	return m_height;
}

BOOL GLWindow::keyDown(int key)
{
	return m_keys[key] == TRUE ? TRUE : FALSE;
}

HRESULT GLWindow::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= 0 && wParam < 256)
	{
		m_keys[wParam] = TRUE;
	}
	return 0;
}

HRESULT GLWindow::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= 0 && wParam < 256)
	{
		m_keys[wParam] = FALSE;
	}
	return 0;
}

HRESULT GLWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
	ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
	return 0;
}

HRESULT GLWindow::OnTimer(WPARAM wParam, LPARAM lParam)
{
	UpdateGL();  // ��Ϣ����:���̵�
	return ::InvalidateRect(m_hWnd, NULL, FALSE); // ʹ����ʧЧ
}

HRESULT GLWindow::OnPaint(WPARAM wParam, LPARAM lParam)
{
	DrawGL();						// ����opengl����
	SwapBuffers(m_hDc);				// ��������
	::ValidateRect(m_hWnd, NULL);   // ʹ������Ч
	return TRUE;
}


