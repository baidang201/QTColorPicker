#include <QMessageBox>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "TColorPicker.h"


TMainWindow::TMainWindow(QWidget *parent) :
    QMainWindow(parent)
{    
	CreateUI();
}

TMainWindow::~TMainWindow()
{

}

void TMainWindow::CreateUI()
{
	mColorPicker = new TColorPicker(this);
	mColorPicker->resize(50, 50);

	QWidget* widget = new QWidget(this);
	setCentralWidget(widget);

	QVBoxLayout* layout = new QVBoxLayout(widget);
	widget->setLayout(layout);

	layout->addWidget(mColorPicker);

	mLable = new QLabel(tr("xxx Sample"), this);
	layout->addWidget(mLable);

	QPushButton* pushButton = new QPushButton("testingText", this);
	layout->addWidget(pushButton);

	connect(mColorPicker, SIGNAL(clicked()), this, SLOT(onColorChange()));

}


void TMainWindow::onColorChange()
{
	QColor color = mColorPicker->GetColor(Qt::black, QPoint(0, 0));
	if (color.isValid())
	{
		mLable->setStyleSheet(QString("color:%1; font-size:22px;").arg(color.name()));
	}
}

