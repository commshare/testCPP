/*http://www.cplusplus.com/reference/string/string/insert/*/
// inserting into a string
#include <iostream>
#include <string>

int main ()
{
  std::string str="to be question";
  std::string str2="the ";
  std::string str3="or not to be";
  std::string::iterator it;
/*
Insertion point: The new contents are inserted before the character at position pos.
If this is greater than the object's length, it throws out_of_range.
Note: The first character is denoted by a value of 0 (not 1).
*/
  // used in the same order as described above:
  str.insert(6,str2);                 // to be (the )question
  std::cout << str << '\n';
  str.insert(6,str3,3,4);             // to be (not )the question
  str.insert(10,"that is cool",8);    // to be not (that is )the question
  str.insert(10,"to be ");            // to be not (to be )that is the question
  str.insert(15,1,':');               // to be not to be(:) that is the question
  it = str.insert(str.begin()+5,','); // to be(,) not to be: that is the question
  str.insert (str.end(),3,'.');       // to be, not to be: that is the question(...)
  str.insert (it+2,str3.begin(),str3.begin()+3); // (or )

  std::cout << str << '\n';
  return 0;
}