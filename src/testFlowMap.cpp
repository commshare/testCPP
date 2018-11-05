#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
using namespace std;
 /**/
 /**/
 /*http://thispointer.com/stdmap-tutorial-part-1-usage-detail-with-examples/*/

enum RECORDSOURCE
{ 
    // invalid record source 
    RECORD_SOURCE_INVALID       = 0,

    // from client
    RECORD_SOURCE_CLIENT_COMMON = (1 << (24 + 0)),
    RECORD_SOURCE_CLIENT_PC_COMMON  =  RECORD_SOURCE_CLIENT_COMMON | (1 << (16 + 0)),
    RECORD_SOURCE_CLIENT_MOB_COMMON =  RECORD_SOURCE_CLIENT_COMMON | (1 << (16 + 1)),
    RECORD_SOURCE_CLIENT_SVC_COMMON =  RECORD_SOURCE_CLIENT_COMMON | (1 << (16 + 2)),

    // from bussiness server
    RECORD_SOURCE_SERVER_COMMON = (1 << (24 + 1)),

    // trigger by record system itself
    RECORD_SOURCE_SYSTEM_COMMON = (1 << (24 + 2)),

    // reserved record source 
    RECORD_SOURCE_RESERVE_COMMON = (1 << (24 + 7)),
};


int main()
{
    std::map<std::string, int> mapOfWords;
    // Inserting data in std::map
    mapOfWords.insert(std::make_pair("earth", 1));
    mapOfWords.insert(std::make_pair("moon", 2));
    mapOfWords["sun"] = 3;
    // Will replace the value of already added key i.e. earth
    mapOfWords["earth"] = 4;
    /*这种插入是可以覆盖的*/
    mapOfWords["sun"] = 100;
    /*遍历所有的元素*/
    // Iterate through all elements in std::map
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end())
    {
        std::cout<<it->first<<" :: "<<it->second<<std::endl;
        it++;
    }
    // Check if insertion is successful or not
    if(mapOfWords.insert(std::make_pair("earth", 1)).second == false)
    {
        std::cout<<"Element with key 'earth' not inserted because already existed"<<std::endl;
    }
    // Searching element in std::map by key.
    if(mapOfWords.find("sun") != mapOfWords.end())
        std::cout<<"word 'sun' found"<<std::endl;
    if(mapOfWords.find("mars") == mapOfWords.end())
        std::cout<<"word 'mars' not found"<<std::endl;


/*    std::vector<string> data={"mob","pc","svc"};
    for (std::vector<string>::iterator t=data.begin(); t!=data.end(); ++t) 
    {
        std::cout<<*t<<std::endl;
    }*/
    return 0;
}
enum REJECT_SOURCE{
REJECT_MOBYY =0 ,
REJECT_PCYY,
REJECT_SVCYY,
REJECT_MAX
};

