#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl/glut.h"

static double firstYear = 0, firstDay = 0, startYear = 0; //��һ������
static double lunaDay = 0, lunaMonth = 0; //����
static double secYear = 0, secDay = 0; //�ڶ�������
static double thdYear = 0, thdDay = 0; //����������
static double thdSatelliteYear = 0, thdSatelliteDay = 0; //���������ǵ�����
static double forthYear = 0,forthDay = 0; //���ĸ�����

void initialize(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//�滭̫��
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	//̫����ת
	glRotatef((GLfloat)firstYear, 0.0, 1.0, 0.0);
	glutWireSphere(1.01, 20, 16);
	glPopMatrix();

	//���Ƶ�һ������
	glPushMatrix();
	//���ǹ�ת
	glRotatef((GLfloat)firstYear, 0.0, 1.0, 0.0);
	glTranslatef(3.0, 0.0, 0.0);
	glColor3f(0.0, 0.5, 0.5);
	//������ת
	glRotatef((GLfloat)firstDay, 0.0, 1.0, 0.0);
	glutWireSphere(0.3, 10, 8);

	//���Ƶ�һ�����ǵ����ǹ��
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	glutSolidTorus(0.005, 1.0, 10, 64);
	glPopMatrix();

	//�滭��һ�����ǵ�����
	glPushMatrix();
	glRotatef((GLfloat)lunaMonth, 0.0, 1.0, 0.0);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)lunaDay, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.6, 0.5);
	glutWireSphere(0.2, 10, 8);
	glPopMatrix();
	glPopMatrix();

	//���Ƶ�һ�����ǹ��
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	glutSolidTorus(0.005, 3.0, 10, 64);
	glPopMatrix();

	//���Ƶڶ������ǹ��
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	glutSolidTorus(0.005, 5.0, 10, 64);
	glPopMatrix();

	//���Ƶڶ�������
	glPushMatrix();
	//���ǹ�ת
	glRotatef((GLfloat)secYear, 0.0, 1.0, 0.0);
	glTranslatef(5.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	//������ת
	glRotatef((GLfloat)secDay, 0.0, 1.0, 0.0);
	glutWireSphere(0.35, 10, 8);
	glPopMatrix();

	//���Ƶ��������ǹ��
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	glutSolidTorus(0.005, 7.0, 10, 64);
	glPopMatrix();

	//���Ƶ���������
	glPushMatrix();
	//���ǹ�ת
	glRotatef((GLfloat)thdYear, 0.0, 1.0, 0.0);
	glTranslatef(7.0, 0.0, 0.0);
	glColor3f(0.5, 0.5, 1.0);
	//������ת
	glRotatef((GLfloat)thdDay, 0.0, 1.0, 0.0);
	glutWireSphere(0.45, 10, 8);

	//���Ƶ��������ǵ����ǹ��
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	//����������תӰ��
	glRotatef(-(GLfloat)thdDay, 0.0, 1.0, 0.0);
	glRotatef(90.0f, 1.0, 1.0, 0.0);
	glutSolidTorus(0.005, 0.8, 10, 64);


	//���Ƶ��������ǵ�����
	glRotatef(-(GLfloat)thdSatelliteYear, 0.0, 0.0, 1.0);
	glTranslatef(0.8, 0.0, 0.0);
	glRotatef((GLfloat)thdSatelliteDay, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.3, 0.2);
	glutWireSphere(0.2, 10, 8);
	glPopMatrix();
	glPopMatrix();


	//���Ƶ��Ŀ����ǹ��
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	glutSolidTorus(0.005, 11.0, 10, 64);
	glPopMatrix();

	//���Ƶ��Ŀ�����
	glPushMatrix();
	//���ǹ�ת
	glRotatef((GLfloat)forthYear, 0.0, 1.0, 0.0);
	glTranslatef(11.0, 0.0, 0.0);
	glColor3f(0.0, 0.5, 0.5);
	//������ת
	glRotatef((GLfloat)forthDay, 0.0, 1.0, 0.0);
	glutWireSphere(0.60, 10, 8);
	glPopMatrix();
	glutSwapBuffers();
}


//�ػ�ͼ��
void reDraw(int width,int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 15.0, 15.0, 0.0, -10.0, 0.0, 0.0, 1.0, -1.0);
}

//��ʼ����������
void idleness()
{
	lunaDay = lunaDay + 0.4;
	if (lunaDay >= 360)
	{
		lunaDay -= 360;
	}
	lunaMonth = lunaMonth + 0.3;
	if (lunaMonth >= 360)
	{
		lunaMonth -= 360;
	}
	firstDay = firstDay + 0.2;
	if (firstDay >= 360)
	{
		firstDay -= 360;
	}
	firstYear = firstYear + 0.1;
	if (firstDay >= 360)
	{
		firstYear -= 360;
	}
	startYear = startYear + 0.02;
	if (startYear >= 360)
	{
		startYear -= 360;
	}
	secDay += 0.15;
	if (secDay>=360)
	{
		secDay -= 360;
	}
	secYear += 0.03;
	if (secYear>=360)
	{
		secYear -= 360;
	}
	thdDay += 0.1;
	if (thdDay>=360)
	{
		thdDay -= 360;
	}
	thdYear += 0.02;
	if (thdYear>=360)
	{
		thdYear -= 360;
	}
	thdSatelliteYear += 0.25;
	if (thdSatelliteYear>=360)
	{
		thdSatelliteYear -= 360;
	}
	thdSatelliteDay += 0.2;
	if (thdSatelliteDay>=360)
	{
		thdSatelliteDay -= 360;
	}

	forthDay += 0.10;
	if (forthDay>=360)
	{
		forthDay -= 360;
	}
	forthYear += 0.01;
	if (forthYear>=360)
	{
		forthYear -= 360;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initialize();
	glutDisplayFunc(display);
	glutReshapeFunc(reDraw);
	glutIdleFunc(idleness);
	glutMainLoop();
	return 0;
}