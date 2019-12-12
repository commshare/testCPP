#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOMAINLEN 1024
#define IPLEN 128

extern "C" {
	enum IpProperty {
		LOCAL_DNS = 0,
		LOCAL_CACHE = 1,
		GSLB_SVR = 2,
	};
	struct DomainIps
	{
		char domain[DOMAINLEN] ;
		IpProperty ippro;
		char ips[3][100] ;

	};
	/**
	 * get ip from a domain
	 */
	int getIpByDomain(const char* domain, char ip[])
	{

	}
	
	int main()
	{
		return 0;
	
	}
	
}
