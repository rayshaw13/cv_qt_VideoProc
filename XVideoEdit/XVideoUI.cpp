#include "XVideoUI.h"
#include<QFileDialog>
#include<string>
#include<QMessageBox>
#include"XVideoThread.h"

XVideoUI::XVideoUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);// ���ر�����
	qRegisterMetaType<cv::Mat>("cv::Mat");
	//ԭ��Ƶ��ʾ�ź�
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.src1video,
		SLOT(SetImage(cv::Mat))
		);

	//�����Ƶ��ʾ�ź�
	QObject::connect(XVideoThread::Get(),
		SIGNAL(ViewDes(cv::Mat)),
		ui.des,
		SLOT(SetImage(cv::Mat))
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
	// ���´򿪰�ť�󣬴�һ����Ƶ�ļ�
	// fromLocal8Bit ��ֹ���ĳ�������
	// tolocal8Bit ��·���г�������ʱ��ͬ��ת��Ϊ���ĵ��ַ���
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("���һ����Ƶ�ļ�"));//�ú���Ҳ���������ļ����͵�
	if (name.isEmpty()) return;
	std::string file = name.toLocal8Bit().data();

	//XVideoThread����Ƶ
	//XVideoThread xv;//��Ϊ���캯��protected���ͣ����ܷ��ʡ�
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
// ���ù�����
void XVideoUI::Set() {
	XFilter::Get()->Clear();
	//�ԱȶȺ�����
	if (ui.bright->value() > 0 || ui.contrast->value() > 1) {
		XFilter::Get()->Add(XTask{ XTASK_GAIN,
		{(double)ui.bright->value(),ui.contrast->value()}
		});
	}
}