#pragma once

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGLWidget>
#include <QtOpenGL>
#include <iostream>


class Viewport : public QGLWidget
{
	Q_OBJECT
public:
	Viewport(QWidget *parent = nullptr);
	~Viewport();
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void setXRotation(int);
	void setYRotation(int);
	void setZRotation(int);

public slots:
	void t1Change(bool);
	void t2Change(bool);
	void l1Change(bool);
	void l2Change(bool);
	void s20Change(bool);
	void s80Change(bool);
	void s320Change(bool);
	void s1280Change(bool);

private:
	GLfloat X = .525731112119133606;
	GLfloat Z = .850650808352039932;
	GLfloat l1Pos[4] = {-3, 7, 5, 0};
	GLfloat l2Pos[4] = {0, 0, 10, 0};
	GLfloat red_light[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat green_light[4] = {0.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat white_light[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat blue_light[4] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat black_light[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat purple_light[4] = {0.3f, 0.0f, 0.588f, 1.0f};
	GLfloat no_mat[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat mat_diffuse[4] = {1.0f, 0.5f, 0.5f, 1.0f};
	GLfloat mat_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat high_shininess[1] = {100.0f};
	GLfloat color[4] = {1.0f, 0.1f, 0.1f, 1.0f};
	GLfloat vdata[12][3] = {
		{ -X, 0.0, Z },{ X, 0.0, Z },{ -X, 0.0, -Z },{ X, 0.0, -Z },
		{ 0.0, Z, X },{ 0.0, Z, -X },{ 0.0, -Z, X },{ 0.0, -Z, -X },
		{ Z, X, 0.0 },{ -Z, X, 0.0 },{ Z, -X, 0.0 },{ -Z, -X, 0.0 }
	};
	GLint tindices[20][3] = {
		{ 0,4,1 },{ 0,9,4 },{ 9,5,4 },{ 4,5,8 },{ 4,8,1 },
		{ 8,10,1 },{ 8,3,10 },{ 5,3,8 },{ 5,2,3 },{ 2,7,3 },
		{ 7,10,3 },{ 7,6,10 },{ 7,11,6 },{ 11,0,6 },{ 0,1,6 },
		{ 6,1,10 },{ 9,0,11 },{ 9,11,2 },{ 9,2,5 },{ 7,2,11 } };

	void drawtriangle(float*, float*, float*);
	void subdivide(float*, float*, float*, long);
	void normalize(float[3]);
	void normcrossprod(float[3], float[3], float[3]);
	//void draw();

	int xRot;
	int yRot;
	int zRot;
	bool activeLights[2];

	int subD;

	QPoint lastPos;
};

#endif

