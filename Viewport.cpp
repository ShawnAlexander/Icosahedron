#include "Viewport.h"

Viewport::Viewport(QWidget *parent) : QGLWidget(parent)
{
	xRot = 0;
	yRot = 0;
	zRot = 0;
	subD = 0;
}

Viewport::~Viewport()
{
}

QSize Viewport::minimumSizeHint() const
{
	return QSize(400, 400);
}

QSize Viewport::sizeHint() const
{
	return QSize(800, 800);
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
}

void Viewport::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		updateGL();
	}
}

void Viewport::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		updateGL();
	}
}

void Viewport::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		updateGL();
	}
}

void Viewport::t1Change(bool checked) {
	glShadeModel(GL_FLAT);
	updateGL();
}

void Viewport::t2Change(bool checked) {
	glShadeModel(GL_SMOOTH);
	updateGL();
}

void Viewport::l1Change(bool checked) {
	if (checked) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	updateGL();
}

void Viewport::l2Change(bool checked) {
	if (checked) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}
	updateGL();
}

void Viewport::s20Change(bool checked) {
	subD = 0;
	updateGL();
}

void Viewport::s80Change(bool checked) {
	subD = 1;
	updateGL();
}

void Viewport::s320Change(bool checked) {
	subD = 3;
	updateGL();
}

void Viewport::s1280Change(bool checked) {
	subD = 6;
	updateGL();
}

void Viewport::initializeGL() {
	//GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
	//GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	//qglClearColor(Qt::black);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT0, GL_POSITION, l1Pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, green_light);
	glLightfv(GL_LIGHT1, GL_POSITION, l2Pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
	glDisable(GL_LIGHT1);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void Viewport::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColor4fv(color);
	for (int i = 0; i < 20; ++i) {
		GLfloat d1[3], d2[3], norm[3];
		for (int j = 0; j < 3; j++) {
			d1[j] = vdata[tindices[i][0]][j] - vdata[tindices[i][1]][j];
			d2[j] = vdata[tindices[i][1]][j] - vdata[tindices[i][2]][j];
		}
		normcrossprod(d1, d2, norm);
		glNormal3fv(norm);
		subdivide(&vdata[tindices[i][0]][0], &vdata[tindices[i][1]][0], &vdata[tindices[i][2]][0], subD);
	}
}

void Viewport::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, +2, -2, +2, 1.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}

	lastPos = event->pos();
}

void Viewport::normalize(float v[3]) {
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		std::cerr << "zero length vector" << std::endl;
	}
	else {
		v[0] /= d; v[1] /= d; v[2] /= d;
	}
}

void Viewport::normcrossprod(float v1[3], float v2[3], float out[3])
{
	GLint i, j;
	GLfloat length;
	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
	normalize(out);
}

void Viewport::drawtriangle(float *v1, float *v2, float *v3)
{
	glBegin(GL_POLYGON);
	glNormal3fv(v1); glVertex3fv(v1);
	glNormal3fv(v2); glVertex3fv(v2);
	glNormal3fv(v3); glVertex3fv(v3);
	glEnd();
}


void Viewport::subdivide(float *v1, float *v2, float *v3, long depth)
{
	GLfloat v12[3], v23[3], v31[3];
	GLint i;

	if (depth == 0) {
		drawtriangle(v1, v2, v3);
		return;
	}
	for (i = 0; i < 3; i++) {
		v12[i] = (v1[i] + v2[i]) / 2;
		v23[i] = (v2[i] + v3[i]) / 2;
		v31[i] = (v3[i] + v1[i]) / 2;
	}
	normalize(v12);
	normalize(v23);
	normalize(v31);
	subdivide(v1, v12, v31, depth - 1);
	subdivide(v2, v23, v12, depth - 1);
	subdivide(v3, v31, v23, depth - 1);
	subdivide(v12, v23, v31, depth - 1);
}
/*
void Viewport::draw()
{
	for (int i = 0; i < 20; ++i) {
		GLfloat d1[3], d2[3], norm[3];
		for (int j = 0; j < 3; j++) {
			d1[j] = vdata[tindices[i][0]][j] - vdata[tindices[i][1]][j];
			d2[j] = vdata[tindices[i][1]][j] - vdata[tindices[i][2]][j];
		}
		normcrossprod(d1, d2, norm);
		glNormal3fv(norm);
		subdivide(&vdata[tindices[i][0]][0], &vdata[tindices[i][1]][0], &vdata[tindices[i][2]][0], subD);
	}
}
*/