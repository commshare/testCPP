/*https://github.com/andreagrandi/go-amqp-example/blob/master/publisher/publisher.go*/

package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"math/rand"
	"time"

	"../contracts"
	//"github.com/streadway/amqp"
	"github.com/adeven/amqp"
)

/*
zhangbin@DESKTOP-1QV8QU4 MINGW64 /j/MYSELF/testCPP/testgo/main/rabbitmq/main (master)
$ go run publisher.go
2017/04/28 11:21:32 Failed to connect to RabbitMQ: dial tcp [::1]:5672: connectex: No connection could be made because the target machine actively refused it.
exit status 1

使用了amqp://test:test@172.25.21.13:15672/ 之后

$ ./publisher.exe
producer: init fun...
2017/05/02 10:40:52 Failed to connect to RabbitMQ: Exception (501) Reason: "EOF"


"amqp://test:test@172.25.21.13:5672/",  换了一个端口号为5672
$ go run publisher.go
producer: init fun...
2017/05/02 10:48:32 Starting publisher...
Starting publisher...
2017/05/02 10:48:32 Failed to Publish on RabbitMQ: Exception (504) Reason: "channel/connection is not open"
exit status 1


*/
var (
	amqpURI = flag.String("amqp", "amqp://test:test@172.25.21.13:15672/", "AMQP URI")
)

func failOnError(err error, msg string) {
	if err != nil {
		log.Fatalf("%s: %s", msg, err)
		panic(fmt.Sprintf("%s: %s", msg, err))
	}
}

/*先执行init*/
func init() {
	fmt.Println("producer: init fun...")
	flag.Parse()
	initAmqp()
}

var conn *amqp.Connection
var ch *amqp.Channel

func initAmqp() {
	var err error

	conn, err = amqp.Dial(*amqpURI)
	failOnError(err, "Failed to connect to RabbitMQ")

	ch, err = conn.Channel()
	failOnError(err, "Failed to open a channel")

	err = ch.ExchangeDeclare(
		"test-exchange", // name
		"direct",        // type
		true,            // durable
		false,           // auto-deleted
		false,           // internal
		false,           // noWait
		nil,             // arguments
	)
	failOnError(err, "Failed to declare the Exchange")
}

func randomString(l int) string {
	bytes := make([]byte, l)
	for i := 0; i < l; i++ {
		bytes[i] = byte(randInt(65, 90))
	}
	return string(bytes)
}

func randInt(min int, max int) int {
	return min + rand.Intn(max-min)
}

func publishMessages(messages int) {
	for i := 0; i < messages; i++ {
		user := contracts.User{}
		user.FirstName = randomString(randInt(3, 10))
		user.LastName = randomString(randInt(3, 10))

		payload, err := json.Marshal(user)
		failOnError(err, "Failed to marshal JSON")

		err = ch.Publish(
			"go-test-exchange", // exchange
			"go-test-key",      // routing key
			false,              // mandatory
			false,              // immediate
			amqp.Publishing{
				DeliveryMode: amqp.Transient,
				ContentType:  "application/json",
				Body:         payload,
				Timestamp:    time.Now(),
			})

		failOnError(err, "Failed to Publish on RabbitMQ")
	}
}

func main() {
	log.Println("Starting publisher...")
	fmt.Println("Starting publisher...")
	// Publish messages
	publishMessages(10000)

	// Close Channel
	defer ch.Close()

	// Close Connection
	defer conn.Close()
}
