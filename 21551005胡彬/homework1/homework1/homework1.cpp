// homework1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"  
#include <GL/glut.h>

// ̫�������������
// ����ÿ���¶��� 30 ��
// һ�� 12 ���£����� 360 ��
static int day = 200; //day�ĳ�ʼֵ�� day �ı仯���� 0 �� 359
void myDisplay(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 40000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -23000000, 23000000, 0, 0, 0, 0, 0, 1);
	// ���ƺ�ɫ�ġ�̫����
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(6960000, 15000,15000);
	// ������ɫ�ġ�����
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(15000000, 0.0f, 0.0f);
	glutSolidSphere(1594500, 15000,15000);
	// ���ƻ�ɫ�ġ�������
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(3800000, 0.0f, 0.0f);
	glutSolidSphere(434500, 15000, 15000);
	glFlush();
	glutSwapBuffers();
}

void myIdle(void)
{
	/* �µĺ������ڿ���ʱ���ã������ǰ����������ƶ�һ�첢���»��ƣ��ﵽ����Ч�� */
	++day;
	if (day >= 360)
		day = 0;
	myDisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // �޸��˲���Ϊ GLUT_DOUBLE
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("̫�������������"); // ���˴��ڱ���
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle); 
	glutMainLoop();
	return 0;
}

