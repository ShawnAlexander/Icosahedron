#pragma once

#ifndef SJ_WINDOW_H
#define SJ_WINDOW_H

#include <QtWidgets/QMainWindow>
#include "Viewport.h"
#include "ui_SJWindow.h"

class SJWindow : public QMainWindow
{
	Q_OBJECT

public:
	SJWindow(QWidget *parent = Q_NULLPTR);
	~SJWindow();

private:
	Ui::SJWindowClass ui;
	QGridLayout *lay;
	Viewport *vp;
	QMenuBar *mb;
	QMenu *sides;
	QAction *s20;
	QAction *s80;
	QAction *s320;
	QAction *s1280;
	QMenu *shading;
	QAction *t1;
	QAction *t2;
	QMenu *light;
	QAction *l1;
	QAction *l2;
};

#endif