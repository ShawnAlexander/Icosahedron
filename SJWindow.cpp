#include "SJWindow.h"

SJWindow::SJWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	lay = new QGridLayout(ui.centralWidget);
	vp = new Viewport();
	lay->addWidget(vp, 0, 0, 1, 1);
	mb = ui.menuBar;
	sides = mb->addMenu("Subdivision");
	s20 = sides->addAction("20");
	s80 = sides->addAction("80");
	s320 = sides->addAction("320");
	s1280 = sides->addAction("1280");
	shading = mb->addMenu("Shading");
	t1 = shading->addAction("Flat");
	t2 = shading->addAction("Smooth");
	light = mb->addMenu("Light");
	l1 = light->addAction("Light #1");
	l2 = light->addAction("Light #2");
	l1->setCheckable(true);
	l1->setChecked(true);
	l2->setCheckable(true);
	connect(s20, &QAction::triggered, vp, &Viewport::s20Change);
	connect(s80, &QAction::triggered, vp, &Viewport::s80Change);
	connect(s320, &QAction::triggered, vp, &Viewport::s320Change);
	connect(s1280, &QAction::triggered, vp, &Viewport::s1280Change);
	connect(l1, &QAction::triggered, vp, &Viewport::l1Change);
	connect(l2, &QAction::triggered, vp, &Viewport::l2Change);
	connect(t1, &QAction::triggered, vp, &Viewport::t1Change);
	connect(t2, &QAction::triggered, vp, &Viewport::t2Change);
}

SJWindow::~SJWindow() {
	delete vp;
	delete lay;
}