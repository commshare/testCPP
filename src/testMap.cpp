#include<map>
#include<string>
#include<iostream>
using namespace std;

void map_insert(map<string,string> *mapStudent, string index, string x){
	mapStudent->insert(map<string,string>::value_type(index,x));
}

int main(int argc,char *argv[]){
	char tmp[32]="";
	map<string,string> mapS;
	
	//insert
	map_insert(&mapS,"192.168.1","zhang");
	map_insert(&mapS,"192.168.2","wang");
	map_insert(&mapS,"192.168.3","shao");

	map<string,string> ::iterator iter;
	cout<< "after insert three 3 elements " <<endl;
	cout<<"--------"<<mapS.size()<<"-------"<<endl;
	
	//find 
	iter= mapS.find("192.168.3");
	if(iter != mapS.end()){
		cout<<"find it "<<endl;
		cout<<"it is "<<iter->second<<endl;
	}else{
		cout << "not find it "<<endl;
	}
	

	//see element
	for(iter = mapS.begin(); iter!= mapS.end();iter++){
		cout<<"|"<<iter->first<<"|"<<iter->second<<"|"<<endl;		
	}
	cout << "----------------"<<endl;
	
#if 1	
	map_insert(&mapS,"192.168.99","china");
	cout << "after insert 99 "<<endl;
	cout<<"------------"<<endl;
	for(iter = mapS.begin(); iter!= mapS.end();iter++ ){
		cout<<"| "<< iter->first  <<" |" <<iter->second <<" |" <<endl;
	}
	cout <<endl;
	
	//delete
	iter=mapS.find("192.168.2");
	if(iter != mapS.end()){
		cout <<"find ["<<iter->first<<"]"<<endl;
		cout<<"delete it "<<endl;
		mapS.erase(iter);
	}else
		cout<<"not find"<<endl;
		
	cout<<"---------output all "<<endl;
	for(iter = mapS.begin();iter!=mapS.end();++iter){
		cout<<"| " <<iter->first <<" |" <<iter->second<<endl;
		
	}
#endif
	return 0;
}
