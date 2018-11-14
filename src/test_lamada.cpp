
#pragma GCC diagnostic error "-std=c++11"  

/*
[capture list] (params list) mutable exception-> return type { function body }
capture list�������ⲿ�����б�
params list���β��б�
mutableָʾ��������˵���Ƿ�����޸Ĳ���ı���
exception���쳣�趨
return type����������
function body��������
*/
 
#include<iostream>
using namespace std;
void testAuto(){
		//test auto in c++11
    cout<<"hello world!"<<endl;  
    auto i=10;  
    cout<<i<<endl;  
} 

/*
Lambda���ʽ����ʹ����ɼ���Χ�ڵ��ⲿ��������������ȷ����
��ȷ������Щ�ⲿ�������Ա���Lambda���ʽʹ�ã�����ô��������ָ����Щ�ⲿ�����أ�
Lambda���ʽͨ������ǰ��ķ�����[]����ȷָ�����ڲ����Է��ʵ��ⲿ������
��һ����Ҳ�ƹ�Lambda���ʽ���������ⲿ������
*/
void testLamada()
{
	//ֵ����
	int a= 123;
	//ע��ĩβ�ģ� 
	auto f= [a] { cout <<a <<endl;} ;
	f(); //123
	
	//��ͨ���������塱����ġ�()���������
	/*���벻������
	25	45	E:\mycode\testCPP\src\test_lamada.cpp	[Error] 'void x' has incomplete type
	*/
	 //auto x = [](int a){cout << a << endl;}(123); 
	 //�����������Ա������������ô���ⲿ����aΪ123���ݽ�ȥ���� TODO
	 auto x = [](int a){cout << a << endl;}; 
	 
	 //���ò��� ���ò���ı���ʹ�õ�ʵ���Ͼ��Ǹ��������󶨵Ķ���
	 a =888;
	 auto ff = [&a] {cout << a <<endl;} ;
	 ff(); //888
	 a =999;
	 ff(); //999
	 
	 //��ʽ����
	 /*
	 �����ֵ��������ò�����Ҫ�����ڲ����б�����ʾ�г�Lambda���ʽ��ʹ�õ��ⲿ������
	 ����֮�⣬���ǻ������ñ��������ݺ������еĴ������ƶ���Ҫ������Щ������
	 ���ַ�ʽ��֮Ϊ��ʽ����
	 ��ʽ���������ַ�ʽ���ֱ���[=]��[&]��[=]��ʾ��ֵ����ķ�ʽ�����ⲿ������
	 [&]��ʾ�����ò���ķ�ʽ�����ⲿ������
	 */
	 a= 555;
	 auto f3 = [=] {cout << a << endl;} ;//ֵ����
	 a=777;
	 f3();  //��ӡ����555������777 

	 //��ʽ���ò���ʾ����
	 auto f4 =[&] {cout << a <<endl;};
	 a=1000;
	 f4(); //��ӡ����1000 
	 
	 
	 /*
	 �޸Ĳ������
ǰ�������ᵽ������Lambda���ʽ�У�����Դ�ֵ��ʽ�����ⲿ�������������в����޸ĸ��ⲿ������
����������������
��ô��û�а취�����޸�ֵ������ⲿ�����أ����Ǿ���Ҫʹ��mutable�ؼ��֣�
�ùؼ�������˵�����ʽ���ڵĴ�������޸�ֵ����ı���
	 */ 
	 a=798;
	 auto f5 = [a]() mutable { cout << ++a ;} ;//
	 cout << a << endl; //798
	 f5();//799 ���޸��� 
} 
void testLambdaParam()
{
	// []	�������κ��ⲿ����
	/*
	Lambda���ʽ�Ĳ���
Lambda���ʽ�Ĳ�������ͨ�����Ĳ������ƣ���ô����Ϊʲô��Ҫ�ó���˵һ���أ�ԭ������Lambda���ʽ�д��ݲ�������һЩ���ƣ���Ҫ�����¼��㣺

�����б��в�����Ĭ�ϲ���
��֧�ֿɱ����
���в��������в�����
*/
  int m = [] (int x ) 
  { 
  	return [] (int y) 
	  {
  		return y *2 ; 
 	  } 
 	  (x) + 6 ;
   }
   (5);
   //�����������ģ�5���ǵ�һ������������x��Ȼ��x��Ϊ�ڲ��Ǹ�����������y����
   //���������������ͷ���5*2 ,��һ�����������ĺ������� return 10+6 
   //16
   std::cout << " m :" << m <<std::endl;
   
   //9
   std::cout <<"n: "<< [](int x,int y) {return x+y ;} (5,4) <<std::endl;
   
   //[=]	��ֵ����ʽ���������ⲿ����
   //113	39	E:\mycode\testCPP\src\test_lamada.cpp	[Error] expected '{' before '<' token ���벻���� 
    //auto gFunc = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
//   auto gf = [] (int x) -> function <int (int) > { 
//   return [=] (int y) { return x+y; } ;
//   };
//   auto lf = gf(4);
   std::cout << lf(5) << std::endl;
   
}
class AAA{
	public:
		bool operator(int i) const {return i>50;}
};

void test1()
{
	vector<int > vec;
	//1 simple lambda 
	auto it = std::find_if(vec.begin(),vec.end(), [] (int i) {return i>50;
	});
	
	auto it2 = std::find_if(vec.begin(),vec.end(), AAA());
	
	//2 LAMBDA RETURN SYNTAX
	std::function < int (int ) > square = [] (int i) -> int {return i*i;}
	
	
	
}

//https://www.cnblogs.com/yyxt/p/4253088.html
int main()
{
	testAuto();
    
    //testLamada �����ⲿ���� 
    testLamada();
    testLambdaParam();
    
    return 0;  
}

