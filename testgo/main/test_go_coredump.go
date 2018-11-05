package main

import (
	"fmt"
	"os"
	"runtime/debug"
	"syscall"
<<<<<<< HEAD
=======
	"time"
>>>>>>> 2e0dbda72b3420acfd314554fc3b05c46df05087
)

/*https://guidao.github.io/go_debug.html
go build -gcflags "-N -l" test8.go

*/
func main() {
	test()
}

func test() {
	defer func() {
		if err := recover(); err != nil {
			/*  // recovering from a panic; err contains whatever was passed to panic()*/
			//打印栈信息
			stack := debug.Stack()
<<<<<<< HEAD
			fmt.Printf("%s\n", "-------print-----stack ------")
			fmt.Printf(string(stack))
			/*// if you just want to log the panic, panic again*/
			panic(err) //这里也可以温和的自己控制退出
=======
			fmt.Printf("%s\n", "-------print-----stack ------\n")
			fmt.Printf(string(stack))
			/*// if you just want to log the panic, panic again*/
			//panic(err) //这里也可以温和的自己控制退出
			path := "./zhangbin.err.log"
			createFile(path)
			redirectStderr(path)
			writeFile(string(stack), path)

>>>>>>> 2e0dbda72b3420acfd314554fc3b05c46df05087
		}
	}()
	var b map[string]string
	fmt.Printf("use cmd :%s to build", "go build -gcflags \"-N -l\" test8.go")
	b["one"] = "zhang"

	fmt.Println(b)
}

/*

$ ./test_go_coredump.exe
use cmd :go build -gcflags "-N -l" test8.go to buildgoroutine 1 [running]:
runtime/debug.Stack(0xc042035d80, 0x49e9c0, 0xc042008270)
        D:/Go/src/runtime/debug/stack.go:24 +0x80
main.test.func1()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:20 +0x61
panic(0x49e9c0, 0xc042008270)
        D:/Go/src/runtime/panic.go:489 +0x2dd
main.test()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:27 +0x118
main.main()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:13 +0x27
panic: assignment to entry in nil map [recovered]
        panic: assignment to entry in nil map

goroutine 1 [running]:
main.test.func1()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:22 +0xd7
panic(0x49e9c0, 0xc042008270)
        D:/Go/src/runtime/panic.go:489 +0x2dd
main.test()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:27 +0x118
main.main()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:13 +0x27

zhangbin@DESKTOP-1QV8QU4 MINGW64 /e/huanju/transcode/daobo/testCPP/testgo/main (master)
$


*/
/*https://stackoverflow.com/questions/34772012/capturing-panic-in-golang*/
// redirectStderr to the file passed in
<<<<<<< HEAD
func redirectStderr(f *os.File) {
	err := syscall.Dup2(int(f.Fd()), int(os.Stderr.Fd()))
	if err != nil {
		fmt.Printf("Failed to redirect stderr to file: %v", err)
	}
}

func createFile(path string) (file os.File) {
	// detect if file exists
	var _, err := os.Stat(path)

	// create file if not exists
	if os.IsNotExist(err) {
		 file, err = os.Create(path)
=======
func redirectStderr(path string) {
	// open file using READ & WRITE permission
	// open file using READ & WRITE permission
	var f, err = os.OpenFile(path, os.O_RDWR, 0644)
	if isError(err) {
		fmt.Printf("open file path %s fail", path)
		return
	}
	defer f.Close()

	err = syscall.Dup2(int(f.Fd()), int(os.Stderr.Fd()))
	if err != nil {
		fmt.Printf("#########Failed to redirect stderr to file: %v\n", err)
	}
	fmt.Println("==>redirect stderr to file %v ok", path)
}

func createFile(path string) (file *os.File) {
	// detect if file exists
	_, err := os.Stat(path)

	// create file if not exists
	if os.IsNotExist(err) {
		file, err = os.Create(path)
>>>>>>> 2e0dbda72b3420acfd314554fc3b05c46df05087
		if isError(err) {
			return
		}
		defer file.Close()
	}

	fmt.Println("==> done creating file", path)
<<<<<<< HEAD
=======
	return
>>>>>>> 2e0dbda72b3420acfd314554fc3b05c46df05087
}
func isError(err error) bool {
	if err != nil {
		fmt.Println(err.Error())
	}

	return (err != nil)
<<<<<<< HEAD
}
=======
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

/*https://github.com/andyidea/gotime/blob/master/gotime.go*/
// 获取时间戳   return:1464059756
func GetTimeUnix(t time.Time) int64 {
	return t.Local().Unix()
}

// 获取当前时间的时间戳 return:1464059756
func GetNowTimeUnix() int64 {
	return GetTimeUnix(time.Now())
}

// 获取当日晚上24点（次日0点）的时间
func Get24time(t time.Time) time.Time {
	dateStr := TimeToDate(t.Add(time.Hour * 24))
	return DateStrToTime(dateStr)
}

// 获取当日晚上24点（次日0点）的时间戳
func Get24timeUnix(t time.Time) int64 {
	t24 := Get24time(t)
	return GetTimeUnix(t24)
}

// 获取今天晚上24点（次日0点）的时间
func GetToday24time() time.Time {
	return Get24time(time.Now())
}

// 获取今天晚上24点（次日0点）的时间戳
func GetToday24timeUnix() int64 {
	return Get24timeUnix(time.Now())
}

// 时间转换成日期字符串 (time.Time to "2006-01-02")
func TimeToDate(t time.Time) string {
	return t.Format("2006-01-02")
}

// 获取当前时间的日期字符串（"2006-01-02"）
func GetNowDateStr() string {
	return TimeToDate(time.Now())
}

// 时间转换成日期+时间字符串 (time.Time to "2006-01-02 15:04:05")
func TimeToDateTime(t time.Time) string {
	return t.Format("2006-01-02 15:04:05")
}

// 获取当前的时期+时间字符串
func GetNowStr() string {
	return TimeToDateTime(time.Now())
}

// 日期字符串转换成时间 ("2006-01-02" to time.Time)
func DateStrToTime(d string) time.Time {
	t, _ := time.ParseInLocation("2006-01-02", d, time.Local)
	return t
}

// 日期+时间字符串转换成时间 ("2006-01-02 15:04:05" to time.Time)
func DateTimeStrToTime(dt string) time.Time {
	t, _ := time.ParseInLocation("2006-01-02 15:04:05", dt, time.Local)
	return t
}

// 时间字符串转换成时间 ("15:04:05" to time.Time)
func TimeTodayStrToTime(dt string) time.Time {
	now := time.Now()
	strNowDate := TimeToDate(now)
	return DateTimeStrToTime(strNowDate + " " + dt)
}

// 是否是周末
func IsWeekend(t time.Time) bool {
	wd := t.Weekday()
	if wd == time.Sunday || wd == time.Saturday {
		return true
	}
	return false
}
>>>>>>> 2e0dbda72b3420acfd314554fc3b05c46df05087
