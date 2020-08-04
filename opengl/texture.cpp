#include "texture.h"

void generateTexture(const char* texturepath,GLuint* textName)
{
	AUX_RGBImageRec* TextureImage[1];
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //����ε���ʾ��ʽ,ģʽ���������������������������ʽ

	glGenTextures(1, textName);
	glBindTexture(GL_TEXTURE_2D, *textName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	memset(TextureImage, 0, sizeof(void*) * 1);
	if (TextureImage[0] = auxDIBImageLoadA(texturepath))  //������
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}


	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);//��Ȼ���Ƚ�ֵ,ͨ�������zֵ�Ƿ�С�ڻ���ڴ洢zֵ

	glClearColor(0, 0, 0, 0);    //���ñ���ɫ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);//����ͶӰ����
}