#include <memory>

class AA{
public:
AA(){}
~AA(){}

private:
int a;
};



int main()
{
	using TT = std::shared_ptr<AA> ;
	TT  aptr;
	//ERR
//	aptr = std::make_shared<AA>(new AA());

//OK
aptr = std::shared_ptr<AA>(new AA());

//OK
	aptr = std::make_shared<AA>();
//ERR
  //  aptr = new AA();
	return 0;
}
