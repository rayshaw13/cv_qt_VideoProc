#include "XVideoUI.h"
#include<QFileDialog>
#include<string>
#include<QMessageBox>
#include"XVideoThread.h"

XVideoUI::XVideoUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);// 隐藏标题栏
	qRegisterMetaType<cv::Mat>("cv::Mat");
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1video,
		SLOT(SetImage(cv::Mat))
		);
	startTimer(40);
}

void XVideoUI::timerEvent(QTimerEvent *e) {
	double pos = XVideoThread::Get()->GetPos();
	ui.playSlider->setValue(pos * 1000);
}

void XVideoUI::Open() {
	// 按下打开按钮后，打开一个视频文件
	// fromLocal8Bit 防止中文出现乱码
	// tolocal8Bit 当路径中出现中文时，同样转换为中文的字符串
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请打开一个视频文件"));//该函数也可以限制文件类型等
	if (name.isEmpty()) return;
	std::string file = name.toLocal8Bit().data();

	//XVideoThread打开视频
	//XVideoThread xv;//因为构造函数protected类型，不能访问。
	if (!XVideoThread::Get()->Open(file)) {
		QMessageBox::information(this, "Message:", name+" open failed");
	}
	else
		QMessageBox::information(this, "Message:", name + " open succeed");
	//QMessageBox::information(this, "", name);
}