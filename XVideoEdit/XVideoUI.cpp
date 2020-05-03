#include "XVideoUI.h"
#include<QFileDialog>
#include<string>
#include<QMessageBox>
#include"XVideoThread.h"

XVideoUI::XVideoUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//setWindowFlags(Qt::FramelessWindowHint);// ���ر�����
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
		QMessageBox::information(this, "Error:", name+"open failed");
	}
	else
		QMessageBox::information(this, "Error:", name + "open succeed");
	//QMessageBox::information(this, "", name);
}