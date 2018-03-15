package main

/*
https://gist.github.com/hnakamur/617f5a9ae16a63cb8c65
*/
import (
	"context"
	"fmt"
	"os"
	"os/signal"
	"time"
)

func main() {
	c1, cancel := context.WithCancel(context.Background())

	exitCh := make(chan struct{})
	go func(ctx context.Context) {
		for {
			fmt.Println("In loop. Press ^C to stop.")
			// Do something useful in a real usecase.
			// Here we just sleep for this example.
			time.Sleep(time.Second)

			select {
			case <-ctx.Done():
				fmt.Println("received done, exiting in 500 milliseconds")
				time.Sleep(500 * time.Millisecond)
				exitCh <- struct{}{}
				return
			default:
			}
		}
	}(c1)

	signalCh := make(chan os.Signal, 1)
	signal.Notify(signalCh, os.Interrupt)
	go func() {
		select {
		case <-signalCh:
			cancel()
			return
		}
	}()
	<-exitCh
}
