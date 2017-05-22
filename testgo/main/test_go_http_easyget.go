/*
https://gist.github.com/montanaflynn/b390b1212dada5864d9b#file-easyget-go-L33
*/
package main

import (
	"encoding/json"
	"fmt"

	"./easyget"
)

// Define response data
type Data struct {
	Date   string
	Cases  int
	Status string
}

func main() {

	// Create any headers we want to send
	headers := make(map[string][]string)
	headers["X-Header-Info"] = []string{"Something"}
	headers["X-Header-Array"] = []string{"One", "Two"}

	// Build the Request struct
	req := easyget.Request{
		BaseUrl:     "http://192.241.227.237/",
		Endpoint:    "ebola/project",
		QueryString: "?distance=5",
		Headers:     headers,
	}

	// Send the request
	res, err := easyget.Get(req)

	// Print error if it exists
	if err != nil {
		fmt.Println(err)
	}

	// Print the stuff in Response struct
	fmt.Println(res.Body.String)
	fmt.Println(res.Headers)
	fmt.Println(res.Status)
	fmt.Println(res.Protocol)

	// Since we have a JSON array lets turn it into a Go array
	var data []Data
	json.Unmarshal(res.Body.Bytes, &data)

	// Print what we got with keys
	fmt.Printf("%+v\n", data)

	// Loop over array and print some stuff we found
	for _, e := range data {
		fmt.Printf("%v total %v cases: %v \n", e.Date, e.Status, e.Cases)
	}
}
