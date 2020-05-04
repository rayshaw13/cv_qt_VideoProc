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
		msleep(40);
		mutex.unlock();
	}
}