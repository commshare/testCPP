#include <iostream>
#include <tuple>
#include <string>
 
using namespace std;
 
static int cnt = 0;
 
class Person {
 
private:
    int id; 
 
public:
    string name;
    int age;
 
    Person()  {
        id = ++cnt;
        cout << "Person()" << id <<endl;
    }
 
    Person(string _name, int _age): name(_name), age(_age) {
        id = ++cnt;
        cout << "Person(string _name, int _age)" << id << endl;
    }
 
    Person(const Person&) {
        id = ++cnt;
        cout << "Person(const Person&)" << id << endl;
    }
 
    Person(Person&&) {
        id = ++cnt;
        cout << "Person(Person&&)" << id << endl;
    }
 
    Person& operator=(const Person&) {
        cout << "operator=(const Person&)" << id << endl;
 
        return *this;
    }
 
};
 
int main () {
  {
    cout << "--------------------------------//(1)" << endl;
    tuple<int, bool, string, Person> t1 = tuple<int, bool, string, Person>(11, true, "ok", Person("ok", 11));
  }
  {
    cout << "--------------------------------//(2)" << endl;
    Person p("ok", 11);
    tuple<int, bool, string, Person> t2 = tuple<int, bool, string, Person>(11, true, "ok", p);
  }
  {
    cout << "--------------------------------//(3)" << endl;
    tuple<int, bool, string, Person> t3 = std::forward_as_tuple(11, true, "ok", Person("ok", 11));
  }
  {
    cout << "--------------------------------//(4)" << endl;
    Person p("ok", 11);
    tuple<int, bool, string, Person> t4 = std::forward_as_tuple(11, true, "ok", p);
  }
  {
    cout << "--------------------------------//(5)" << endl;
    tuple<int, bool, string, Person> t5 = std::make_tuple(11, true, "ok", Person("ok", 11));
  }
  {
    cout << "--------------------------------//(6)" << endl;
    Person p("ok", 11);
    tuple<int, bool, string, Person> t6 = std::make_tuple(11, true, "ok", p);
  }
    {
        cout << "--------------------------------//(7)" << endl;
        int i = 11;
        bool b = true;
        string s = "ok";
        Person p("ok", 11);
        tuple<int, bool, string, Person> t7 = std::tie(i, b, s, p);
    }
  
  return 1;
}
