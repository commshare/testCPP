package main

import (
	"bufio"
	"errors"
	"flag"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"time"
)

func main() {
	t10txt := "/home/zhangbin1/db/10.txt"
	logfile := "scclen"
	fmt.Printf("default input file is %v,use -i to change it with FULL path \n", t10txt)
	fmt.Printf("default input log file is %v ,use -l to change it , the path is /home/zhangbin1/db/ \n", logfile)
	inputfile := flag.String("i", "", "input file with path")
	inputDir := flag.String("d", "", "input dir path")

	//inputlog := flag.String("l", "/home/zhangbin1/db/"+logfile+".log", "output log name")

	/*！！！！must do parse ！！！！！！*/
	flag.Parse()

	//logger.Info("-###-inputfile [%v] inputDir [%v] -----", *inputfile, *inputDir)
	fmt.Printf("--###--inputfile [%v] inputDir [%v] ----\n", *inputfile, *inputDir)

	if inputfile == nil {
		fmt.Println("inputfile pointer is nil ")
	} else {
		fmt.Println("inputfile pointer is NOT nil ") /*竟然不是nil的*/
	}

	if *inputfile == "" {
		fmt.Println(" *inputfile  is EMPTY ") /*打印了这个*/
	} else {
		fmt.Println(" *inputfile  is NOT  EMPTY ")
	}
	//dir := "V:\\RECORD_TEST\testCPP\testgo\\main\test"
	runDir(*inputDir)
}

/*https://www.baiyuxiong.com/?p=1175*/
//删除函数
func remove(s []string, i int) []string {
	return append(s[:i], s[i+1:]...)
}
func runDir(searchDir string) ([]string, error) {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("Recovered in runDir", r)

		}
	}()
	//searchDir := "V:\\RECORD_TEST\\testCPP\\testgo\\main\\optisrv\\main"
	if searchDir == "" {

		fmt.Println("no dir ", searchDir)
		return nil, errors.New("no dir ")
	}
	fileList := make([]string, 0)
	e := filepath.Walk(searchDir, func(path string, f os.FileInfo, err error) error {
		fileList = append(fileList, path)
		return err
	})

	if e != nil {
		panic(e)
	}

	fmt.Printf("==========len of filelist %v \n", len(fileList))
	fileList = remove(fileList, 0)
	fmt.Printf("=====after remove=====len of filelist %v \n", len(fileList))
	for index, file := range fileList {
		fmt.Printf("----index %v --file %v \n", index, file)
	}
	for _, file := range fileList {
		ret, err := checkInput(file)
		fmt.Println(file)
		if ret == true {
			getlines(file)
		} else {
			fmt.Printf("check file fail %v err %v", file, err)
		}
	}
	return fileList, nil
}
func getlines(inputfile string) {
	//t2000txt:="V:\\xcrs_trunk\\mxcrs_shooter\\myshard_shooter\\main\\2000.txt"

	startTime := time.Now()
	fmt.Printf("input file :%v ---now %v \n", inputfile, startTime)
	file, err := os.Open(inputfile)
	if err != nil {
		panic(err)
	}
	defer file.Close()
	lines, errs := LinesWithError(file)

	for line := range lines {
		fmt.Printf("==========line %v====== \n", line)
	}

	err1 := <-errs
	if err1 != nil {
		if err1 == io.EOF {
			fmt.Printf("==========EOF ====== \n")

		} else {
			fmt.Printf("=========read line err %v ", err1)

			//panic(err1)
			return
		}
	}
	fmt.Printf("---getlines---END END END-------%v---\n", time.Now().Sub(startTime))
}

func LinesWithError(r io.Reader) (lines <-chan string, err <-chan error) {
	br := bufio.NewReader(r)
	chan_line := make(chan string, 0)
	chan_error := make(chan error, 1)
	go func() {
		defer func() {
			close(chan_line)
			close(chan_error)
		}()
		linebuf := ""
		for {
			line, isPrefix, err := br.ReadLine()
			if err == io.EOF {
				chan_error <- /*nil*/ io.EOF
				return
			} else if err != nil {
				chan_error <- err
				return
			}
			linebuf += string(line)
			if !isPrefix {
				chan_line <- linebuf
				linebuf = ""
			}
		}
	}()
	return chan_line, chan_error
}
func checkInput(input string) (bool, error) {
	ret, err := Exists(input)
	if ret == true {

		fmt.Printf("--2-%v exits \n", input)
	} else {

		fmt.Printf("-4--%v NOT exits \n", input)
	}
	return ret, err
}

func Exists(name string) (bool, error) {
	if _, err1 := os.Stat(name); err1 != nil {
		if os.IsNotExist(err1) {
			return false, err1
		}
	}

	return true, nil
}
