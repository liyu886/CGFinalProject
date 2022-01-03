﻿#ifndef __MYGLWIDGET_H__
#define __MYGLWIDGET_H__

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

//#include "GLFW/glfw3.h"

#include "mycamera.h"
#include "solarSystem.h"
// #include "textRender.h"

class MyGLWidget : public QOpenGLWidget {
	Q_OBJECT

public:
	MyGLWidget(QWidget* parent = nullptr);
	~MyGLWidget();

protected:
	void initializeGL();
	virtual void paintGL();
	void resizeGL(int width, int height);
	void keyPressEvent(QKeyEvent* e);
	virtual bool event(QEvent* e) override;

	void calcFPS();

	void drawSkybox();

private:
	int scene_id;
	int fps;
	void scene_0();
	void scene_1();

	QOpenGLShaderProgram shaderProgram;
	QTimer* timer;
	SolarSystem* solarSystem;

	Camera camera;

};
#endif // __MYGLWIDGET_H__
