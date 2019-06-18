
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
	int nMicIndex;///< mic��������Ĭ��ֵ0��-1����
	int nPlayerIndex;///< player������,Ĭ��ֵ0��-1����
	int nCameraIndex;///< camera������,Ĭ��ֵ0��-1����
	bool isCameraExternal;///< �Ƿ�ȡ������ͷ����
	void* hWindow;///< ���ھ��

	int nWidth;///< ��Ƶ��С��0Ϊʹ��Ĭ��ֵ
	int nHeight;///< ��Ƶ��С��0Ϊʹ��Ĭ��ֵ
	int nCodeRate;///< ��Ƶ���ʣ�0Ϊʹ��Ĭ��ֵ 
	int nFrameRate;///< ��Ƶ֡�ʣ�0Ϊʹ��Ĭ��ֵ
	int nOpenVideoEnhance;///< �Ƿ���Ƶ��ǿ��0Ϊʹ��Ĭ��ֵ��1�򿪣�-1�ر�
	int nVideoEnhanceNoise;///< ƽ����
	int nVideoEnhanceSharp;///< ������
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
