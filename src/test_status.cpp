#include <stdio.h>
#include <stdint.h>
class EYStatus
	{
public:
		void muteVideo(bool local, bool mute)
		{
			if (mute) //close video
			{
				if (local) //mute local video
				{
					status_ = status_ & 0x0111;
				}
				else //mute remote video
				{
					status_ = status_ & 0x1101;
				}
			}
			else //open video
			{
				if (local) //open local video
				{
					status_ = status_ | 0x1000;
				}
				else //open remote video
				{
					status_ = status_ | 0x0010;
				}
			}
		}
		uint16_t getstatus() { return status_; }
	private:
		//lv la rv ra
		uint16_t status_ = 0x1111;
	};
	
	struct aaa
	{
		//aaa() {
		//	hh =true;
		//	cc= true;
		//}
		bool hh;
		bool cc;
	};
	
	int main()
	{
		aaa a;
		printf("hh %d cc %d \n",a.hh,a.cc);
		EYStatus e;
		e.muteVideo(true,true); //111
		e.muteVideo(true,false);//1111
		e.muteVideo(true,true); //111
		e.muteVideo(false,false);//111
		e.muteVideo(false,true);//101
		e.muteVideo(false,false);//111
		printf("status %x \n",e.getstatus() );
		return 0;
	}
