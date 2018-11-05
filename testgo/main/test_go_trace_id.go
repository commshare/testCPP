package main

import (
	"fmt"
	"strings"
)

/*2017/11/20 05:01:07 [playlist_generator.go:942] [I] http error:/xcrs/15013x03_25929849_1832645014_1511123919_1511113048.m3u8?traceid=vod_crs_m3u8_mq_access_1046643205916071941_T53SyBKBPYdc7syA8vn7xgW72545120 reason:307*/

func main() {
	uri := "/xcrs/15013x03_25929849_1832645014_1511123919_1511113048.m3u8?traceid=vod_crs_m3u8_mq_access_1046643205916071941_T53SyBKBPYdc7syA8vn7xgW72545120"
	TRACE_HTTP_VOD_MQ_REQUEST := "traceid=vod_crs_m3u8_mq_access"
	if strings.Contains(uri, TRACE_HTTP_VOD_MQ_REQUEST) == true {
		fmt.Println("got traceid=vod_crs_m3u8_mq_access")
	}
}
