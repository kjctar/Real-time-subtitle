# -Real-time-subtitle
# 实时字幕
基于QT调用百度实时语音API和百度翻译API，实现视频字幕的实时生成  
可以设置音频的输入设备，如果只录制电脑的系统声音就选择立体声  
如果不能使用，请再const.h里配置自己的api参数  
![Image of Yaktocat](https://github.com/kjctar/Real-time-subtitle/blob/master/1.png)

显示开始按钮，按下按钮会变为暂停，目前只有开始和暂停选项，窗口会实时显示电影里英语的英文字幕和翻译的中文字幕

![Image of Yaktocat](https://github.com/kjctar/Real-time-subtitle/blob/master/2.png)

Quick start

# assume the following codes in example.go file
$ cat example.go

package main

import "github.com/gin-gonic/gin"

func main() {
	r := gin.Default()
	r.GET("/ping", func(c *gin.Context) {
		c.JSON(200, gin.H{
			"message": "pong",
		})
	})
	r.Run() // listen and serve on 0.0.0.0:8080 (for windows "localhost:8080")
}

# run example.go and visit 0.0.0.0:8080/ping (for windows "localho
