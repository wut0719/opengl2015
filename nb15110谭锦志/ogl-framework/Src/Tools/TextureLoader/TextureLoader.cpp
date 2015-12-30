#include "TextureLoader.h"
#include "../../GLWindow/GLWindow.h"

TextureLoader::TextureLoader()
{
	
}

TextureLoader::~TextureLoader()
{

}

/* 
* ���һ�������Ƿ�Ϊ 2 �������η�������ǣ����� 1�����򷵻� 0
*/
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return(n & (n - 1)) == 0;
}

/*
 * ����bitmap ���ط��������ID
 */
GLuint TextureLoader::LoadBitMapTexture(const char* file)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0; // ������������
	GLuint texture_ID = 0;
	GLint last_texture_ID;
	// ���ļ������ʧ�ܣ�����
	FILE* pFile = fopen(file, "rb");
	if (pFile == 0) {
		return 0; 
	}
		
	// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
	fseek(pFile, 0x0012, SEEK_SET);  // �ҵ�ͷ����Ϣ�еĿ����Ϣ��
	fread(&width, 4, 1, pFile);      // ��ȡ��
	fread(&height, 4, 1, pFile);	 // ��ȡ��
	fseek(pFile, BMP_Header_Length, SEEK_SET);
	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
	{
		GLint line_bytes = width * 3; // ��Ȳ���4�ı���ʱ���зŴ���4��
		while (line_bytes % 4 != 0) {
			++line_bytes;
		}
		total_bytes = line_bytes * height;
	}
	// �����������ֽ��������ڴ�
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0) {
		fclose(pFile);
		return 0;
	}
	// ��ȡ��������
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);   

		// �������������Ҫ��������
		if (!power_of_two(width)       // 1.����2�����η�
			|| !power_of_two(height)   // 2.�߲���2�����η�
			|| width > max			   // 3.��Խ��
			|| height > max)           // 4.��Խ��
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳�256��������
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;
			// ����ÿ����Ҫ���ֽ��������ֽ���
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0) {
				++new_line_bytes;
			}
			new_total_bytes = new_line_bytes * new_height;
			// �����ڴ�
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0) {
				free(pixels);
				fclose(pFile);
				return 0;
			}
			// ������������
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);
			// �ͷ�ԭ�����������ݣ��� pixels ָ���µ��������ݣ����������� width�� height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}
	// ����һ���µ�������
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0) {
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// ���µ������������������������
	// �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);
	free(pixels);  // �ͷ��ڴ�
	return texture_ID;
}

