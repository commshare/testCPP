package main

import (
	"errors"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

func main() {
	file, _ := exec.LookPath(os.Args[0])
	path, _ := filepath.Abs(file)
	println(path)

	exepath, _ := os.Executable()

	println(exepath)

	i := strings.LastIndex(exepath, "/")
	if i > 0 {
		println(string(exepath[0 : i+1]))
	} else {
		println("cannot find folder")
	}
}

func GetCurrentPath() (string, error) {
	file, err := exec.LookPath(os.Args[0])
	if err != nil {
		return "", err
	}
	path, err := filepath.Abs(file)
	if err != nil {
		return "", err
	}
	i := strings.LastIndex(path, "/")
	if i < 0 {
		i = strings.LastIndex(path, "\\")
	}
	if i < 0 {
		return "", errors.New(`error: Can't find "/" or "\".`)
	}
	return string(path[0 : i+1]), nil
}
