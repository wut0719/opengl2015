#include <gl/glut.h>
#include <cmath>
static int year = 0, month = 0, day = 0;
static float self_rot = 0;

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);  //�����ɫ������
	glPushMatrix();  //ѹջ
	glColor3f(1, 0, 0);   //���ú�ɫ��ͼ
	glRotatef(self_rot, 0, 1, 0);
	glutWireSphere(1, 20, 16);   //����̫��

	glColor3f(0, 0, 1);   //������ɫ��ͼ
	float angle = 0;
	int splitNum = 100;//����100��ֱ����ģ��Բ
	float step = 2 * 3.14 / splitNum;//ÿ�����ӵĽǶ�
	glBegin(GL_LINE_LOOP);
	for (angle = 0; angle < 2 * 3.14; angle += step)
		glVertex3f(3*sin(angle), 0.0, 3*cos(angle));
	glEnd();
	
	glRotatef((GLfloat)year, 0, 1, 0);  //��y����ת 
	glTranslatef(3, 0, 0); //�������е�������x���������ƶ�3����λ��
	
	glRotatef((GLfloat)day, 0, 1, 0);  //��y����ת
	
	glutWireSphere(0.3, 10, 8);   //���Ƶ���

	glColor3f(1, 1, 1);   //���ð�ɫ��ͼ
	angle = 0;
	splitNum = 100;//����100��ֱ����ģ��Բ
	step = 2 * 3.14 / splitNum;//ÿ�����ӵĽǶ�
	glBegin(GL_LINE_LOOP);
	for (angle = 0; angle < 2 * 3.14; angle += step)
		glVertex3f(sin(angle), 0.0, cos(angle));
	glEnd();
	glRotatef((GLfloat)month, 0, 1, 0);

	glTranslatef(1, 0, 0); //�������е�������x���������ƶ�1����λ��
	glRotatef((GLfloat)day, 0, 1, 0);  //��y����ת
	glColor3f(1, 1, 1);   //���ð�ɫ��ͼ
	glutWireSphere(0.15, 10, 8);//��������

	
	glPopMatrix(); //��ջ

	glutSwapBuffers();
	glFlush();   //ˢ�´�������ʾ��ǰ����ͼ��
}


void init(void)
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT); //ѡ��ƽ������ģʽ��⻬����ģʽ
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);   //���û���
	glMatrixMode(GL_PROJECTION);  //ָ����һ�������ǵ�ǰ����
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20);   //����͸��ͶӰ����(fovy,aspect,zNear,zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glFrustum(-1,1,-1,1,1.5,20.0);  //��͸�Ӿ�����Ե�ǰ����(left,Right,bottom,top,near,far);

	gluLookAt(0, 5, 5, 0, 0, 0, 0, 1, 0);
}

void changeAngle(int id)
{
	year = (year + 2) % 360;
	month = (month + 2) % 360;
	day = (day + 2) % 360;
	self_rot = self_rot + 0.5;
	if (self_rot >= 360)
		self_rot = 0;
	glutPostRedisplay();
	glutTimerFunc(33, changeAngle, 1);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv); //�̶���ʽ
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //����ģʽ
	glutInitWindowSize(960, 640);    //��ʾ��Ĵ�С
	glutInitWindowPosition(0, 0); //ȷ����ʾ�����Ͻǵ�λ��
	glutCreateWindow("Glut����̫��ϵ");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(33, changeAngle, 1);//��33�����һ�θı�ǶȺ���
	glutMainLoop(); //����GLUT�¼�����ѭ��
	return 0;
}


