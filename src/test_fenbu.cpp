//https://github.com/jungheenam/shekqtlr/blob/master/12.18/HJHDirectX%20(12.18%20??)/HJHDirectX/P02_PlayerStat.cpp 

//[0,30) [30,50) [50,80) [80,120) [120,200) >=200
 #include <stdint.h>
#include <iostream>
#include <sstream>
using namespace std;

class P02_PlayerStat 
{
private:
	struct tagSTAT
	{
		uint64_t _A;
		uint64_t _B;
		uint64_t _C;
		uint64_t _D;
		uint64_t _E;
		uint64_t _F;
	};
	tagSTAT stat; //·Ö²¼ 

public:
	P02_PlayerStat();
	~P02_PlayerStat();
	void clearStat();
	void Update(uint64_t v);

	tagSTAT getStat() { return stat; }
	string getStatStr() { 
		ostringstream os;
		os<<stat._A << " " <<stat._B <<" " <<stat._C <<" "<<stat._D <<" "<<stat._E <<" "<<stat._F <<" "<<endl;
		return os.str() ;// .c_str()
	 }
   void dump(std::ostringstream& os);
};

P02_PlayerStat::P02_PlayerStat()
{
	clearStat();
}

void P02_PlayerStat::clearStat(){
	stat._A = 0;
	stat._B =0;
	stat._C =0;
	stat._D =0;
	stat._E =0 ;
	stat._F =0; 
}

P02_PlayerStat::~P02_PlayerStat()
{
	std::cout <<"de structor "<<endl;
}
//[0,30) [30,50) [50,80) [80,120) [120,200) >=200
void P02_PlayerStat::Update(const uint64_t v)
{
	//cout<<"V :"<<v<<endl;
	if( v >= 0) {
		if( 0 <= v && v <30 ){
			stat._A ++ ;
		}else{
			if( 30 <= v && v <50 ){
				stat._B ++ ;
			}else{
				if( 50 <= v && v < 80 ){
					stat._C ++;
				//	cout<<"c++"<<endl;
				}else{
					if( 80 <= v && v < 120 ){
					//	cout<<"D++"<<endl;
						stat._D ++ ;
					}else{
						if( 120 <= v && v< 200){
						//	cout<<"E++"<<endl;
							stat._E ++ ;
						}else{
							if( v >=200 ){
							//	cout<<"F++"<<endl;
								stat._F ++;
							}else{
								std::cout <<"error v"<<endl;
							}
						}
					}
				}
			}
		}
	}else{
		std::cout <<"error v "<<v <<endl;
	}
}
void P02_PlayerStat::dump(std::ostringstream& os){
     os << "Distribution [0,30) "<<stat._A <<" ; [30,50) "<<stat._B<<"; [50,80) "<<stat._C <<";  [80,120) "<<stat._D <<" ;  [120,200)"<<stat._E<<";  >=200 ms "<<stat._F <<std::endl;
}
int checkD(uint64_t  v){
	cout<< "check :"<<v <<endl;
	if (v > 80 ) {
		cout<<"v >80" <<v <<endl;
	}
		if( 50 <= v && v < 80 ){
			cout<<"v  [50,80)  "<<v<<endl;
		}else{
			cout<<"v >= 80"<<v<<endl;
		}
	return 0;
}
void dump(std::ostringstream& os,P02_PlayerStat st){
	os<<"china :" ;
	st.dump(os);
}
int main(){
	P02_PlayerStat st;
	//[0,30) [30,50) [50,80) [80,120) [120,200) >=200
	st.Update(20);
	st.Update(40);
	st.Update(60);
	st.Update(100);
	st.Update(190);
	st.Update(220);
	std::cout <<"stat: "<< st.getStatStr()<<endl;

	st.clearStat();
	for(int i=0;i<300;i++){
		st.Update(i);
	}
	std::cout <<"stat: "<< st.getStatStr()<<endl;
	checkD(100);
		std::ostringstream os;
	dump(os,st);
	cout <<"os :"<<os.str()<<endl;
}


string convertInt(int num)
{
    std::stringstream ss;   // <-- also note namespace qualification
    ss << num;
    return ss.str();
}

