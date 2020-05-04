#pragma once
#include<QOpenGLWidget>
#include<opencv2\core.hpp>
#include<opencv2\imgproc.hpp>
#include<QPainter>
using namespace cv;

class XVideoWidget:public QOpenGLWidget
{

	Q_OBJECT

public:
	XVideoWidget(QWidget *p);
	void paintEvent(QPaintEvent *e);
	virtual ~XVideoWidget();

public slots:
	void SetImage(cv::Mat mat);
protected:
	QImage img;//进行图片的绘制
};

