﻿#include "ball.h"

Ball::Ball()
	: texId(0)
	, radius(1.0f)
	, pos(10.0f, 0.0f, 0.0f)
	, revSpeed(1.0f)
	, rotSpeed(2.0f)
	, lightPos(0.0f, 0.0f, 0.0f)
	, lightColor(1.0f, 1.0f, 0.8f)
	, shininess(32.0f)
	, ambient(0.2f)
	, revAngle(0.0f)
	, rotAngle(0.0f)
	, obliquity(23.44f)
	, angleSpan(0.5f)
	, VBO(QOpenGLBuffer::VertexBuffer)
	, IBO(QOpenGLBuffer::IndexBuffer)
	, texture(QOpenGLTexture::Target2D)
{

	GLfloat u = 0, v = 0;
	GLint uStepNum = 360 / angleSpan;
	GLint vStepNum = 360 / angleSpan;
	GLfloat uStep = 1.0f / uStepNum;
	GLfloat vStep = 1.0f / vStepNum;
	GLfloat x = sin(PI * v) * cos(2 * PI * u);
	GLfloat y = sin(PI * v) * sin(2 * PI * u);
	GLfloat z = cos(PI * v);
	vertices << x << y << z << x << y << z << 0.5f << 1.0f;
	for (int i = 1; i < vStepNum; i++)
	{
		for (int j = 0; j < uStepNum; j++)
		{
			u = uStep * j;
			v = vStep * i;
			x = sin(PI * v) * cos(2 * PI * u);
			y = sin(PI * v) * sin(2 * PI * u);
			z = cos(PI * v);
			vertices << x << y << z << x << y << z << 1.0f - u << v;
		}
	}

	u = 1.0f;
	v = 1.0f;
	x = sin(PI * v) * cos(2 * PI * u);
	y = sin(PI * v) * sin(2 * PI * u);
	z = cos(PI * v);
	vertices << x << y << z << x << y << z << 0.5f << 0.0f;

	for (int i = 0; i <= uStepNum; i++) // 球体上第一层
	{
		indices << 0 << i + 1 << i + 2; // 上顶点总是第一个点
	};

	for (int i = 1; i < vStepNum - 1; i++) {
		int start = 1 + (i - 1) * (uStepNum + 1);
		for (int j = start; j < start + (1 + uStepNum); j++) {

			/*
			*       j
			*       |\
			*       | \
			*       |__\
			* j+uStepn j + (uStepnum + 1) % vStepnum
			*/
			indices << j << j + uStepNum + 1 << start + (1 + uStepNum) + ((j + 1 - start) % (1 + uStepNum));
			/*
			*
			*         j ___ ��j + 1��% uStepnum
			*           \  |
			*		     \ |
			*		      \|
			*     j + (uStepnum + 1) % vStepnum
			*/
			indices << j << start + (j + 1 - start) % (1 + uStepNum) << start + uStepNum + 1 + (j + 1 - start) % (1 + uStepNum);

		}
	}

	int last = 1 + (uStepNum + 1) * (vStepNum - 1);
	int start = 1 + (uStepNum + 1) * (vStepNum - 2);
	for (int i = 1 + (uStepNum + 1) * (vStepNum - 2); i < 1 + uStepNum * (vStepNum - 1); i++) // 球体上最后一层
	{
		indices << i << last << (last + ((1 + i) - start) % (1 + uStepNum)); // 逆时针排列
	}

	VAO.create();
	VBO.create();
	IBO.create();

	QOpenGLVertexArrayObject::Binder{ &VAO };

	VBO.bind();
	VBO.allocate(vertices.data(), sizeof(GLfloat) * vertices.size());
	VBO.release();

	IBO.bind();
	IBO.allocate(indices.data(), sizeof(unsigned int) * indices.size());
	IBO.release();
	texture.create();
}

Ball::~Ball() 
{
}

Ball::Ball(GLint texId, GLfloat r, QVector3D pos, GLfloat revS, GLfloat rotS, GLfloat obliquity, GLfloat s, GLfloat ambient, GLfloat diffuse, GLfloat specular, GLfloat angleSpan)
	: texId(texId)
	, radius(r)
	, pos(pos)
	, revSpeed(revS)
	, rotSpeed(rotS)
	, lightPos(0.0f, 0.0f, 0.0f)
	, lightColor(1.0f, 1.0f, 0.8f)
	, shininess(s)
	, ambient(ambient)
	, diffuse(diffuse)
	, specular(specular)
	, revAngle(0.0f)
	, rotAngle(0.0f)
	, obliquity(obliquity)
	, angleSpan(angleSpan)
	, VBO(QOpenGLBuffer::VertexBuffer)
	, IBO(QOpenGLBuffer::IndexBuffer)
	, texture(QOpenGLTexture::Target2D)
{
	GLfloat u = 0, v = 0;
	GLint uStepNum = 360 / angleSpan;
	GLint vStepNum = 360 / angleSpan;
	GLfloat uStep = 1.0f / uStepNum;
	GLfloat vStep = 1.0f / vStepNum;
	GLfloat x = sin(PI * v) * cos(2 * PI * u) * radius;
	GLfloat y = sin(PI * v) * sin(2 * PI * u) * radius;
	GLfloat z = cos(PI * v) * radius;
	vertices << x << y << z << x << y << z << 0.5f << 1.0f;
	for (int i = 1; i < vStepNum; i++)
	{
		for (int j = 0; j < uStepNum; j++)
		{
			u = uStep * j;
			v = vStep * i;
			x = sin(PI * v) * cos(2 * PI * u) * radius;
			y = sin(PI * v) * sin(2 * PI * u) * radius;
			z = cos(PI * v) * radius;
			vertices << x << y << z << x << y << z << 1.0f - u << v;
		}
	}

	u = 1.0f;
	v = 1.0f;
	x = sin(PI * v) * cos(2 * PI * u) * radius;
	y = sin(PI * v) * sin(2 * PI * u) * radius;
	z = cos(PI * v) * radius;
	vertices << x << y << z << x << y << z << 0.5f << 0.0f;

	for (int i = 0; i <= uStepNum; i++) // 球体上第一层
	{
		indices << 0 << i + 1 << i + 2; // 上顶点总是第一个点
	};

	for (int i = 1; i < vStepNum - 1; i++) {
		int start = 1 + (i - 1) * (uStepNum + 1);
		for (int j = start; j < start + (1 + uStepNum); j++) {

			/*
			*       j
			*       |\
			*       | \
			*       |__\
			* j+uStepn j + (uStepnum + 1) % vStepnum
			*/
			indices << j << j + uStepNum + 1 << start + (1 + uStepNum) + ((j + 1 - start) % (1 + uStepNum));
			/*
			*
			*         j ___ ��j + 1��% uStepnum
			*           \  |
			*		     \ |
			*		      \|
			*     j + (uStepnum + 1) % vStepnum
			*/
			indices << j << start + (j + 1 - start) % (1 + uStepNum) << start + uStepNum + 1 + (j + 1 - start) % (1 + uStepNum);

		}
	}

	int last = 1 + (uStepNum + 1) * (vStepNum - 1);
	int start = 1 + (uStepNum + 1) * (vStepNum - 2);
	for (int i = 1 + (uStepNum + 1) * (vStepNum - 2); i < 1 + uStepNum * (vStepNum - 1); i++) // 球体上最后一层
	{
		indices << i << last << (last + ((1 + i) - start) % (1 + uStepNum)); // 逆时针排列
	}
	VAO.create();
	VBO.create();
	IBO.create();

	QOpenGLVertexArrayObject::Binder{ &VAO };

	VBO.bind();
	VBO.allocate(vertices.data(), sizeof(GLfloat) * vertices.size());
	VBO.release();

	IBO.bind();
	IBO.allocate(indices.data(), sizeof(unsigned int) * indices.size());
	IBO.release();

	texture.create();
}

void Ball::textureBind(QString tex)
{
	texture.setData(QImage(tex).mirrored());
	texture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
	texture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
	texture.setBorderColor(QColor(1.0f, 1.0f, 1.0f, 1.0f));
	texture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Linear);
	texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
}

void Ball::revolute(GLfloat speed) {
	revAngle = (revAngle + revSpeed * speed) < 360 ? revAngle + revSpeed * speed : 0;
}

void Ball::rotate(GLfloat speed) {
	rotAngle = (rotAngle + rotSpeed * speed) < 360 ? rotAngle + rotSpeed * speed : 0;
}

void Ball::drawBall(QOpenGLExtraFunctions* f, QMatrix4x4 view, QMatrix4x4 projection, QMatrix4x4 model, QVector3D viewPos, QOpenGLShaderProgram& shader) {

	QOpenGLVertexArrayObject::Binder{ &VAO };

	VBO.bind();
	IBO.bind();
	shader.bind();

	shader.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 8); // Pos
	shader.enableAttributeArray(0);
	shader.setAttributeBuffer(1, GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8); // Normal
	shader.enableAttributeArray(1);
	shader.setAttributeBuffer(2, GL_FLOAT, sizeof(GLfloat) * 6, 2, sizeof(GLfloat) * 8); // TexCoord
	shader.enableAttributeArray(2);


	//model.setToIdentity();
	model.rotate(revAngle, QVector3D(0.0f, 1.0f, 0.0f));  // 公转
	model.translate(pos);
	model.rotate(-revAngle, QVector3D(0.0f, 1.0f, 0.0f));
	model.rotate(obliquity, QVector3D(0.0f, 0.0f, 1.0f));// 轴倾角
	model.rotate(rotAngle, QVector3D(0.0f, 1.0f, 0.0f)); // 自转
	if (this->texId == 9)  // 月球
	{
		model.translate(QVector3D(1.5f, 0.0f, 0.0f));
	}
	model.rotate(90, QVector3D(1.0f, 0.0f, 0.0f));

	shader.setUniformValue("model", model);
	shader.setUniformValue("view", view);
	shader.setUniformValue("projection", projection);
	shader.setUniformValue("lightPos", lightPos);
	shader.setUniformValue("lightColor", lightColor);
	shader.setUniformValue("viewPos", viewPos);
	shader.setUniformValue("shininess", shininess);
	shader.setUniformValue("ambientStrength", ambient);
	shader.setUniformValue("diffuseStrength", diffuse);
	shader.setUniformValue("specularStrength", specular);


	texture.bind(texId);
	shader.setUniformValue("ourTexture", texId);

	// f->glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	f->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	texture.release();
	shader.release();
	VBO.release();
	IBO.release();
}
