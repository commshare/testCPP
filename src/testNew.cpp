#include<iostream>
using namespace std;

class CTest { public : int a;};
class CBest { public : int b; /*default 0*/
};

CTest *fun(CBest * pBest){
	CTest *pTest= new CTest();
	pTest->a = pBest->b;
	return pTest;
}
int main(){
	CBest * pBest = new CBest();
	if(pBest != NULL){
		pBest->b=10;
		
	}
	CTest *pRes= fun(pBest);
	if(pBest != NULL )
		delete pBest;
	if(pRes!=NULL){
		cout<< pRes->a << endl;
		delete pRes;
	}
	return 0;
}
