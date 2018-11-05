// main_test.go

/*
然后在该文件夹下面执行如下命令进行 benchmark:

$ go test -bench=.

根据上面的压测结果来看, 使用加锁的方式性能是使用 channel 的方式性能的 3.6倍 左右,
这个数值可不低啊. 所以在做服务端开发的时候, 对性能有所疑惑的时候一定要自己做一下 benchmark, 不能人云亦云.

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main/mutex_vs_channel (master)
$ go test -bench=.
BenchmarkUseMutex-4     100000000               16.1 ns/op
BenchmarkUseChan-4      30000000                53.1 ns/op
PASS
ok      _/V_/RECORD_TEST/testCPP/testgo/main/mutex_vs_channel   5.059s

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main/mutex_vs_channel (master)
$



*/
package main

import "testing"

func BenchmarkUseMutex(b *testing.B) {
	for n := 0; n < b.N; n++ {
		UseMutex()
	}
}
func BenchmarkUseChan(b *testing.B) {
	for n := 0; n < b.N; n++ {
		UseChan()
	}
}
