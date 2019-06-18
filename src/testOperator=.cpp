#include <stdio.h>
//±ÜÃâÀàÐÍ³åÍ»
//typedef char				int8;
typedef short				int16;
typedef int					int32;
typedef long long			int64;
typedef signed long long	int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;
struct PSMBase {
public:
		PSMBase()
	{
		this->appId = 0;
		this->from = 0;
		this->sid = 0;
		this->uid = 0;
		this->ver = 0;
	}
	PSMBase& operator = (const PSMBase &b)
	{
		this->appId = b.appId;
		this->from = b.from;
		this->sid = b.sid;
		this->uid = b.uid;
		this->ver = b.ver;
		return *this;
	}
	PSMBase(PSMBase &b)
	{
		this->appId = b.appId;
		this->from = b.from;
		this->sid = b.sid;
		this->uid = b.uid;
		this->ver = b.ver;
	}
	PSMBase(uint32 sid, uint32 uid, uint32 appId, uint32 ver, uint32 from)
	{
		this->sid = sid;
		this->uid = uid;
		this->appId = appId;
		this->ver = ver;
		this->from = from;
	}
	~PSMBase(){	};
public:
	uint32 sid;
	uint32 uid;
	uint32 appId;
	uint32 ver;
	uint32 from;
};

class ttt 
{
	public:
	ttt(PSMBase b)
	{
		p = b;
	}
	PSMBase p;
};

int main()
{
	PSMBase b ;
	b.appId = 100;
	ttt t(b);
	printf(" %d \n",t.p.appId);
	return 0;
}
