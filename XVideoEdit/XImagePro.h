#pragma once
#include<opencv2\core.hpp>

class XImagePro
{
public:
	//����ԭͼ���������ϴεĴ�����
	void Set(cv::Mat mat1, cv::Mat mat2);

	//��ȡ�������
	cv::Mat Get() { return des; }

	//�������ȺͶԱȶ�
	///@para bright double ����0~100
	///@para contrast double �Աȶ�1.0~3.0
	void Gain(double bright, double contrast);
	XImagePro();
	~XImagePro();
private:
	//ԭͼ
	cv::Mat src1, src2;

	//Ŀ��ͼ
	cv::Mat des;
};

