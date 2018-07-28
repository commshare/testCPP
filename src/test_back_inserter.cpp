//back_inserter()

#include<iostream>
#include<vector>
#include<deque>
#include<set>
#include<list>
#include<algorithm>
#include<iterator>
using namespace std;
int main( int argc ,char **argv)
{
	list<int> int_list;

	//insert elements from 1 to 9 into the first collection : int_list
	for(int i = 1; i <= 9 ; ++i)
		int_list.push_back(i);

	//printf all the elements in the int_list
	list<int>::iterator list_pos;
	cout<<"elements in the int_list now: ";
	for( list_pos = int_list.begin(); list_pos != int_list.end(); ++list_pos)
		cout << *list_pos << ' ';
		cout << endl;

	//copy all the elements of int_list into int_vector by appending them
	vector<int> int_vector;
	copy(int_list.begin(),int_list.end(),back_inserter(int_vector));
	//printf all the elements int the  int_vector
	vector<int>::iterator pos_vector;
	cout<<"elements in the int_vector:";
	for( pos_vector = int_vector.begin(); pos_vector != int_vector.end();++pos_vector)
		cout<< *pos_vector << ' ';
	cout<< endl;

	//copy all the elements of int_list into int_set
	//only inserter that works for associative containers
	set<int> int_set;
	copy(int_list.begin(),int_list.end(),inserter(int_set,int_set.begin()));
	set<int>:: iterator pos_printf_list;
	cout<<"elements of int_set now:";
	for(pos_printf_list = int_set.begin(); pos_printf_list != int_set.end(); ++pos_printf_list)
		cout<< *pos_printf_list << ' ';
		cout<< endl;

	return 0;
}
