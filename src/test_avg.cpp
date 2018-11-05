struct StatAvgMax
{
	StatAvgMax()
	{
		lastResetTime = 0;
		reset();
	}
	void reset()
	{
		avg = 0;
		max = 0;
		min = 0xFFFFFFFF;
		total = 0;
		cnt = 0;
	}
	void add(uint32_t value)
	{
		/*if(SelectorEPoll::m_iNow > lastResetTime+cycleTime)
		{
			reset();
		}*/

		if(value > max)
		{
			max = value;
		}
		if(value < min)
		{
			min = value;
		}
		cnt++;
		total += (uint64_t)value;
		avg = total/cnt;
	}
	/*void setCycleTime(uint32_t ct)
	{
		cycleTime = ct;
	}*/
	uint32_t avg;
	uint32_t max;
	uint32_t min;
	uint64_t total;
	uint32_t cnt;
	uint64_t lastResetTime;
	//uint32_t cycleTime;//计算周期，单位秒
};


class DelayDistribution 
{
private:
	struct tagSTAT
	{
		uint64_t _A;
		uint64_t _B;
		uint64_t _C;
		uint64_t _D;
		uint64_t _E;
		uint64_t _F;
	};
	tagSTAT stat; //分布 

public:
	DelayDistribution();
	~DelayDistribution();
	void clearStat();
	void Update(uint64_t v);

	tagSTAT getStat() { return stat; }
	string getStatStr() { 
		ostringstream os;
		os<<stat._A << " " <<stat._B <<" " <<stat._C <<" "<<stat._D <<" "<<stat._E <<" "<<stat._F <<" "<<endl;
		return os.str() ;// .c_str()
	 }

};

DelayDistribution::DelayDistribution()
{
	clearStat();
}

void DelayDistribution::clearStat(){
	stat._A = 0;
	stat._B =0;
	stat._C =0;
	stat._D =0;
	stat._E =0 ;
	stat._F =0; 
}

DelayDistribution::~DelayDistribution()
{
	std::cout <<"de structor "<<endl;
}
//[0,30) [30,50) [50,80) [80,120) [120,200) >=200
void DelayDistribution::Update(const uint64_t v)
{
	if( v >= 0) {
		if( 0 <= v && v <30 ){
			stat._A ++ ;
		}else{
			if( 30 <= v && v <50 ){
				stat._B ++ ;
			}else{
				if( 50 <= v && v < 80 ){
					stat._C ++;
				}else{
					if( 80 <= v && v < 120 ){
						stat._D ++ ;
					}else{
						if( 120 <= v && v< 200){
							stat._E ++ ;
						}else{
							if( v >=200 ){
								stat._F ++;
							}else{
								std::cout <<"error v"<<endl;
							}
						}
					}
				}
			}
		}
	}else{
		std::cout <<"error v "<<v <<endl;
	}
}

class ResourceStatItem{
public:
    float _average_value;
    float _max_value;
    float _min_value;

    ResourceStatItem() {
        _average_value = 0;
        _max_value     = 0;
        _min_value     = 0;
    }
};

 class ResourceStatTempData {
    public:
        uint32_t _count; //数目 
        float    _total_value;  //求和 
        DelayDistribution* _result; //分布 

        ResourceStatTempData() {
            _count       = 0;
            _total_value = 0;
            _result      = NULL;
        }
    };
