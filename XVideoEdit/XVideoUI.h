#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XVideoUI.h"


class XVideoUI : public QMainWindow
{
	Q_OBJECT

public:
	XVideoUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::XVideoUIClass ui;
public slots:
	void Open();
};
