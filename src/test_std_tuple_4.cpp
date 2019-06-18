

int main()
{
std::tuple<int ,float ,size_t > threet;

std::tuple<vector,vector<double>,int ,list<int> > somval ("tuple",{2.11,3.22},100,{1,2,3});

std::tuple<int,int ,double> some {2,3,3.15};

auto itme = std::make_tuple("string",3,30.02);
auto book = get<1> (itme);//返回tuple对象item的第二个成员，从0开始计数

auto sz = tuple_size<decltype(itme)>::value ; //sz 为3

 
return 0;

}
