#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XVideoUI.h"

static bool pressSlider = false;

class XVideoUI : public QMainWindow
{
	Q_OBJECT

public:
	XVideoUI(QWidget *parent = Q_NULLPTR);
	void timerEvent(QTimerEvent *e);

private:
	Ui::XVideoUIClass ui;
public slots:
	void Open();
	void SliderPress();
	void SliderRelease();
	void SetPos(int);//»¬¶¯ÌõÍÏ¶¯
};
