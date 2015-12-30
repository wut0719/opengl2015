#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl/glut.h"

static double sunRot = 0, firstPlaRot = 0;
static double firstPlaSatRot = 0, firstPlaSatRev = 0;
static double secondPlaRot = 0, secondPlaRev = 0;
static double thirdPlaRev = 0, thirdPlaRot = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	/*̫��*/
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef((GLfloat)sunRot, 0.0, 0.0, 1.0);//̫����ת
	glutWireSphere(2, 30, 16);
	glPopMatrix();

	/*��һ�����ǹ��*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 5.0, 10, 64);
	glPopMatrix();
	/*��һ������*/
	glPushMatrix();
	glRotatef((GLfloat)sunRot, 0.0, 0.0, 1.0);//��ת
	glTranslatef(5.0, 0.0, 0.0);
	glColor3f(0.5, 0.3, 0.6);
	glRotatef((GLfloat)firstPlaRot, 0.0, 0.0, 1.0);//��ת
	glutWireSphere(0.3, 10, 8);

	/*��һ�����ǵ����ǹ��*/
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glutSolidTorus(0.005, 1.0, 10, 64);
	glPopMatrix();

	/*��һ�����ǵ�����*/
	glPushMatrix();
	glRotatef((GLfloat)firstPlaSatRev, 0.0, 0.0, 1.0);//��ת
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)firstPlaSatRot, 0.0, 0.0, 1.0);//��ת
	glColor3f(0.5, 0.6, 0.5);
	glutWireSphere(0.1, 10, 8);
	glPopMatrix();
	glPopMatrix();


	/*�ڶ������ǹ��*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 8.0, 10, 64);
	glPopMatrix();

	/*�ڶ�������*/
	glPushMatrix();
	glRotatef((GLfloat)secondPlaRev, 0.0, 0.0, 1.0);//��ת
	glTranslatef(8.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glRotatef((GLfloat)secondPlaRot, 0.0, 0.0, 1.0);//��ת
	glutWireSphere(1, 20, 10);
	glPopMatrix();

	/*���������ǹ��*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 11.0, 10, 64);
	glPopMatrix();

	/*����������*/
	glPushMatrix();
	glRotatef((GLfloat)thirdPlaRev, 0.0, 0.0, 1.0);//���ǹ�ת
	glTranslatef(11.0, 0.0, 0.0);
	glColor3f(0.36, 0.88, 0.44);
	glRotatef((GLfloat)thirdPlaRot, 0.0, 0.0, 1.0);//������ת
	glutWireSphere(0.45, 10, 8);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void resetAngle(double& angle)
{
	if (angle >= 360)
	{
		angle -= 360;
	}
}

void idle()
{
	//̫����ת����һ�����ǵĹ�ת
	sunRot += 1;
	resetAngle(sunRot);
	//��һ�����ǵ���ת
	firstPlaRot += 1.1;
	resetAngle(firstPlaRot);
	//��һ�����ǵ�������ת
	firstPlaSatRot += 0.1;
	resetAngle(firstPlaSatRot);
	//��һ�����ǵ����ǹ�ת
	firstPlaSatRev += 0.3;
	resetAngle(firstPlaSatRot);
	//�ڶ������ǵ���ת
	secondPlaRot += 1.2;
	resetAngle(secondPlaRot);
	//�ڶ������ǵĹ�ת
	secondPlaRev += 0.8;
	resetAngle(secondPlaRev);
	//���������ǵ���ת
	thirdPlaRot += 1.4;
	resetAngle(thirdPlaRot);
	//���������ǵĹ�ת
	thirdPlaRev += 0.6;
	resetAngle(thirdPlaRev);

	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutRotateFunc(rotate);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}