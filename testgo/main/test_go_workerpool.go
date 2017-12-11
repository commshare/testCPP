/*
https://gobyexample.com/worker-pools
*/

package main

import (
	"fmt"
	"time"
)

/*
In order to use our pool of workers we need to send them work and collect their results. We make 2 channels for this.
*/
func worker(id int, jobs <-chan int, results chan<- int) {
	for j := range jobs {
		fmt.Println("worker :", id, "---start job", j)
		time.Sleep(time.Second)
		fmt.Println("worker ", id, "---finish job", j)
		results <- j * 2
	}
}

func main() {
	jobs := make(chan int, 100)
	results := make(chan int, 100)
	/*pool的大小是3个*/
	for w := 1; w <= 3; w++ {
		go worker(w, jobs, results)
	}
	/*Here we send 5 jobs and then close that channel to indicate that’s all the work we have.*/
	for j := 1; j <= 5; j++ {
		jobs <- j
	}
	close(jobs)

	/*Finally we collect all the results of the work.*/
	for a := 1; a <= 5; a++ {
		<-results
	}
}
