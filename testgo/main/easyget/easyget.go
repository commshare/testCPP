package easyget

import (
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
)

// Define Request struct
type Request struct {
	BaseUrl     string
	Endpoint    string
	QueryString string
	Headers     map[string][]string
}

// Define Response struct
type Response struct {
	RawBody  []byte
	Body     Body
	Headers  map[string][]string
	Status   int
	Protocol string
}

// Define Body struct that goes in Response
type Body struct {
	Bytes  []byte
	String string
}

func Get(req Request) (Response, error) {

	// Build the URL
	var url string
	url += req.BaseUrl
	url += req.Endpoint
	url += req.QueryString

	// Create an HTTP client
	c := &http.Client{}
	fmt.Printf("============url :[%s]\n", url)
	/*"http://yycloudlive15013.bs2dl.yy.com/crs_ba265a91789342f38c75694e427ef174_bak.ts?fileinformationv2"*/
	// Create an HTTP request
	r, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return Response{}, err
	}

	// Add any defined headers
	if req.Headers != nil {
		r.Header = http.Header(req.Headers)
	}

	// Add User-Agent if none is given
	if r.Header["User-Agent"] == nil {
		r.Header.Set("User-Agent", "Golang easyget")
	}

	// Send the request
	res, err := c.Do(r)

	// Check for error
	if err != nil {
		return Response{}, err
	}

	// Make sure to close after reading
	defer res.Body.Close()

	// Limit response body to 1mb
	lr := &io.LimitedReader{res.Body, 1000000}

	// Read all the response body
	rb, err := ioutil.ReadAll(lr)

	// Check for error
	if err != nil {
		return Response{}, err
	}

	// Build the output
	responseOutput := Response{
		Body: Body{
			Bytes:  rb,
			String: string(rb),
		},
		Headers:  res.Header,
		Status:   res.StatusCode,
		Protocol: res.Proto,
	}

	// Send it along
	return responseOutput, nil
}
