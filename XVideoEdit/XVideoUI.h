#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XVideoUI.h"
#include"XFilter.h"

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
	void SetPos(int);//滑动条拖动

	// 设置过滤器
	void Set();

	// 导出视频
	void Export();
	// 导出结束
	void ExportEnd();

};
