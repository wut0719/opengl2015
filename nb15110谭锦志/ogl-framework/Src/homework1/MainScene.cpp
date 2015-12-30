#include "MainScene.h"
#include "../Tools/ShaderLoader/LoadShaders.h"    // shader����
#include <math.h>

#include "../Tools/TextureLoader/TextureLoader.h" // texture����
#include "../Tools/ScreenShot/ScreenShot.h"       // ��Ļ��ͼ

#include <string>
#include "../System/System.h"					  // ϵͳ����

#define MAXTEXTURE	3													// ��������������Ŀ

// �ڴ˴������û�����:
GLfloat	ep_Angle;														// ����ת�ĽǶ�
GLfloat	es_Angle;														// ������ת�ĽǶ�
GLfloat	mp_Angle;														// ������ת�ĽǶ�
GLfloat	ms_Angle;														// ������ת�ĽǶ�
GLuint	texture[MAXTEXTURE];											// �������飬������������
GLUquadricObj *quadric;													// ���������������

GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// ���廷�������ɫ
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// ��������������ɫ
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };					// �����Դ��λ��

MainScene::MainScene()
{
	m_texLoader = NULL;
	m_screenShot = NULL;
}

MainScene::~MainScene()
{
	if ( NULL != m_texLoader) {
		m_texLoader = NULL;
	}
	if (NULL != m_screenShot) {
		m_screenShot = NULL;
	}
}

// ��ʾģʽ
void MainScene::ViewMode()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// ͸��ģʽ
	// �˴�width��height��Ҫǿ��ת��Ϊfloat �� ��ΪGLWindow�н��䶨��ΪGLsizei����ǿת��������opengl�ӿ�
	gluPerspective(45.0f, (float)this->GetWidth() / (float)this->GetHeight(), 0.01f, 100.0f);

	// �����λ��
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); 

	// ѡ��ģʽ�۲����
	glMatrixMode(GL_MODELVIEW); 

	glLoadIdentity();
}

BOOL MainScene::initGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);

	// ѡ����Ȳ��Է�
	glDepthFunc(GL_LEQUAL);

	// ������ȼ��
	glEnable(GL_DEPTH_TEST);
	
	glShadeModel(GL_SMOOTH);

	// �ϸ��͸�Ӽ���
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 

	/////////////////////////////��ʼ��////////////////////////////////////////
	
	// ��������
	texture[0] = m_texLoader->LoadBitMapTexture("bitmap/earth.bmp");
	texture[1] = m_texLoader->LoadBitMapTexture("bitmap/sun.bmp");
	texture[2] = m_texLoader->LoadBitMapTexture("bitmap/moon.bmp");

	glEnable(GL_TEXTURE_2D);								// ����2D����ӳ��

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);			// ���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);			// �����������

	quadric = gluNewQuadric();								// ����һ���������ָ��
	gluQuadricTexture(quadric, GLU_TRUE);					// ������������
	gluQuadricDrawStyle(quadric, GLU_FILL);					// �������
	glEnable(GL_LIGHTING);									// �򿪹���
	glEnable(GL_LIGHT1);									// �򿪹�Դ1
	
	//////////////////////////////////////////////////////////////////////////
	return TRUE;
}

BOOL MainScene::DrawGL(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // �����ɫ����Ȼ���
	glLoadIdentity(); // ���õ�ǰ����
	///////////////////////////////����////////////////////////////////////////
	
	glTranslatef(0.0f, 0.0f, -5.0f);						// ������ϵ������Ļ8.0f
	glRotatef(10, 1.0f, 0.0f, 0.0f);						// ������ϵ��x����ת10��
	glEnable(GL_LIGHT0);									// �򿪹�Դ0

/**********************************����̫��*************************************************/

	glBindTexture(GL_TEXTURE_2D, texture[1]);				// ������
	
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);		// ���ù�Դ1�ĵ�ǰλ��
	glEnable(GL_TEXTURE_2D);

	gluSphere(quadric, 0.6f, 32, 32);						// ����̫������

/**********************************���Ƶ���*************************************************/

	glDisable(GL_LIGHT0);
	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);					// ������ϵ��Y����תep_Angle�Ƕ�  ���Ƶ���ת
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);					// ������ϵ��X����ת-90��

	glEnable(GL_TEXTURE_2D);								// ��������

	glTranslatef(2.2f, 0.0f, 0.0f);							// ������ϵ����2.0f
	glBindTexture(GL_TEXTURE_2D, texture[0]);				// ������
	glPushMatrix();											// ��ǰģ����ͼ������ջ
	glRotatef(es_Angle, 0.0f, 0.0f, 1.0f);					// ������ϵ��Z����תes_Angle�Ƕ�  ���Ƶ�����ת
	gluSphere(quadric, 0.35f, 32, 32);						// ��������
	glPopMatrix();											// ��ǰģ����ͼ�����ջ

/**********************************��������*************************************************/

	glRotatef(mp_Angle, 0.0f, 0.0f, 1.0f);					// ������ϵ��Z����תmp_Angle�Ƕ� ����������ת
	glBindTexture(GL_TEXTURE_2D, texture[2]);				// ������
	glTranslatef(0.5f, 0.0f, 0.0f);							// ����0.5f
	glRotatef(ms_Angle, 0.0f, 0.0f, 1.0f);					// ������ϵ��Z����תms_Angle�Ƕ� ����������ת
	gluSphere(quadric, 0.1, 32, 32);						// ������������

/**********************************��������*************************************************/
	ep_Angle += 1.5f;  
	mp_Angle += 8.0f;
	es_Angle += 3.0f;
	ms_Angle += 7.0f;
	
	//////////////////////////////////////////////////////////////////////////

	glFlush(); // ˢ��GL�������
	return TRUE;
}

BOOL MainScene::UpdateGL(GLvoid)
{
	/* 
	* ϵͳ����ӳ��˵��
	* F1->F12     : VK_F1 -> VK_F12
	* num 0 -> 9  : VK_NUMPAD0 -> VK_NUMPAD9
	* char A -> Z : 0x41 -> ... ���� 
	*/

	if (keyDown(VK_F1))  // ����F1 ����������Ϊbmp
	{
		m_screenShot->GrabScreen(this);
	}

	return TRUE;
}

GLvoid MainScene::DestroyGL(GLvoid)
{

}

