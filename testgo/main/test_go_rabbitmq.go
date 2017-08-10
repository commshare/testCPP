package main

import (
	"bytes"
	"fmt"
	"log"
	"os"
	"time"

	"github.com/streadway/amqp"
)

var conn *amqp.Connection
var channel *amqp.Channel
var count = 0

const (
	queueName = "push.msg.q"
	exchange  = "t.msg.ex"
	mqurl     = "amqp://shi:123@127.0.0.1:5672/test"
)

/*http://studygolang.com/articles/4802*/
func testRMQ() {
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

func main() {
	CloudAMQPwithGoGettingStarted()
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

	channel.Publish(exchange, queueName, false, false, amqp.Publishing{
		ContentType: "text/plain",
		Body:        []byte(msgContent),
	})
}

func receive() {
	if channel == nil {
		mqConnect()
	}

	msgs, err := channel.Consume(queueName, "", true, false, false, false, nil)
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

/*
$ ./test_go_rabbitmq.exe
panic: runtime error: invalid memory address or nil pointer dereference
[signal 0xc0000005 code=0x0 addr=0x0 pc=0x56e8d4]

goroutine 35 [running]:
github.com/streadway/amqp.(*Connection).allocateChannel(0x0, 0x0, 0x0, 0x0)
        D:/zhangbin/go/gopath/src/github.com/streadway/amqp/connection.go:576 +0x54
github.com/streadway/amqp.(*Connection).openChannel(0x0, 0xc042094040, 0xc04208a060, 0xc042083db0)
        D:/zhangbin/go/gopath/src/github.com/streadway/amqp/connection.go:602 +0x36
github.com/streadway/amqp.(*Connection).Channel(0x0, 0xc042094040, 0x5f9d01, 0xc042080101)
        D:/zhangbin/go/gopath/src/github.com/streadway/amqp/connection.go:629 +0x32
main.CloudAMQPwithGoGettingStarted.func2(0x0, 0x0)
        J:/MYSELF/testCPP/testgo/main/test_go_rabbitmq.go:130 +0x64
created by main.CloudAMQPwithGoGettingStarted
        J:/MYSELF/testCPP/testgo/main/test_go_rabbitmq.go:142 +0xe9

*/
/*https://www.cloudamqp.com/docs/go.html*/
func CloudAMQPwithGoGettingStarted() {
	url := os.Getenv("CLOUDAMQP_URL")
	if url == "" {
		url = "amqp://localhost"
	}
	connection, _ := amqp.Dial(url)
	defer connection.Close()
	go func(con *amqp.Connection) {
		channel, _ := connection.Channel()
		defer channel.Close()
		durable, exclusive := false, false
		autoDelete, noWait := true, true
		q, _ := channel.QueueDeclare("test", durable, autoDelete, exclusive, noWait, nil)
		channel.QueueBind(q.Name, "#", "amq.topic", false, nil)
		autoAck, exclusive, noLocal, noWait := false, false, false, false
		messages, _ := channel.Consume(q.Name, "", autoAck, exclusive, noLocal, noWait, nil)
		multiAck := false
		for msg := range messages {
			fmt.Println("Body:", string(msg.Body), "Timestamp:", msg.Timestamp)
			msg.Ack(multiAck)
		}
	}(connection)

	go func(con *amqp.Connection) {
		timer := time.NewTicker(1 * time.Second)
		channel, _ := connection.Channel()

		for t := range timer.C {
			msg := amqp.Publishing{
				DeliveryMode: 1,
				Timestamp:    t,
				ContentType:  "text/plain",
				Body:         []byte("Hello world"),
			}
			mandatory, immediate := false, false
			channel.Publish("amq.topic", "ping", mandatory, immediate, msg)
		}
	}(connection)

	select {}
}
