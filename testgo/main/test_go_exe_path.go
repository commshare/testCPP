package main

import (
<<<<<<< HEAD
	"os"
	"os/exec"
	"path/filepath"
=======
	"errors"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
>>>>>>> 2e0dbda72b3420acfd314554fc3b05c46df05087
)

func main() {
	file, _ := exec.LookPath(os.Args[0])
	path, _ := filepath.Abs(file)
	println(path)
<<<<<<< HEAD
=======

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
>>>>>>> 2e0dbda72b3420acfd314554fc3b05c46df05087
}
