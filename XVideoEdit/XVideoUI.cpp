#include "XVideoUI.h"
#include<QFileDialog>
#include<string>
#include<QMessageBox>
#include"XVideoThread.h"

static bool isExport = false;// 是否是导出状态的标志位

XVideoUI::XVideoUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);// 隐藏标题栏
	qRegisterMetaType<cv::Mat>("cv::Mat");
	//原视频显示信号
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1video,
		SLOT(SetImage(cv::Mat))
		);

	//输出视频显示信号
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewDes(cv::Mat)),
		ui.des,
		SLOT(SetImage(cv::Mat))
	);

	// 导出视频结束
	QObject::connect(XVideoThread::Get(),
		SIGNAL(SaveEnd()),
		this,
		SLOT(ExportEnd())
	);

	startTimer(40);
}

void XVideoUI::timerEvent(QTimerEvent *e) {
	if (pressSlider)
		return;
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

void XVideoUI::SliderPress() {
	pressSlider = true;
}
void XVideoUI::SliderRelease() {
	pressSlider = false;
}
void XVideoUI::SetPos(int pos) {
	XVideoThread::Get()->Seek((double)pos / 1000.);
}
// 设置过滤器
void XVideoUI::Set() {
	XFilter::Get()->Clear();
	//对比度和亮度
	if (ui.bright->value() > 0 || ui.contrast->value() > 1) {
		XFilter::Get()->Add(XTask{ XTASK_GAIN,
		{(double)ui.bright->value(),ui.contrast->value()}
		});
	}
}
// 导出视频
void XVideoUI::Export() {

	if (isExport) {// 如果已经是导出状态，那么此时按键上的文字是停止导出,同时本次点击的意图是停止导出调用stopSave
		XVideoThread::Get()->StopSave();
		isExport = false;
		ui.exportButton->setText("Start export");
		return;
	}
	// 开始导出
	QString name = QFileDialog::getSaveFileName(this, "save", "out1.avi");// 默认导出文件名是out1.avi
	if (name.isEmpty()) return;
	std::string filename = name.toLocal8Bit().data();
	if (XVideoThread::Get()->StartSave(filename)) {
		isExport = true;
		ui.exportButton->setText("Stop export");
	}
	
}

void XVideoUI::ExportEnd()
{
	isExport = false;
	ui.exportButton->setText("start export");
}
