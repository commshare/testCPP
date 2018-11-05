
type ModleDefaultData struct {
	name string
}

type ModleCounterData struct {
	name string
}

type ModleHistoData struct {
	name string
}

type Base struct {
	Default []*ModleDefaultData
	Counter []*ModleCounterData
	Histo   []*ModleHistoData
}

func NewBase() *Base {

	base := &Base{
		Defult:  make([]*ModleDefaultData, 0, 10),
		Counter: make([]*ModleCounterData, 0, 10),
		Histo:   make([]*ModleHistoData, 0, 10),
	}
	return base
}

type BaseMgr struct {
	dataChanIndex int32
	dataChans     []chan interface{}
	length        int32
	chanDefault   chan *ModuleDefaultData
	chanHisto     chan *ModuleHistoData
	chanBase      chan *ModuleCounterData
}

func newBaseMgr(workerNum int, chanbufferSize int) {
	if workerNum < 1 {
		workerNum = 1
	}
	if chanbufferSize < 50 {
		chanbufferSize = 50
	}
	m:= BaseMgr{
		dataChanIndex :0,
		dataChans : make([]chan interface ,0 ),
		chanDefault : make(chan *ModuleDefaultData,chanbufferSize),
		chanHisto: make(chan * ModuleHistoData,chanbufferSize),
		chanCounter : make(chan *ModuleCounterData,chanbufferSize),
	}

	for i:=0 ; i< workerNum; i++ {
		dataChan := make(chan interface{}, chanbufferSize)
		go m.work(dataChan) /*每个worker对应一个datachan*/
		m.dataChans = append(m.dataChans,dataChan)
	}
	m.length = int32(len(m.dataChans))
	go m.doModel
	return &m
}
func (this * BaseMgr)getIndex() int32 {
	dataChanIndex := atomic.AddInt32(&this.dataChanIndex,1)
	if dataChanIndex >10000 {
		atomic.StoreInt32(&this.dataChanIndex,0)
	}
	dataChanIndex %= this.length
	return dataChanIndex
}
func (this *BaseMgr)Dispatch(data interface{}) bool {
	index := this.getIndex()
	aChan := this.dataChans[index]  /*返回一个chan interface{}*/
	select {
	case aChan <- data :
		return true
	default :

	}
	return false
}

func (this *BaseMgr) SendDefaultData(data *ModleDefaultData)(err error){
	select {
	case this.chanDefault <- data:
		break
	default:
		err = errors.New("default modle is full")
	}
	return
}

func (this *BaseMgr) SendCounterData(data *ModuleCounterData)(err error){
	select {
	case this.chanCounter <- data:
		break
	default:
		err = errors.New("chanCounter modle is full")
	}
	return
}

func (this *BaseMgr) SendHistoData(data *ModuleCounterData)(err error){
	select {
	case this.chanHisto <- data:
		break
	default:
		err = errors.New("SendHistoData modle is full")
	}
	return
}