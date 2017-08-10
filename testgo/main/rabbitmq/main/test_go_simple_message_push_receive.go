/*
http://studygolang.com/articles/4802
*/
package main

import (
	"bytes"
	"flag"
	"fmt"
	"log"
	"time"

	"github.com/streadway/amqp"
)

const (
	mq_url_default  = "amqp://guest:guest@localhost:5672/"
	mq_url_ubuntu16 = "amqp://test:test@172.25.21.13:5672/"
)

var conn *amqp.Connection
var channel *amqp.Channel
var count = 0

var (
	/*需要falg包*/
	simple_queueName = flag.String("queue", "test-queue", "Ephemeral AMQP queue name")
)

const (
	/*
		$ ./test_go_simple_message_push_receive.exe
		2017/05/02 11:48:05 :Exception (404) Reason: "NOT_FOUND - no queue 'push.msg.q' in vhost '/'"

	*/
	queueName = "push.msg.q"
	exchange  = "t.msg.ex"
	mqurl     = mq_url_ubuntu16
)

func main() {
	go func() {
		for {
			push()
			time.Sleep(1 * time.Second)
		}
	}()
	receive()
	fmt.Println("end")
	close()
}

func failOnErr(err error, msg string) {
	if err != nil {
		log.Fatalf("%s:%s", msg, err)
		panic(fmt.Sprintf("%s:%s", msg, err))
	}
}

func mqConnect() {
	var err error
	conn, err = amqp.Dial(mqurl)
	failOnErr(err, "failed to connect tp rabbitmq")

	channel, err = conn.Channel()
	failOnErr(err, "failed to open a channel")
}

func close() {
	channel.Close()
	conn.Close()
}

//连接rabbitmq server
func push() {

	if channel == nil {
		mqConnect()
	}
	msgContent := "hello world!"

	channel.Publish(exchange /*queueName*/, *simple_queueName /*这是一个指针，所以要* 得到内容*/, false, false, amqp.Publishing{
		ContentType: "text/plain",
		Body:        []byte(msgContent),
	})
}

func receive() {
	if channel == nil {
		mqConnect()
	}

	msgs, err := channel.Consume( /*queueName*/ *simple_queueName, "", true, false, false, false, nil)
	failOnErr(err, "")

	forever := make(chan bool)

	go func() {
		//fmt.Println(*msgs)
		for d := range msgs {
			s := BytesToString(&(d.Body))
			count++
			fmt.Printf("receve msg is :%s -- %d\n", *s, count)
		}
	}()

	fmt.Printf(" [*] Waiting for messages. To exit press CTRL+C\n")
	<-forever
}

func BytesToString(b *[]byte) *string {
	s := bytes.NewBuffer(*b)
	r := s.String()
	return &r
}
