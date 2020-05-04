#include "XVideoThread.h"

static VideoCapture cap1;
static bool isexit = false;

bool XVideoThread::Open(const std::string file) {
	std::cout << "open: " << file << std::endl;
	mutex.lock();
	bool re = cap1.open(file);
	mutex.unlock();
	std::cout << re << "\n";
	if(!re)
		return re;
	fps = cap1.get(CAP_PROP_FPS);// ��ȡ֡��
	if (fps <= 0) fps = 25;// ���û���õ�֡��ֵ���ͼٶ�Ϊ25
	return true;
}
XVideoThread::XVideoThread()
{
	start();// �����߳�
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
		// �ж���Ƶ�Ƿ��
		if (!cap1.isOpened()) {// ���cap1û�д򿪣��߳�û�д򿪣�����continueֱ����
			mutex.unlock();
			msleep(5);
			continue;
		}
		// ��ȡһ֡���ݣ����벢�����ɫת��
		if (!cap1.read(mat1)||mat1.empty()) {
			mutex.unlock();
			msleep(5);
			continue;
		}
		// ��ʾͼ�� �����ﲻʹ��imshow�ˣ�������ʾ��QT�С���mat1����ȥ����videowidget����
		ViewImage1(mat1);
		//msleep(40);
		int s = 0;
		s = 1000 / fps;
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