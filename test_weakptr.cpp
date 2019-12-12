#inlcude <memory>
#include <iostream>
//https://www.jianshu.com/p/26967eb6d8f9
#if 0
class T
{
public:
    ....
    int* getPayLoad() {return (int *)serial_payload.data();}
private:
    std::unique_ptr<std::vector<char>> serial_payload;
};

std::unque_ptr<> read()
{
  char msg[5] = {1, 2, 3, 4, 5};
  auto data = std::make_unique<T>(msg, msg+5);
  return std::move(data);
}

int main()
{
  int * data = read()->getPayLoad();
  printf("data[0] = %d", data[0]);
}




#endif


using namespace std;

void test()
{
	shared_ptr<int> sp(new int(10));
	weak_ptr<int> wp(sp);
	
	cout <<wp.use_count() <<std::endl;
}

int main()
{
	test();
	return 0;
}
