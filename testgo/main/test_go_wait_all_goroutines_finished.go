/*


This code is shorter, and doesn’t introduce unneeded complexity.
What was wrong with the “Canonical way” code?
Well, for one thing, the messages channel doesn’t get closed, which could cause a memory leak 内存泄露啊. It’s also not exactly cosidered the best use for a WaitGroup. As enneff put it:
The original program leaves the printing goroutine hanging (it blocks trying to receive a fourth message that never comes). This will create a memory leak in a long-running problem. You need to close the messages channel after the wg.Wait, to make sure that goroutine terminates. Obviously not a problem in a trivial program, but we should teach good practices at all times. But that still doesn’t solve the problem of the racing and printing goroutines, and there’s no reason why the so-called “old-school” way isn’t appropriate here. When you know the number of messages to expect you might as well count them to know when to finish. Here the waitgroup is superfluous and confusing. WaitGroups are more useful for doing different tasks in parallel.
More importantly, I mistakenly put the code to print the results in its own goroutine, which causes a race condition between the main goroutine and the goroutine that is printing. In many cases, the main goroutine will win this race, which is BAD!! Turns out that my whole “sleep for a few seconds, then send a message down the channel” example is actually not a good example for wait groups at all.
The “fetch some JSON from the Reddit API” example, however, actually is a good candidate for sync.WaitGroup, and enneff even featured a rewrite that takes advantage of multiple channels to send errors in case something goes wrong!
*/
// This snippet was prepared in response to this article:
// https://nathanleclaire.com/blog/2014/02/15/how-to-wait-for-all-goroutines-to-finish-executing-before-continuing/
package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
)

func main() {
	urls := []string{
		"http://www.reddit.com/r/aww.json",
		"http://www.reddit.com/r/funny.json",
		"http://www.reddit.com/r/programming.json",
	}

	resc, errc := make(chan string), make(chan error)

	for i, url := range urls {
		go func(url string) {
			fmt.Printf("fetch goroutine...%v \n", i)
			body, err := fetch(url)
			if err != nil {
				errc <- err
				return
			}
			resc <- string(body)
		}(url)
	}
	fmt.Printf("wait for all gourinte ... \n")
	for i := 0; i < len(urls); i++ {
		select {
		case res := <-resc:
			fmt.Printf("get res i %v \n", i)
			fmt.Println(res)
		case err := <-errc:
			fmt.Println(err)
		}
	}
}

func fetch(url string) (string, error) {
	res, err := http.Get(url)
	if err != nil {
		return "", err
	}
	body, err := ioutil.ReadAll(res.Body)
	res.Body.Close()
	if err != nil {
		return "", err
	}
	return string(body), nil
}
