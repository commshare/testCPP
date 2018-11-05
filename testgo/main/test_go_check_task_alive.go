package gotask

/*https://github.com/catyguan/bma.go.esp/blob/3813e28849949355adaee27e386e0eceaf9337e9/src/bmautil/gotask/gotask.go*/
type GoTask struct {
	C chan bool
}

func NewGoTask() *GoTask {
	r := new(GoTask)
	r.Init()
	return r
}

func (this *GoTask) Init() {
	this.C = make(chan bool, 1)
}

func (this *GoTask) Close() {
	defer func() {
		recover()
	}()
	close(this.C)
}

func (this *GoTask) IsClose() bool {
	select {
	case <-this.C:
		return true
	default:
		return false
	}
}
package gotask

import (
	"fmt"
	"os"
	"testing"
	"time"
)

func safeCall() {
	time.AfterFunc(5*time.Second, func() {
		os.Exit(-100)
	})
}

func TestTimer(t *testing.T) {
	safeCall()
	gt := NewGoTask()
	defer gt.Close()

	timer := time.NewTicker(100 * time.Millisecond)
	go func() {
		for {
			select {
			case <-timer.C:
				fmt.Println("i do...")
			case <-gt.C:
				fmt.Println("end!")
				return
			}
		}
	}()
	time.Sleep(1 * time.Second)
}