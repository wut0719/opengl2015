#pragma once
/*
 * BitMap : �ṩBitMap����
 *          1) ��Ļ����Ϊ BitMap
 *		    2) ���� BitMap
 */

#include "../../GLWindow/stdafx.h"

class GLWindow;

#define BMP_Header_Length 54

class TextureLoader 
{
public:
	TextureLoader ();
	~TextureLoader ();

	// ����λͼ����
	GLuint LoadBitMapTexture(const char* file);

private:
	GLint m_width;
	GLint m_height;
};