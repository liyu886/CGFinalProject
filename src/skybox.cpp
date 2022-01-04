#pragma once
#include "skybox.h"
#define sky_size 500.0f

Skybox::Skybox(QWidget* widget) :
	SkyboxVBO(QOpenGLBuffer::VertexBuffer),
	SkyboxTexture(QOpenGLTexture::Target2D)
{

	SkyboxVertices = {
		// λ��              // ��ɫ				// ����
		 1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // ����
		-1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // ����
		-1.0f * sky_size,  1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // ����
		 1.0f * sky_size,  1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // ����

		 1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // ����
		-1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // ����
		-1.0f * sky_size,  1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // ����
		 1.0f * sky_size,  1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // ����

		 1.0f * sky_size, 1.0f * sky_size,  -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // ����
		 1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // ����
		 1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // ����
		 1.0f * sky_size, 1.0f * sky_size,  1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // ����

		 -1.0f * sky_size, 1.0f * sky_size,  -1.0f * sky_size, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // ����
		 -1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // ����
		 -1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // ����
		 -1.0f * sky_size, 1.0f * sky_size,  1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // ����

		 1.0f * sky_size, 1.0f * sky_size, -1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // ����
		-1.0f * sky_size, 1.0f * sky_size, -1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // ����
		-1.0f * sky_size, 1.0f * sky_size, 1.0f * sky_size,    1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // ����
		 1.0f * sky_size, 1.0f * sky_size, 1.0f * sky_size,    1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // ����

		 1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // ����
		-1.0f * sky_size, -1.0f * sky_size, -1.0f * sky_size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // ����
		-1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // ����
		 1.0f * sky_size, -1.0f * sky_size, 1.0f * sky_size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // ����
	};
}

Skybox::~Skybox() {

}
void Skybox::drawSkybox(QMatrix4x4 view, QMatrix4x4 model, QMatrix4x4 projection) {
	shaderProgram.bind();
	float time = QTime::currentTime().msecsSinceStartOfDay() / 1000.0;
	model.rotate(10 * time, QVector3D(1.0f, 0.0f, -1.0f));//��պ���ת

	shaderProgram.setUniformValue("view", view);
	shaderProgram.setUniformValue("projection", projection);
	shaderProgram.setUniformValue("model", model);

	SkyboxVAO.bind();
	SkyboxVBO.create();       // ����VBO����
	SkyboxVBO.bind();         // ��VBO�󶨵���ǰ�Ķ��㻺�����QOpenGLBuffer::VertexBuffer����
	// ���������ݷ��䵽VBO�У���һ������Ϊ����ָ�룬�ڶ�������Ϊ���ݵ��ֽڳ���
	SkyboxVBO.allocate(SkyboxVertices.data(), sizeof(float) * SkyboxVertices.size());

	shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(0);
	shaderProgram.setAttributeBuffer(1, GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(1);
	shaderProgram.setAttributeBuffer(2, GL_FLOAT, sizeof(GLfloat) * 6, 2, sizeof(GLfloat) * 8);
	shaderProgram.enableAttributeArray(2);

	SkyboxTexture.bind(0);
	shaderProgram.setUniformValue("ourTexture", 0);      // ��ourTexture��ɫ������������Ԫ0�л�ȡ��������

	glDrawArrays(GL_QUADS, 0, 24);
	SkyboxVAO.release();
	SkyboxTexture.release();
	shaderProgram.release();
}

void Skybox::init() {
	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shaders/triangle.vert")) {     //��Ӳ����붥����ɫ��
		qDebug() << "ERROR:" << shaderProgram.log();    // �������ʱ��ӡ������Ϣ
	}
	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resource/shaders/triangle.frag")) {   //��Ӳ�����Ƭ����ɫ��
		qDebug() << "ERROR:" << shaderProgram.log();    // �������ʱ��ӡ������Ϣ
	}
	if (!shaderProgram.link()) {						// ������ɫ��
		qDebug() << "ERROR:" << shaderProgram.log();    // �������ʱ��ӡ������Ϣ
	}

	SkyboxVAO.create();       // ����VAO����

	SkyboxTexture.create();

	SkyboxTexture.setData(QImage(":/resource/textures/sky.png").mirrored());
	SkyboxTexture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	SkyboxTexture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

	SkyboxTexture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Linear);
	SkyboxTexture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);


}
