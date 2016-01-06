#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "legacy_stdio_definitions.lib")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <gl/glaux.h>
#include <gl/glut.h>

static double sunRot = 0, firstPlaRot = 0;
static double firstPlaSatRot = 0, firstPlaSatRev = 0;
static double secondPlaRot = 0, secondPlaRev = 0;
static double thirdPlaRev = 0, thirdPlaRot = 0;

GLuint		    texture[5];
GLUquadricObj	*q;
GLUquadricObj    *p;
GLUquadricObj    *t;
GLUquadricObj    *r;
GLUquadricObj    *s;
AUX_RGBImageRec *TextureImage[5];

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File = NULL;									// File Handle
	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}
	File = fopen(Filename, "r");							// Check To See If The File Exists
	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}
	return NULL;										// If Load Failed Return NULL
}

void init(void)
{
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_SMOOTH);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0f };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	q = gluNewQuadric();								  // Create A New Quadratic

	gluQuadricNormals(q, GL_SMOOTH);					  // Generate Smooth Normals For The Quad
	gluQuadricTexture(q, GL_TRUE);						  // Enable Texture Coords For The Quad

	p = gluNewQuadric();
	gluQuadricNormals(p, GL_SMOOTH);					  // Generate Smooth Normals For The Quad
	gluQuadricTexture(p, GL_TRUE);

	t = gluNewQuadric();
	gluQuadricNormals(t, GL_SMOOTH);
	gluQuadricTexture(t, GL_TRUE);

	r = gluNewQuadric();
	gluQuadricNormals(r, GL_SMOOTH);
	gluQuadricTexture(r, GL_TRUE);

	s = gluNewQuadric();
	gluQuadricNormals(r, GL_SMOOTH);
	gluQuadricTexture(r, GL_TRUE);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping

															/*******************Init Texture**************************************/

	memset(TextureImage, 0, sizeof(void *) * 1);			  // Set The Pointer To NULL

	if (TextureImage[0] = LoadBMP("DATA/jbBall.bmp"))
	{
		glGenTextures(1, &texture[0]);					  // Create The Texture

		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (TextureImage[0])						// If Texture Exists
		{
			if (TextureImage[0]->data)			// If Texture Image Exists
			{
				free(TextureImage[0]->data);		// Free The Texture Image Memory
			}

			free(TextureImage[0]);				   // Free The Image Structure 
		}
	}

	if (TextureImage[1] = LoadBMP("DATA/sun.bmp"))
	{
		glGenTextures(1, &texture[1]);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (TextureImage[1])						// If Texture Exists
		{
			if (TextureImage[1]->data)			// If Texture Image Exists
			{
				free(TextureImage[1]->data);		// Free The Texture Image Memory
			}

			free(TextureImage[1]);				   // Free The Image Structure 
		}
	}

	if (TextureImage[2] = LoadBMP("DATA/jbball2.bmp"))
	{
		glGenTextures(1, &texture[2]);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (TextureImage[2])						// If Texture Exists
		{
			if (TextureImage[2]->data)			// If Texture Image Exists
			{
				free(TextureImage[2]->data);		// Free The Texture Image Memory
			}

			free(TextureImage[2]);				   // Free The Image Structure 
		}
	}

	if (TextureImage[3] = LoadBMP("DATA/muxing.bmp"))
	{
		glGenTextures(1, &texture[3]);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->sizeX, TextureImage[3]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (TextureImage[3])						// If Texture Exists
		{
			if (TextureImage[3]->data)			// If Texture Image Exists
			{
				free(TextureImage[3]->data);		// Free The Texture Image Memory
			}

			free(TextureImage[3]);				   // Free The Image Structure 
		}
	}

	if (TextureImage[4] = LoadBMP("DATA/jbBall1.bmp"))
	{
		glGenTextures(1, &texture[4]);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[4]->sizeX, TextureImage[4]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[4]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (TextureImage[4])						// If Texture Exists
		{
			if (TextureImage[4]->data)			// If Texture Image Exists
			{
				free(TextureImage[4]->data);		// Free The Texture Image Memory
			}

			free(TextureImage[4]);				   // Free The Image Structure 
		}
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*太阳*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glColor3f(1.0, 0.0, 0.0);
	glRotatef((GLfloat)sunRot, 0.0, 0.0, 1.0);//太阳自转
	//glutWireSphere(2, 30, 16);
	gluSphere(p,2,30,16);
	glPopMatrix();

	/*第一颗行星轨道*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 5.0, 10, 64);
	glPopMatrix();
	/*第一颗行星*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glRotatef((GLfloat)sunRot, 0.0, 0.0, 1.0);//公转
	glTranslatef(5.0, 0.0, 0.0);
	//glColor3f(0.5, 0.3, 0.6);
	glRotatef((GLfloat)firstPlaRot, 0.0, 0.0, 1.0);//自转
	gluSphere(q, 0.3, 10, 8);
	//glutWireSphere(0.3, 10, 8);

	/*第一颗行星的卫星轨道*/
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glutSolidTorus(0.005, 1.0, 10, 64);
	glPopMatrix();

	/*第一颗行星的卫星*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glRotatef((GLfloat)firstPlaSatRev, 0.0, 0.0, 1.0);//公转
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)firstPlaSatRot, 0.0, 0.0, 1.0);//自转
	//glColor3f(0.5, 0.6, 0.5);
	//glutWireSphere(0.1, 10, 8);
	gluSphere(q, 0.1, 10, 8);
	glPopMatrix();
	glPopMatrix();


	/*第二颗行星轨道*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 8.0, 10, 64);
	glPopMatrix();

	/*第二颗行星*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glRotatef((GLfloat)secondPlaRev, 0.0, 0.0, 1.0);//公转
	glTranslatef(8.0, 0.0, 0.0);
	//glColor3f(0.0, 0.0, 1.0);
	glRotatef((GLfloat)secondPlaRot, 0.0, 0.0, 1.0);//自转
	//glutWireSphere(1, 20, 10);
	gluSphere(s,1, 20, 10);
	glPopMatrix();

	/*第三颗行星轨道*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 11.0, 10, 64);
	glPopMatrix();

	/*第三颗行星*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glRotatef((GLfloat)thirdPlaRev, 0.0, 0.0, 1.0);//行星公转
	glTranslatef(11.0, 0.0, 0.0);
	glColor3f(0.36, 0.88, 0.44);
	glRotatef((GLfloat)thirdPlaRot, 0.0, 0.0, 1.0);//行星自转
	//glutWireSphere(0.45, 10, 8);
	gluSphere(r,0.45, 10, 8);
	glPopMatrix();

	glutSwapBuffers();
	glRasterPos2f(0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glFlush();
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
	//太阳自转，第一颗行星的公转
	sunRot += 1;
	resetAngle(sunRot);
	//第一颗行星的自转
	firstPlaRot += 1.1;
	resetAngle(firstPlaRot);
	//第一颗行星的卫星自转
	firstPlaSatRot += 0.1;
	resetAngle(firstPlaSatRot);
	//第一颗行星的卫星公转
	firstPlaSatRev += 0.3;
	resetAngle(firstPlaSatRot);
	//第二颗行星的自转
	secondPlaRot += 1.2;
	resetAngle(secondPlaRot);
	//第二颗行星的公转
	secondPlaRev += 0.8;
	resetAngle(secondPlaRev);
	//第三颗行星的自转
	thirdPlaRot += 1.4;
	resetAngle(thirdPlaRot);
	//第三颗行星的公转
	thirdPlaRev += 0.6;
	resetAngle(thirdPlaRev);

	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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