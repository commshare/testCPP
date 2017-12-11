package main

import (
	"fmt"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"
)

// KubeRouter holds the information needed to run server
type KubeRouter struct {
	Client string
}


/*nrc*/
// NetworkRoutingController is struct to hold necessary information required by controller
type NetworkRoutingController struct {
	syncPeriod           time.Duration	
}
// Run runs forever until we are notified on stop channel
func (nrc *NetworkRoutingController) Run(stopCh <-chan struct{}, wg *sync.WaitGroup) {
	t := time.NewTicker(nrc.syncPeriod)
	defer t.Stop()
	defer wg.Done()

	// loop forever till notified to stop on stopCh
	for {
		select {
		case <-stopCh:
			fmt.Println("--1---Shutting down network routes controller")
			return
		default:
		}

		time.Sleep(2 * time.Second)

		select {
		case <-stopCh:
			fmt.Println("--2--Shutting down network routes controller")
			return
		case <-t.C:
		}
	}
}

/*npc*/
// NetworkPolicyController strcut to hold information required by NetworkPolicyController
type NetworkPolicyController struct {
	nodeIP          net.IP
	nodeHostName    string
	mu              sync.Mutex
	syncPeriod      time.Duration
	v1NetworkPolicy bool
}

func NewNetworkPolicyController(duration time.Duration ) (*NetworkPolicyController) {
{
	npc := NetworkPolicyController{}
	npc.syncPeriod = duration
	npc.v1NetworkPolicy = true
	return npc
}

// Run runs forver till we receive notification on stopCh
func (npc *NetworkPolicyController) Run(stopCh <-chan struct{}, wg *sync.WaitGroup) {
	t := time.NewTicker(npc.syncPeriod)
	defer t.Stop()
	defer wg.Done()

	fmt.Println("Starting network policy controller")

	// loop forever till notified to stop on stopCh
	for {
		select {
		case <-stopCh:
			fmt.Println("Shutting down network policies controller")
			return
		default:
		}

		/*虚拟一个耗时操作*/
		sleep(1 * time.Second)

		select {
		case <-stopCh:
			fmt.Println("Shutting down network policies controller")
			return
		case <-t.C:
		}
	}
}

// Run starts the controllers and waits forever till we get SIGINT or SIGTERM
func (kr *KubeRouter) Run() error {
	var err error
	var wg sync.WaitGroup

	stopCh := make(chan struct{})
	npc := NewNetworkPolicyController(1)

	wg.Add(1)
	go npc.Run(stopCh, &wg)

	wg.Add(1)
	go nrc.Run(stopCh, &wg)

	wg.Add(1)
	go nsc.Run(stopCh, &wg)

	// Handle SIGINT and SIGTERM
	ch := make(chan os.Signal)
	signal.Notify(ch, syscall.SIGINT, syscall.SIGTERM)
	<-ch

	fmt.Printf("Shutting down the controllers \n")
	close(stopCh)

	wg.Wait()
	return nil
}

func main() {

	router := KubeRouter{}
	router.Run()
}
