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
	//��1����Ƶ�ļ�
	bool Open(const std::string file);
	
	~XVideoThread();

	//�߳���ں���
	void run();//����QThread���run����
signals:
	void ViewImage1(cv::Mat mat);
protected:
	QMutex mutex;
	XVideoThread();//��������Ϊprotected���ͣ�ֻ����ͨ��Get()�����̣߳���֤����Ψһ�ԡ�
};

