#ifndef __MYMETEOR_H__
#define __MYMETEOR_H__

#ifdef MAC_OS
#include <QtOpenGL/QtOpenGL>
#else
#include <GL/glew.h>
#endif
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QtMath>
#include "GL/glut.h"

class Meteor
{
public:
	Meteor(QWidget* widget);
	void initMeteor();
	void drawMeteor();
	void explode();					//��ըЧ��
	void meteor_run();				//����Ч��
	void change_rainbow();			//ûʲô�õġ����ĳɲʺ���ɫ
	void change_color();			//ûʲô�õġ����ı���ɫ

private:
	QWidget* widget;


	static const int MAX_PARTICLES = 2000;          //���������
	static const GLfloat COLORS[12][3];             //�ʺ����ɫ
	bool m_Rainbow;                                 //�Ƿ�Ϊ�ʺ�ģʽ
	GLuint m_Color;                                 //��ǰ����ɫ
	float m_Slowdown;                               //��������
	float m_xSpeed;                                 //x������ٶ�
	float m_ySpeed;                                 //y������ٶ�
	float m_Deep;                                   //������Ļ�ľ���

	int screen_width;
	int screen_height;

	struct Particle                                 //�������ӽṹ��
	{
		bool active;                                //�Ƿ񼤻�
		float life;                                 //��������
		float fade;                                 //˥���ٶ�

		float r, g, b;                              //������ɫ
		float x, y, z;                              //λ������
		float xi, yi, zi;                           //�������ٶ�
		float xg, yg, zg;                           //��������ٶ�
	} m_Particles[MAX_PARTICLES];                   //����������ӵ�����
	//Camera camera;
};
#endif // __MYMETEOR_H__