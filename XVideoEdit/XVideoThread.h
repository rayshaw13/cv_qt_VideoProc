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
	//打开1号视频文件
	bool Open(const std::string file);
	// 返回当前播放位置
	double GetPos();
	// 跳转视频
	///@para frame int 帧位置
	bool Seek(int frame);
	bool Seek(double pos);//重载Seek

	// 开始保存视频
	bool StartSave(const std::string filename, int width = 0, int height = 0);
	
	// 停止保存视频。写入视频帧索引
	void StopSave();

	~XVideoThread();

	//线程入口函数
	void run();//重载QThread类的run函数
signals:
	//显示原视频1图像
	void ViewImage1(cv::Mat mat);

	//显示原视频2图像
	void ViewDes(cv::Mat mat);

	void SaveEnd();// 导出结束
protected:
	QMutex mutex;
	bool isWrite;// 是否写入视频
	XVideoThread();//将其声明为protected类型，只可以通过Get()访问线程，保证对象唯一性。
};

