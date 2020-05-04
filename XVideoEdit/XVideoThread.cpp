#include "XVideoThread.h"

static VideoCapture cap1;
static bool isexit = false;

bool XVideoThread::Open(const std::string file) {
	std::cout << "open: " << file << std::endl;
	mutex.lock();
	bool re = cap1.open(file);
	mutex.unlock();
	std::cout << re << "\n";
	return re;
}
XVideoThread::XVideoThread()
{
	start();// 开启线程
}

XVideoThread::~XVideoThread()
{
	mutex.lock();
	isexit = true;
	mutex.unlock();
}

void XVideoThread::run() {
	Mat mat1;
	for (;;) {
		mutex.lock();
		if (isexit) {
			mutex.unlock();
			break;
		}
		// 判断视频是否打开
		if (!cap1.isOpened()) {// 如果cap1没有打开（线程没有打开），就continue直至打开
			mutex.unlock();
			msleep(5);
			continue;
		}
		// 读取一帧数据，解码并完成颜色转换
		if (!cap1.read(mat1)||mat1.empty()) {
			mutex.unlock();
			msleep(5);
			continue;
		}
		// 显示图像 在这里不使用imshow了，而是显示在QT中。将mat1传出去，由videowidget绘制
		ViewImage1(mat1);
		msleep(40);
		mutex.unlock();
	}
}