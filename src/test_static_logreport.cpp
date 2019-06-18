
#include <memory>

using WebLogFunc = std::function<void(int, const char* msg)>;
class TT{
	public:
		static WebLogFunc logfunc ;
		TT(){
			
		}
		~TT()
		{
		}
};

WebLogFunc TT::logfunc = nullptr;

int main()
{
	return 0;
}
