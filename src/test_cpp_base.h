#define STR(x) (((string)(x)).c_str())  

#define MAP_HAS1(m,k) ((bool) ((m).find((k))!=(m).end()) )

#define MAP_HAS2(M,k1,k2) (\
(MAP_HAS1((m),(k1)) == true ) ? MAP_HAS1((m)[(k1)],(k2),(k3)) : false \
      )

#define MAP_HAS3(m,k1,k2,k3) (\
	(MAP_HAS1((m),(k1))==true)? MAP_HAS2((m)[(k1)],(k2),(k3)) : false \
)

#define FOR_MAP(m,k,v,i) for( map<k,v> :: iterator i = (m).begin() ; i!= (m).end(); i++) 

#define MAP_KEY(i) ((i)->first)

#define MAP_VALUE(i) ((i)->second)

#define MAP_ERASE1(m,k) if(MAP_HAS1((m),(k))) (m).erase((k) ) ;

#define MAP_ERASE2(m,k1,k2) \ 
if(MAP_HAS1((m),(k))) { \
	MAP_ERASE1((m)[(k1)],(k2));\
	if((m)[(k1)].size() == 0 ) \
	MAP_ERASE1((m),(k1)); \
} 


#define FOR_VECTOR(v,i) for(uint32_t i=0;i<(v).size();i++)
#define FOR_VECTOR_ITERATOR(e,v,i) for(vector<e>::iterator i=(v).begin();i!=(v).end();i++)
#define FOR_VECTOR_WITH_START(v,i,s) for(v,i,s) for(uint32_t i=s;i<(v).size();i++)
#define ADD_VECTOR_END(v,i) (v).push_back((i))
#define ADD_VECTOR_BEGIN(v,i) (v).insert((v).begin(),(i))
#define VECTOR_VAL(i)  (*(i))
 

