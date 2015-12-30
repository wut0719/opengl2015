#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <math.h>
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLShaderManager shaderManager;
GLMatrixStack modelViewMatrix;
GLMatrixStack projectionMatrix;
GLFrustum viewFrustum;
GLGeometryTransform transformPipeline;

GLTriangleBatch sunSphereBatch;
GLTriangleBatch earthSphereBatch;
GLTriangleBatch moonSphereBatch;
GLBatch floorBatch;
GLFrame cameraFrame;

void SetupRc()
{
	//��ʼ����ɫ������
	shaderManager.InitializeStockShaders();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//��һ����
	gltMakeSphere(sunSphereBatch, 0.4f, 30, 30);
	//��һ������
	gltMakeSphere(earthSphereBatch, 0.2f, 26, 13);
	//��һ��С����
	gltMakeSphere(moonSphereBatch, 0.1f, 18, 9);

	//��һ���ذ�
	floorBatch.Begin(GL_LINES, 324);
	for(GLfloat x = -20.0; x <= 20.0f; x += 0.5)
	{
		floorBatch.Vertex3f(x, -0.55f, 20.0f);
		floorBatch.Vertex3f(x, -0.55f, -20.0f);

		floorBatch.Vertex3f(20.0f, -0.55f, x);
		floorBatch.Vertex3f(-20.0f, -0.55f, x);
	}
	floorBatch.End();
}

void ChangeSize(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
	
	//����ͶӰ���󣬲���������ͶӰ�����ջ
	viewFrustum.SetPerspective(35.0f, float(nWidth)/float(nHeight), 1.0f, 100.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

	//����ת��ͨ��ʹ��������ѵ�
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void RenderScene()
{
	//�趨��ɫֵ
	static GLfloat vSunColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
	static GLfloat vEarthColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
	static GLfloat vMoonColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};

	//����ʱ��Ķ���
	static CStopWatch rotTimer;
	float yRot = rotTimer.GetElapsedSeconds() * 60.0f;

	//�����ɫ����Ȼ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���浱ǰģ����ͼ���󣨵�λ����
	modelViewMatrix.PushMatrix();

	M3DMatrix44f mCamera;
	cameraFrame.GetCameraMatrix(mCamera);
	modelViewMatrix.PushMatrix(mCamera);

	//�任��Դ��λ�õ��۾�����
	M3DVector4f vLightPos = {0.0f, 10.0f, 5.0f, 1.0f};
	M3DVector4f vLightEyePos;
	m3dTransformVector4(vLightEyePos, vLightPos, mCamera);

	//���Ƶذ�
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor);
	floorBatch.Draw();

	//��ʾΪ�߿���
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//����������ת��̫��
	modelViewMatrix.Translate(0.0f, 0.0f, -3.5f);

	//����仯
	modelViewMatrix.PushMatrix();

	//Ӧ��һ����ת��ʽ������̫��
	modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vSunColor);
	sunSphereBatch.Draw();
	modelViewMatrix.PopMatrix();

	//Ӧ����һ����ת��ʽ����ƽ�ƣ�Ȼ����Ƶ���
	modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
	modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vEarthColor);
	earthSphereBatch.Draw();

	//Ӧ����һ����ת��ʽ����ƽ�ƣ�Ȼ���������
	modelViewMatrix.Rotate(yRot * -4.0f, 0.0f, 1.0f, 0.0f);
	modelViewMatrix.Translate(0.4f, 0.0f, 0.0f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vMoonColor);
	moonSphereBatch.Draw();

	//�ָ�֮ǰ��ģ����ͼ���󣨵�λ����
	modelViewMatrix.PopMatrix();
	modelViewMatrix.PopMatrix();    
	modelViewMatrix.PopMatrix();

	//ִ�л���������
	glutSwapBuffers();

	//����GLUT�ظ���
	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	float linear = 0.1f;
	float angular = float(m3dDegToRad(5.0f));

	if(key == GLUT_KEY_UP)
		cameraFrame.MoveForward(linear);
	if(key == GLUT_KEY_DOWN)
		cameraFrame.MoveForward(-linear);
	if(key == GLUT_KEY_LEFT)
		cameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
	if(key == GLUT_KEY_RIGHT)
		cameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);

	glutCreateWindow("SphereWorld");

	glutSpecialFunc(SpecialKeys);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRc();
	glutMainLoop();

	return 0;
}
