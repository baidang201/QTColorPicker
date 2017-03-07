#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "TColorPicker.h"

class TMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TMainWindow(QWidget *parent = 0);
    ~TMainWindow();
  
private:
	void CreateUI();

public slots:
	void onColorChange();

private:
	QLabel* mLable;

	TColorPicker* mColorPicker;
};

#endif // MAINWINDOW_H
