package main

/*go-amqp-example
Example of publisher and consumer of RabbitMQ messages in Golang
https://github.com/andreagrandi/go-amqp-example/blob/master/README.md*/
/*
$ ./consumer.exe
2017/04/28 11:16:06 Failed to connect to RabbitMQ: dial tcp [::1]:5672: connectex: No connection could be made because the target machine actively refused it.

*/
import (
	"encoding/json"
	"flag"
	"fmt"
	"log"

	"../contracts"
	"github.com/streadway/amqp"
)

var ( /*"amqp://guest:guest@localhost:5672/"*/
	amqpURI = flag.String("amqp", "amqp://test:test@172.25.21.13:5672/", "AMQP URI")
)

func failOnError(err error, msg string) {
	if err != nil {
		log.Fatalf("%s: %s", msg, err)
		panic(fmt.Sprintf("%s: %s", msg, err))
	}
}

func init() {
	flag.Parse()
	initAmqp()
}

var conn *amqp.Connection
var ch *amqp.Channel
var replies <-chan amqp.Delivery

func initAmqp() {
	var err error
	var q amqp.Queue

	conn, err = amqp.Dial(*amqpURI)
	failOnError(err, "Failed to connect to RabbitMQ")

	log.Printf("got Connection, getting Channel...")

	ch, err = conn.Channel()
	failOnError(err, "Failed to open a channel")

	log.Printf("got Channel, declaring Exchange (%s)", "go-test-exchange")

	err = ch.ExchangeDeclare(
		"go-test-exchange", // name of the exchange
		"direct",           // type
		true,               // durable
		false,              // delete when complete
		false,              // internal
		false,              // noWait
		nil,                // arguments
	)
	failOnError(err, "Failed to declare the Exchange")

	log.Printf("declared Exchange, declaring Queue (%s)", "go-test-queue")

	q, err = ch.QueueDeclare(
		"go-test-queue", // name, leave empty to generate a unique name
		true,            // durable
		false,           // delete when usused
		false,           // exclusive
		false,           // noWait
		nil,             // arguments
	)
	failOnError(err, "Error declaring the Queue")

	log.Printf("declared Queue (%q %d messages, %d consumers), binding to Exchange (key %q)",
		q.Name, q.Messages, q.Consumers, "go-test-key")

	err = ch.QueueBind(
		q.Name,             // name of the queue
		"go-test-key",      // bindingKey
		"go-test-exchange", // sourceExchange
		false,              // noWait
		nil,                // arguments
	)
	failOnError(err, "Error binding to the Queue")

	log.Printf("Queue bound to Exchange, starting Consume (consumer tag %q)", "go-amqp-example")

	replies, err = ch.Consume(
		q.Name,            // queue
		"go-amqp-example", // consumer
		true,              // auto-ack
		false,             // exclusive
		false,             // no-local
		false,             // no-wait
		nil,               // args
	)
	failOnError(err, "Error consuming the Queue")
}

func main() {
	log.Println("Start consuming the Queue...")
	var count int = 1

	for r := range replies {
		log.Printf("Consuming reply number %d", count)
		user := contracts.User{}
		json.Unmarshal(r.Body, &user)
		fmt.Printf("FirstName: %s, LastName: %s\n", user.FirstName, user.LastName)
		count++
	}
}
