package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func walkFunc(path string, info os.FileInfo, err error) error {
	fmt.Printf("FileName[%s]FileSize[%d]Dir[%v]\n",
		filepath.Join(path, info.Name()), info.Size(), info.IsDir())
	return err
}

/*https://gist.github.com/fubarhouse/5ae3fdd5ed5be9e718a92d9b3c780a22*/
func run() ([]string, error) {
	searchDir := "V:\\RECORD_TEST\\testCPP\\testgo\\main\\optisrv\\main"

	fileList := make([]string, 0)
	e := filepath.Walk(searchDir, func(path string, f os.FileInfo, err error) error {
		fileList = append(fileList, path)
		return err
	})

	if e != nil {
		panic(e)
	} else {
		fmt.Println("Complete!!!!!!!!!")
	}

	for _, file := range fileList {
		fmt.Println(file)
	}

	return fileList, nil
}

func main() {
	run()
}
