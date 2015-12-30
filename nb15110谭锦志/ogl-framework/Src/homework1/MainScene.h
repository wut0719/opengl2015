#pragma once
#include "../GLWindow/GLWindow.h"  // ʹ��GLWindow �� ����win32��װ�Ĵ���Ӧ�����

class TextureLoader;
class ScreenShot;

class MainScene : public GLWindow
{
public:
	MainScene();
	~MainScene();

	// ��ʼ��
	BOOL initGL(GLvoid) override;

	// ��ʾģʽ
	void ViewMode() override;

	// ���Ƴ���
	BOOL DrawGL(GLvoid) override;

	// ���´�����Ϣ
	BOOL UpdateGL(GLvoid) override;

	// opengl��������ǰ�Ĵ���
	GLvoid DestroyGL(GLvoid) override;

private:
	TextureLoader *m_texLoader;  // ������ع���
	ScreenShot *m_screenShot;	 // ��Ļ��ͼ����
};