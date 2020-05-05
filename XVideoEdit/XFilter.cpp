#include "XFilter.h"
#include<QThread>
#include<QMutex>

class CXFilter :public XFilter {
public:
	std::vector<XTask> tasks;
	QMutex mutex;
	cv::Mat Filter(cv::Mat mat1, cv::Mat mat2) {
		mutex.lock();
		XImagePro p;
		p.Set(mat1, mat2);
		for (int i = 0; i < tasks.size(); ++i) {
			switch (tasks[i].type)
			{
			case XTASK_GAIN:
				p.Gain(tasks[i].para[0], tasks[i].para[1]);
				break;
			default:
				break;
			}
		}
		cv::Mat re = p.Get();
		mutex.unlock();
		return re;
	}

	void Add(XTask task) {
		mutex.lock();
		tasks.push_back(task);
		mutex.unlock();
	}

	void Clear() {
		mutex.lock();
		tasks.clear();//直接把列表清零即可
		mutex.unlock();
	}
};

XFilter *XFilter::Get() {
	static CXFilter cx;
	return &cx;
}

XFilter::XFilter()
{
}


XFilter::~XFilter()
{
}
