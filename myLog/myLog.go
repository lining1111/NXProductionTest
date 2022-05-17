package myLog

import (
	"fmt"
	"log"
	"os"
)

var Logger *log.Logger

func init() {
	dirLog := "./NPT"
	_, errPath := os.Stat(dirLog)
	if errPath != nil && os.IsNotExist(errPath) {
		os.Mkdir(dirLog, os.ModePerm)
	}
	logFile, err := os.OpenFile("./NPT/NXProductinTest.log", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		fmt.Println("打开日志文件异常")
	}
	Logger = log.New(logFile, "success", log.Ldate|log.Ltime|log.Lshortfile)
}
