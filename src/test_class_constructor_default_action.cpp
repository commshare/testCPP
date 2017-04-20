#include <iostream>
#include <cstdio>
#include <sys/types.h>

#define URI_TYPE int 

// class Pack
// {
// private:
//   Pack (const Pack & o);
//   Pack & operator = (const Pack& o);
// public:
//   uint16_t xhtons(uint16_t i16)
//   {
//     return XHTONS(i16);
//   }
//   uint32_t xhtonl(uint32_t i32)
//   {
//     return XHTONL(i32);
//   }
//   uint64_t xhtonll(uint64_t i64)
//   {
//     return XHTONLL(i64);
//   }

//   // IMPORTANT remember the buffer-size before pack. see data(), size()
//   // reserve a space to replace packet header after pack parameter
//   // sample below: OffPack. see data(), size()
//   Pack(PackBuffer & pb, size_t off = 0) : m_buffer(pb)
//   {
//     m_offset = pb.size() + off;
//     m_buffer.resize(m_offset);
//   }

//   // access this packet.
//   char * data()
//   {
//     return m_buffer.data() + m_offset;
//   }
//   const char * data()  const
//   {
//     return m_buffer.data() + m_offset;
//   }
//   size_t size() const
//   {
//     return m_buffer.size() - m_offset;
//   }

//   Pack & push(const void * s, size_t n)
//   {
//     m_buffer.append((const char *)s, n); return *this;
//   }
//   Pack & push(const void * s)
//   {
//     m_buffer.append((const char *)s); return *this;
//   }

//   Pack & push_uint8(uint8_t u8)
//   {
//     return push(&u8, 1);
//   }
//   Pack & push_uint16(uint16_t u16)
//   {
//     u16 = xhtons(u16); return push(&u16, 2);
//   }
//   Pack & push_uint32(uint32_t u32)
//   {
//     u32 = xhtonl(u32); return push(&u32, 4);
//   }
//   Pack & push_uint64(uint64_t u64)
//   {
//     u64 = xhtonll(u64); return push(&u64, 8);
//   }

//   Pack & push_varstr(const Varstr & vs)
//   {
//     return push_varstr(vs.data(), vs.size());
//   }
//   Pack & push_varstr(const void * s)
//   {
//     return push_varstr(s, strlen((const char *)s));
//   }
//   Pack & push_varstr(const std::string & s)
//   {
//     return push_varstr(s.data(), s.size());
//   }
//   Pack & push_varstr(const void * s, size_t len)
//   {
//     if(len > 0xFFFF) throw PackError("push_varstr: varstr too big");
//     return push_uint16(uint16_t(len)).push(s, len);
//   }
//   Pack & push_varstr32(const void * s, size_t len)
//   {
//     if(len > 0xFFFFFFFF) throw PackError("push_varstr32: varstr too big");
//     return push_uint32(uint32_t(len)).push(s, len);
//   }
// #ifdef WIN32
//   Pack & push_varwstring32(const std::wstring &ws)
//   {
//     size_t len = ws.size() * 2;
//     return push_uint32((uint32_t)len).push(ws.data(), len);
//   }
// #endif

//   virtual ~Pack()
//   {
//   }
// public:
//   // replace. pos is the buffer offset, not this Pack m_offset
//   size_t replace(size_t pos, const void * data, size_t rplen)
//   {
//     m_buffer.replace(pos, (const char*)data, rplen);
//     return pos + rplen;
//   }
//   size_t replace_uint8(size_t pos, uint8_t u8)
//   {
//     return replace(pos, &u8, 1);
//   }
//   size_t replace_uint16(size_t pos, uint16_t u16)
//   {
//     u16 = xhtons(u16);
//     return replace(pos, &u16, 2);
//   }
//   size_t replace_uint32(size_t pos, uint32_t u32)
//   {
//     u32 = xhtonl(u32);
//     return replace(pos, &u32, 4);
//   }
// protected:
//   PackBuffer & m_buffer;
//   size_t m_offset;
// };


/**
 * Abstract base class for all objects that can be marsrhalled and
 * unmarshalled .
 */

// struct Marshallable 
// {
//   /* 返回输出的字节数*/
//   virtual void marshal(Pack &) const = 0;
//   /* 成功返回非0,否则返回0 */
//   virtual void unmarshal(const Unpack &) = 0;
//   virtual ~Marshallable()
//   {
//   }
//   virtual std::ostream & trace(std::ostream & os) const
//   {
//     return os << "trace Marshallable [ not immplement ]";
//   }
// };

class MYPackBuffer{
    public :
        MYPackBuffer(){
            std::cout<<"this is the contructor of MYPackBuffer()" <<std::endl;
        }
        std::string data(){
            return name;
        }
        void setData(std::string name){
            this->name=name;
        }
    private:
        std::string name;
};

struct Header{
    public:
    //uint32_t 
    int length;
    URI_TYPE uri;
    //uint16_t 
    int code;
    
    public:
        Header():length(),code(200),mpb(){}   /*length初始化的括号是空的，打印出来是0*/
       //	uint32_t
       int getLength(){
		    return length;
	    }
        std::string testMYPackBuffer(){
            std::string name ="my name is zhangbin";
            mpb.setData(name);
            return mpb.data();
        }
    private:
        MYPackBuffer mpb;

};

// struct FrameData : public Marshallable
// {
 

//   uint32_t id;
//   uint32_t roomid;
//   std::string frame; 
//   uint32_t flag;

//   /*可以根据身份证id找到房号roomid*/
//   std::map<uint32_t,uint32_t> mapRoom;//key:id  values: roomid
//   FrameData() : flag(0) {};

//   virtual void marshal(Pack &p) const  /*感觉是一个打包的操作？*/
//   {
//     p << id << roomid << frame << flag;
//     marshal_container(p, mapUidTime);    
//   }
//   virtual void unmarshal(const Unpack &up)
//   {
//     up >> sid >> timeStamp >> uid >> frameId >> frame;
//     if (!up.empty())
//     {
//       up >> flag;
//     }
//     if (!up.empty() && (up.size() >= 2 * sizeof(uint32_t)))
//     {
//       up >> appid;
//       up >> dts;
//     }
//     if(!up.empty())
//     {
//       unmarshal_container(up, std::inserter(mapUidTime, mapUidTime.end()));
//     }
//   }
// };
struct Sender : public Header
{
    public :
        Sender();
    
};
int main(){

    Header test;
    std::cout<<"length init : " << test.getLength() << std::endl;  //0 
    std::cout<<"class MYPB init : "<<test.testMYPackBuffer();  //打印出来了，说明（）也是初始化了类的实例
    getchar();
}