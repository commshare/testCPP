#include "test_template_h.h"
	template<typename ClientT>
Server<ClientT> :: Server(){
	
}
	template<typename ClientT>
Server<ClientT>::~Server(){
	
}




	template<typename ClientT>
void Server<ClientT>::get(){
	return ;	
}

class server_client {
public:
  unsigned int _uid;

public:
  server_client()
      : _uid(0) {
  }

  unsigned int get_uid() const {
    return _uid;
  }
};

int main(){
	Server<server_client> server;
	server.get();
	return 0;
}
