#include "ScreenShot.h"
#include "../../GLWindow/GLWindow.h"
#include "../../System/System.h"
#include <string>

ScreenShot::ScreenShot()
{

}

ScreenShot::~ScreenShot()
{

}

void ScreenShot::GrabScreen(GLWindow* pWnd)
{
	FILE* pDummyFile;    // ���ڱ���bmp���ݵ��ļ�ָ��
	FILE* pWritingFile;  // ���ڶ�ȡ
	GLubyte* pPixelData; // ��������
	GLubyte BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint PixelDataLength;

	// �����������ݵ�ʵ�ʳ���
	i = pWnd->GetWidth() * 3; // ÿһ�е��������ݳ���

	while (i % 4 != 0) {
		++i; // �������ݣ�ֱ�� i ��4�ı���
	}

	PixelDataLength = i * pWnd->GetHeight();
	// �����ڴ�ʹ��ļ�
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0) {
		exit(0);  // ����ʧ��
	}

	pDummyFile = fopen("bitmap/dummy.bmp", "rb");

	if (pDummyFile == 0) {
		exit(0);
	}

	std::string file_name = std::string("screenshot/grab_screen ");
	std::string sys_time = apanoo::System::GetInstance()->GetSystemTime();

	std::string full_file_name = file_name + sys_time + std::string(".bmp");   // �����ļ�����ϵͳʱ���

	pWritingFile = fopen(full_file_name.c_str(), "wb");
	if (pWritingFile == 0) {
		exit(0);
	}

	// ��ȡ����
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, pWnd->GetWidth(), pWnd->GetHeight(),
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// �� dummy.bmp ���ļ�ͷ����Ϊ���ļ����ļ�ͷ
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);

	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = pWnd->GetWidth();
	j = pWnd->GetHeight();
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// д����������
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// �ͷ��ڴ�͹ر��ļ�
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}
