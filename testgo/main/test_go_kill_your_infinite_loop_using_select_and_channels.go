package main

import (
	"fmt"
	"time"
)

/*https://stackoverflow.com/questions/42560109/how-to-kill-goroutine*/
var quit chan struct{} /*chan struct{}?
nit, there's no such thing as a "zero-sized channel". All channels have the same size in memory regardless of their type.
It may be unbuffered if that's what you mean. – JimB Mar 2 at 18:05

@JimB I think he means that the message itself, the struct{}{}, is zero size. – Kaedys Mar 2 at 18:35


 It is a zero-sized channel.
We can only fill it with empty structs (that is: struct{}{}).
It could be a chan bool or whatever else, since we don't use the content of the channel.
The important point is that we use the quit channel to notify the infinite loop in our goroutine that it is time to stop.
*/

func startLoop(done chan struct{}) {
	quit = make(chan struct{})
	go loop(done)
}

func stopLoop() {
	// As mentioned by Kaedys
	//close(quit)
	// permits signalling everyone havins such a `case <-quit:`
	// statement to be stopped at once, which might be even better.
	quit <- struct{}{}
}

/*
The select statement is used to catch what comes out of channels.
 It is a blocking statement (that will halt the execution until something is put in one of the channels surveyed by a case),
  unless you put a default statement. In this situation, every time the select is executed,
   the loop will break if something was put inside quit, or do_stuff() will be called.
You already know this if you've been through the Go Tour.
*/
// BTW, you cannot call your function main, it is reserved
func loop(done chan struct{}) {
	// This ticker will put something in its channel every 2s 每两秒
	ticker := time.NewTicker(2 * time.Second)
EXIT_FOR:
	for {
		select {
		case <-quit:
			fmt.Println("quit it")

			// If you don't stop it, the ticker will cause memory leaks
			ticker.Stop()
			/*单纯的break 不能退出for循环，加一个flag就能跳出了*/
			break EXIT_FOR /*这样可以跳出for*/
		case <-ticker.C:
			/*Finally, for further fun,
			             you can ask your do_stuff function to be executed at regular time intervals by using Tickers,
						  instead of consuming 100% CPU, like so:*/
			// do stuff. I'd call a function, for clarity:
			do_stuff()
			/*Here, select is blocking, since we removed the default statement.*/
		}
	}
	/*只有跳出for才能执行这一句，需要quit执行才能跳出for*/
	/**/
	time.Sleep(3 * time.Second)
	/*通知main退出*/
	done <- struct{}{}
}

func do_stuff() {
	now := time.Now().Unix()
	fmt.Println("====do=== ", now)
}

/*

Worth noting that the typical style for quit channels is to close() them rather than sending a value over them.
 Not only is this cleaner in the code, but a closed channel signals all listeners at once,
 whereas you'd otherwise have to send a separate message over the channel for each listener.
 Also, main() is the program entry point gets called by default,
 you don't need to (and I believe can't) call it separately from another function. – Kaedys Mar 2 at 17:22


I heard something about close() letting the case be executed, which I thought unlogical.

But now I get it: signalling everyone at once will be very useful for me, thanks :) – Adrien Luxey Mar 2 at 17:26


Even better is the context package, see golang.org/pkg/context
You should change your example to use a ctx, cancel := context.WithCancel(context.Background()).

Then main can use a defer cancel(), the goroutines can use a select on the ctx.Done() channel to exit. – Zan Lynx Mar 2 at 17:56


nit, there's no such thing as a "zero-sized channel". All channels have the same size in memory regardless of their type.
It may be unbuffered if that's what you mean. – JimB Mar 2 at 18:05

@JimB I think he means that the message itself, the struct{}{}, is zero size. – Kaedys Mar 2 at 18:35

*/
func main() {
	var done chan struct{}
	done = make(chan struct{})

	startLoop(done)
	time.Sleep(7 * time.Second)
	stopLoop()
	<-done
	fmt.Println("end of main")
}
