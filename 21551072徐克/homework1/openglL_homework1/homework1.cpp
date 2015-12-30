#include <iostream>
#include <glut.h>

using namespace std;

static GLfloat sunRevolute   = 0.0f;	//̫���Դ�����
static GLfloat earthRevolute = 0.0f;	//�����Դ�����
static GLfloat earthRotate   = 200.0f;	//����ת����
static GLfloat moonRevolute  = 0.0f;	//�����Դ�����
static GLfloat moonRotate    = 10.0f;	//����ת����

void myDisplay(void){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75,1,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-25,0,0,0,0,1,0);

	//����̫����Դ
	GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// ����̫���Ĳ���
	GLfloat sun_mat_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_diffuse[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_emission[] = {0.3f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);

	//����̫��
	glPushMatrix();
	glRotatef(sunRevolute/30.0*360.0, 0.0f, 0.0f, -1.0f);	//̫����ת������30��
	glutSolidSphere(4.0,20,20);
	glPopMatrix();

	//����������
	GLfloat earth_mat_ambient[] = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat earth_mat_diffuse[] = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat earth_mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
	
	glPushMatrix();
	glRotatef(earthRotate/360.0*360.0,0.0f,0.0f,-1.0f);	//����ת������360��
	glTranslatef(14.0f,0.0f,0.0f);
	glRotatef(earthRevolute/1.0f*360.0, 0.0f, 0.0f, -1.0f);	//������ת������1��
	glutSolidSphere(2.0,15,15); 	

	//�����������
	GLfloat moon_mat_ambient[] = {0.5f, 0.5f, 0.0f, 1.0f};
	GLfloat moon_mat_diffuse[] = {0.5f, 0.5f, 0.0f, 1.0f};
	GLfloat moon_mat_specular[] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat moon_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat moon_mat_shininess = 50.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, moon_mat_shininess);
	
	glPushMatrix();
	glRotatef(moonRotate/27.0*360.0-earthRotate/360.0*360.0+earthRevolute/1.0f*360.0, 0.0f, 0.0f, 1.0f);	//����ת������27��
	glTranslatef(5.0f,0.0f,0.0f);
	glRotatef(moonRevolute/27.0f*360.0, 0.0f, 0.0f, 1.0f);	//�����Դ�������27��
	glutSolidSphere(1.0,10,10);
	glPopMatrix();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
		2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
		2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
	sunRevolute+=0.01f;
	if (sunRevolute>=30.0f)
	{
		sunRevolute -= 30.0f;
	}

	earthRevolute+=0.01f;
	if (earthRevolute>=1.0f)
	{
		earthRevolute-=1.0f;
	}

	earthRotate+=0.01f;
	if(earthRotate>=360.0f)
	{
		earthRotate -= 360.0f;
	}

	moonRotate+=0.01f;
	if(moonRotate>=27.0f)
	{
		moonRotate -= 27.0f;
	}

	moonRevolute+=0.01f;
	if(moonRevolute>=27.0f)
	{
		moonRevolute -=27.0f;
	}
	myDisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(500,100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("homework1");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(renderScene);
	glEnable(GL_DEPTH_TEST); 
    glutMainLoop();
	return 0;
}