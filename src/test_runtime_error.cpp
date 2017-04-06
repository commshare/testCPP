#include <stdexcept>

class A {};

class GameException : public A ,public std::runtime_error
{
    public :
    /*
    error: no matching function for call to 'std::runtime_error::runtime_error()'
    */
    /*
    https://github.com/lywaterman/erlmono/blob/36358029e043b6b8069d6032bf69c69df71066b9/c_src/errors.hpp
    */
     GameException():std::runtime_error("hello") {}
     GameException(std::string const&msg):std::runtime_error(msg){}
       using std::runtime_error::runtime_error;

       /*
       https://github.com/dwfait/spacerts/blob/a665a2e97b51c0b92c0f03ec0367c92b375a8347/src/exceptions.h
       */
    public :
        GameException(std::string message):
        std::runtime_error(message)
        {}
        GameException(const char* text) : std::runtime_error(text)
};


int main(){
    GameException x;
//   system("PAUSE");
    return 0;
}