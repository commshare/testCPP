
#include <iostream>

struct iRoomParam {
	iRoomParam(void) {
	
		nMicIndex = nPlayerIndex = nCameraIndex = 0;
		isCameraExternal = true;
		hWindow = 0;
		nWidth = nHeight = 0;
		nCodeRate = 0;
		nFrameRate = 0;
		nOpenVideoEnhance = 0;
		nVideoEnhanceNoise = 0;
		nVideoEnhanceSharp = 0;
	}
	int nMicIndex;///< mic的索引，默认值0，-1不打开
	int nPlayerIndex;///< player的索引,默认值0，-1不打开
	int nCameraIndex;///< camera的索引,默认值0，-1不打开
	bool isCameraExternal;///< 是否取出摄像头裸流
	void* hWindow;///< 窗口句柄

	int nWidth;///< 视频大小，0为使用默认值
	int nHeight;///< 视频大小，0为使用默认值
	int nCodeRate;///< 视频码率，0为使用默认值 
	int nFrameRate;///< 视频帧率，0为使用默认值
	int nOpenVideoEnhance;///< 是否视频增强，0为使用默认值，1打开，-1关闭
	int nVideoEnhanceNoise;///< 平滑度
	int nVideoEnhanceSharp;///< 清晰度
};
int main()
{
	struct iRoomParam c;
	c.nCodeRate = 1200;
	struct iRoomParam  r;
	r =c;
	std::cout <<"r "<<r.nCodeRate <<std::endl;
	return 0;
}
