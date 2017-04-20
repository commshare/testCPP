// http://mashuai.blog.51cto.com/700343/267718

#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
 
 void display(vector<int> vec){
     cout<<"display all item "<<endl;
     vector<int>::iterator it;
     for(it = vec.begin();it!=vec.end();++it){
         cout<<"cur *it :" << *it<<std::endl;
     }
 }
void fun()

{

    vector<int> iVec;

    vector<int>::iterator it;

    for(int i=0;i<10;i++)

        iVec.push_back(i);

    display(iVec);

    for(it=iVec.begin();it!=iVec.end();++it)

    {

        if(*it ==4 || *it == 7)

        {
            cout<<"delete item " << *it <<endl;    
            it=iVec.erase(it); //这里erase 4 之后，it会后移一个位置到5，for 会到6，然后后走else 变为7 ， for变为8，这样就跳过了7
            cout<<"cur item " << *it<<endl;

        }

        else

            ++it;

    }

    display(iVec);

}

void fun2()

{

    vector<int> iVec;

    vector<int>::iterator it;

    for(int i=0;i<10;i++)

        iVec.push_back(i);

    display(iVec);

    for(it=iVec.begin();it!=iVec.end();++it)

    {

        if(*it ==4 || *it == 7)

        {
            cout<<"delete item " << *it <<endl;    
            it=iVec.erase(it);
            cout<<"cur item " << *it<<endl;    

             --it;//这里回退一个
              cout<<"after --it : cur item " << *it<<endl;
              cout<<"cur item " << *it<<endl;    
        }

    }

    display(iVec);

}
int main()
{
    vector<int> arr;
    arr.push_back(6);
    arr.push_back(7);
    arr.push_back(8);
    arr.push_back(9);

    for(vector<int>::iterator it=arr.begin(); it!=arr.end(); )
    {
        if(* it == 8)
        {
            it = arr.erase(it);  //要这样erase，要返回
             cout <<"cur it: "<< * it << std::endl;
        }
        else
        {
            ++it;
        }
    }

    //注意上面不能写成

    /*
        for(vector<int>::iterator it=arr.begin(); it!=arr.end(); it ++)
        {
            if(* it == 8)
            {
                arr.erase(it); //在erase后，it失效，并不是指向vector的下一个元素，it成了一个“野指针”。

            }
        }
      
    */

    cout << "After remove 8:\n";
   
     cout <<  " -------show vector ---------";
    for(vector<int>::iterator it = arr.begin(); it < arr.end(); ++it)
    {
        cout << * it << " ";
    }
    cout << endl << arr.size();
    cout << endl;

    cout<<" call func : " <<endl;

    fun();
    fun2();
    getchar();
}
 