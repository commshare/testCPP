package utils

import (
	"fmt"
	"io"
	"os"
)

/*https://gist.github.com/novalagung/13c5c8f4d30e0c4bff27*/
func createFile(path string) {
	// detect if file exists
	var _, err = os.Stat(path)

	// create file if not exists
	if os.IsNotExist(err) {
		var file, err = os.Create(path)
		if isError(err) { return }
		defer file.Close()
	}

	fmt.Println("==> done creating file", path)
}

func writeFile(outstr string, path string) {
	// open file using READ & WRITE permission
	var file, err = os.OpenFile(path /*os.O_RDWR*/, os.O_WRONLY|os.O_APPEND /*写+追加*/, 0666)
	if isError(err) {
		return
	}
	defer file.Close()

	// write some text line-by-line to file
	temp := GetNowStr() + "dump stack begin..." + "\n"
	_, err = file.WriteString(temp)
	if isError(err) {
		return
	}
	_, err = file.WriteString(outstr)
	if isError(err) {
		return
	}

	temp = GetNowStr() + "dump stack end..." + "\n"
	_, err = file.WriteString(temp)
	if isError(err) {
		return
	}

	// save changes
	err = file.Sync()
	if isError(err) {
		return
	}

	fmt.Println("==> done writing to file")
}

func readFile(path string) {
	// re-open file
	var file, err = os.OpenFile(path, os.O_RDWR, 0644)
	if isError(err) { return }
	defer file.Close()

	// read file
	var text = make([]byte, 1024)
	for {
		n, err := file.Read(text)
		if err != io.EOF {
			if isError(err) { break }
		}
		if n == 0 {
			break
		}
	}
	if isError(err) { return }

	fmt.Println("==> done reading from file")
	fmt.Println(string(text))
}

func deleteFile(path string) {
	// delete file
	var err = os.Remove(path)
	if isError(err) { return }

	fmt.Println("==> done deleting file")
}

func isError(err error) bool {
	if err != nil {
		fmt.Println(err.Error())
	}

	return (err != nil)
}
