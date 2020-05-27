#pragma once
#include<QThread>
#include<iostream>
#include<QMutex>

#include<opencv2\core.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\imgcodecs.hpp>
#include<opencv2\highgui.hpp>

#include"XFilter.h"

using namespace cv;
class XVideoThread:public QThread
{

	Q_OBJECT

public:
	int fps;
	static XVideoThread* Get() {
		static XVideoThread vt;
		return &vt;
	}
	//��1����Ƶ�ļ�
	bool Open(const std::string file);
	// ���ص�ǰ����λ��
	double GetPos();
	// ��ת��Ƶ
	///@para frame int ֡λ��
	bool Seek(int frame);
	bool Seek(double pos);//����Seek

	// ��ʼ������Ƶ
	bool StartSave(const std::string filename, int width = 0, int height = 0);
	
	// ֹͣ������Ƶ��д����Ƶ֡����
	void StopSave();

	~XVideoThread();

	//�߳���ں���
	void run();//����QThread���run����
signals:
	//��ʾԭ��Ƶ1ͼ��
	void ViewImage1(cv::Mat mat);

	//��ʾԭ��Ƶ2ͼ��
	void ViewDes(cv::Mat mat);

	void SaveEnd();// ��������
protected:
	QMutex mutex;
	bool isWrite;// �Ƿ�д����Ƶ
	XVideoThread();//��������Ϊprotected���ͣ�ֻ����ͨ��Get()�����̣߳���֤����Ψһ�ԡ�
};

