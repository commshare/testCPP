#include <iostream>
 #include <stdint.h>

using namespace std;

struct home{
	int f;
	int m;
};

struct kevent64_s {
	uint64_t	ident;		/* identifier for this event */
	int16_t		filter;		/* filter for event */
	uint16_t	flags;		/* general flags */
	uint32_t	fflags;		/* filter-specific flags */
	int64_t		data;		/* filter-specific data */
	uint64_t	udata;		/* opaque user data identifier */
	uint64_t	ext[2];		/* filter-specific extensions */
};

void setll(long long data){
	struct kevent64_s s;
	s.udata = data;
	cout <<"udata ll " <<s.udata <<endl;
}

void set(uint64_t data){
	struct kevent64_s s;
	s.udata = data;
	cout <<"udata uint64_t " <<s.udata << endl;
}
int main(){
	struct home h;
	h.f = 10;
	h.m= 100;
	struct home * p = &h;
	uint64_t udata ;
	udata=(uint64_t) p;
	struct home *ph = (struct home *) udata;
	std::cout << "udata "<< ph->f <<ph->m <<endl;
	setll(0);
	set(0);
	return 0;
}
