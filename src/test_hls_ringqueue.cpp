#include <iostream>
#include <string>
#include <stdarg.h>
using namespace std;

// 只支持依序往尾部添加元素的固定最大大小的ring queue
template<typename T, int SZ> /* T是一个模板类型,大小固定，是SIZE*/
/*
 * startpos 记录第一个元素的位置
 * nextPos 记录当前可供插入的位置，每次插入，使用nextPos就可以保证
 * */
class RingQueue  /*固定大小的ring，只支持在尾部添加，那么前面的会被覆盖？*/
{
public:
    RingQueue():startpos(-1),nextPos(0) /*起始位置赋值-1，下一个位置是0*/
    {
    };
    T& append(const T& t)
    {
        m_data[nextPos] = t; /*插入使用nextPos，在下nextPos直接插入，好像是一个数组结构呢*/
        return increaseTail();
    };
    // Just like append but no value is needed for tail element
    T& increaseTail()
    {
        T* inserted = &m_data[nextPos];        /*取地址*/
        if (nextPos == startpos) /*TODO 如果当前插入的位置nextPos 等于startpos ，那么startpos 挪动*/
        {

            // overwrite
            startpos = (startpos+1) % SZ; /*假如012，共3个位置，当前nextPos算出来是0，那么重新计算startpos是（0+1）%3 为1，下次插入的位置nextpos是1，又相等？TODO 是的，后面的就一直相等了*/
            std::cout<<"nextPos == startpos :"<<nextPos<<"set startpos to :"<<startpos <<std::endl;
        } 
        else if (startpos == -1) /*首次插入的起始地址设置为0*/
        {
        	std::cout<<"first time set startpos to 0 "<<std::endl;
            startpos = 0; /*首次插入后队列头在0位置*/
        }
        /*每次确定下次可以插入的空位置*/
        nextPos = (nextPos+1) % SZ; /*这是正常的找位子的计算过程，+1 就是下一个要插入的位置，实际的位置要%SZ计算出来，（如012，共3个位置，3就坐在0上，4坐在1上，5在2上）*/
        std::cout<<"increase nextPos to :"<<nextPos<<std::endl;
        return *inserted; /*如果取不出来地址，然后用* 会怎么样呢*/
    };
    inline int size() const
    {
        if (startpos == -1)
            return 0; /*0代表么有*/
        return startpos < nextPos? (nextPos-startpos)/*不相等的时候是所有位置第一次满之前*/ : (nextPos+SZ-startpos) /*此后，缓冲一直是满的，next和start一直是相等的，所以直接返回SZ就ok*/;
    }
    inline T& first()
    {
        return m_data[startpos]; /*start还真一直指向第一个，换句话说TODO 是最久未使用的那个*/
    }
    inline T& end()
    {
    	/*nextpos初始化值为0，第一轮nextpos都大于0，第二轮开始是0，那么返回SZ-1位置*/
        return m_data[nextPos>0? nextPos-1 : SZ-1];
    }
    inline T& nth(int n)    // 第n个元素，0开始,这里不检查边界
    {
        return m_data[(startpos+n) % SZ];  
    }
    inline void reset() // 不清楚具体元素怎么清理，实际清理得由使用者来做
    {
        startpos = -1;
        nextPos = 0;
    }
	inline void show() // 
    {
	      std::cout<<"startpos :"<<startpos<<" nextpos :"<<nextPos<<endl;
	      std::cout<<"end() :" << end()<<std::endl;
	      for(int i=0;i<SZ;i++) {
	      	std::cout<<"show i:"<<i<<" value :"<<m_data[i]<<std::endl;
	      }
    }
private:
    T m_data[SZ]; /*模板类型，大小固定是SZ*/
    int startpos;
    int nextPos;
};
#define MAX_GOP_TAGS 3      // 最多缓存3个GOP的FLV TAGS
typedef     int MYTYPE ;
    
int  main(){
	RingQueue<MYTYPE, MAX_GOP_TAGS> m_queue;

	int i ;
	for(i=0;i<10;i++ ){
		std::cout<<"======="<<std::endl<<"append i ="<<i<<std::endl;
		m_queue.append(i);
		m_queue.show();
	}
	return 0; 
}

/*
$ g++ -o test_hls_ringqueue test_hls_ringqueue.cpp

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/src (master)
$ ./test_hls_ringqueue
=======
append i =0
first time set startpos to 0
increase nextPos to :1
startpos :0 nextpos :1
end() :0
show i:0 value :0
show i:1 value :1984850813
show i:2 value :4200976
=======
append i =1
increase nextPos to :2
startpos :0 nextpos :2
end() :1
show i:0 value :0
show i:1 value :1
show i:2 value :4200976
=======
append i =2
increase nextPos to :0
startpos :0 nextpos :0
end() :2
show i:0 value :0
show i:1 value :1
show i:2 value :2
=======
append i =3
nextPos == startpos :0set startpos to :1
increase nextPos to :1
startpos :1 nextpos :1
end() :3
show i:0 value :3
show i:1 value :1
show i:2 value :2
=======
append i =4
nextPos == startpos :1set startpos to :2
increase nextPos to :2
startpos :2 nextpos :2
end() :4
show i:0 value :3
show i:1 value :4
show i:2 value :2
=======
append i =5
nextPos == startpos :2set startpos to :0
increase nextPos to :0
startpos :0 nextpos :0
end() :5
show i:0 value :3
show i:1 value :4
show i:2 value :5
=======
append i =6
nextPos == startpos :0set startpos to :1
increase nextPos to :1
startpos :1 nextpos :1
end() :6
show i:0 value :6
show i:1 value :4
show i:2 value :5
=======
append i =7
nextPos == startpos :1set startpos to :2
increase nextPos to :2
startpos :2 nextpos :2
end() :7
show i:0 value :6
show i:1 value :7
show i:2 value :5
=======
append i =8
nextPos == startpos :2set startpos to :0
increase nextPos to :0
startpos :0 nextpos :0
end() :8
show i:0 value :6
show i:1 value :7
show i:2 value :8
=======
append i =9
nextPos == startpos :0set startpos to :1
increase nextPos to :1
startpos :1 nextpos :1
end() :9
show i:0 value :9
show i:1 value :7
show i:2 value :8

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/src (master)
$



*/