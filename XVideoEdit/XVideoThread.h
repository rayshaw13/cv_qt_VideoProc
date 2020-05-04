#pragma once
#include<QThread>
#include<iostream>
#include<QMutex>

#include<opencv2\core.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\imgcodecs.hpp>
#include<opencv2\highgui.hpp>
using namespace cv;
class XVideoThread:public QThread
{

	Q_OBJECT

public:
	static XVideoThread* Get() {
		static XVideoThread vt;
		return &vt;
	}
	//打开1号视频文件
	bool Open(const std::string file);
	
	~XVideoThread();

	//线程入口函数
	void run();//重载QThread类的run函数
signals:
	void ViewImage1(cv::Mat mat);
protected:
	QMutex mutex;
	XVideoThread();//将其声明为protected类型，只可以通过Get()访问线程，保证对象唯一性。
};

