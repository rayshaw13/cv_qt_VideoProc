#include "XVideoThread.h"

// 一号视频源
static VideoCapture cap1;

// 保存视频
static VideoWriter vw;
static bool isexit = false;

bool XVideoThread::Open(const std::string file) {
	std::cout << "open: " << file << std::endl;
	mutex.lock();
	bool re = cap1.open(file);
	mutex.unlock();
	std::cout << re << "\n";
	if(!re)
		return re;
	fps = cap1.get(CAP_PROP_FPS);// 获取帧率
	if (fps <= 0) fps = 25;// 如果没有拿到帧率值，就假定为25
	return true;
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
	wait();
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
			// 导出到结尾位置，停止导出
			if (isWrite) {
				StopSave();
				SaveEnd();// 调用信号函数
			}

			msleep(5);
			continue;
		}
		// 显示图像1 在这里不使用imshow了，而是显示在QT中。将mat1传出去，由videowidget绘制
		ViewImage1(mat1);

		//通过过滤器处理视频
		Mat des=XFilter::Get()->Filter(mat1, Mat());

		//显示生成后视频图像
		ViewDes(des);

		int s = 0;
		s = 1000 / fps;

		if (isWrite) {
			//s = 1;// 当视频导出时 sleep时间变短，暂时不改了
			vw.write(des);
		}
		//msleep(40);

		msleep(s);
		mutex.unlock();
	}
}

double XVideoThread::GetPos() {
	double pos = 0;
	mutex.lock();
	if (!cap1.isOpened()) {
		mutex.unlock();
		return pos;
	}
	double count=cap1.get(CAP_PROP_FRAME_COUNT);
	double cur = cap1.get(CAP_PROP_POS_FRAMES);
	if(count>0.001)
		pos = cur / count;
	mutex.unlock();
	return pos;
}

bool XVideoThread::Seek(int frame) {
	mutex.lock();
	if (!cap1.isOpened()) {
		mutex.unlock();
		return false;
	}
	int re = cap1.set(CAP_PROP_POS_FRAMES, frame);
	mutex.unlock();
	return re;
}

bool XVideoThread::Seek(double pos) {
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	int frame = pos*count;
	return Seek(frame);
}

bool XVideoThread::StartSave(const std::string filename, int width, int height) {
	std::cout << "开始导出" << std::endl;
	Seek(0);// 跳到视频开始处
	mutex.lock();
	if (!cap1.isOpened()) {// 确保原图1打开
		mutex.unlock();
		return false;
	}
	if (width <= 0)// 如果没有设置width，那么就获取原图的宽度
		width = cap1.get(CAP_PROP_FRAME_WIDTH);
	if (height <= 0)
		height = cap1.get(CAP_PROP_FRAME_HEIGHT);
	vw.open(filename, VideoWriter::fourcc('X', '2', '6', '4'), this->fps, Size(width, height));
	if (!vw.isOpened()) {
		mutex.unlock();
		std::cout << "start save failed" << std::endl;
		return false;
	}
	this->isWrite = true;
	mutex.unlock();
	return true;
}

void XVideoThread::StopSave() {
	std::cout << "停止导出" << std::endl;
	mutex.lock();// 因为释放的时候有可能还在写入，因此加入锁
	vw.release();
	isWrite = false;
	mutex.unlock();
}