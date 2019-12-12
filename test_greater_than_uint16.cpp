#include <iostream>

int main()
{
	
	//uint16的最大值是 65536吧
	 
   uint16_t a = 1;
   uint16_t b = 2;
   
   //1 - 2 是65536 
   uint16_t c = (uint16_t)(a-b);
      std::cout <<"c  "<<c <<std::endl;
      
      //2 -1 就是 1  
      uint16_t d = (uint16_t)(b-a);
   std::cout <<"d  "<<d <<std::endl;
   
   
      // -2 是65534 
      uint16_t e = (uint16_t)(-2);
      std::cout <<"e  "<<e <<std::endl;


      // -65536  是0
      uint16_t f = (uint16_t)(0 - 65536);
      std::cout <<"f  "<<f <<std::endl;
      
      
            // -65535  是1
      uint16_t g = (uint16_t)(0 - 65535);
      std::cout <<"g  "<<g <<std::endl;
}
