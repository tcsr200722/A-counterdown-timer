<img width="1280" alt="fullscreen" src="https://user-images.githubusercontent.com/45707573/122680172-88bff500-d220-11eb-8b91-debc9fe785aa.png">

config.ini放在timer.exe同级目录下

文件结构

word : 提示词

deadline : 事件发生的日期 示例2022.06.18 21:04:06

font_size : 字号

font_color : 字体颜色(HTML)

font_family : 字体族

font_bold : 

​	[true] 加粗 

​	[false] 不加粗

shining:

​	[true] 时间分隔符闪烁

​	[false] 时间分隔符不闪烁

music_volume: [0-100] 倒计时归零时，铃声的音量

top_hint:

​	[true] 置顶

​	[false] 不置顶

倒计时结束后将播放铃声提醒，如果同级目录下存在"music.mp3"，则优先播放"music.mp3"，否则默认播放内置铃声



鼠标事件：
双击数字黑色背景，进入全屏模式，会有一个图片跳动，每3s随机变换一个位置（不会和倒计时字幕所在位置冲突），需要在同级目录下放一个logo.png图片

全屏模式下按ESC或者双击鼠标右键退出全屏

非全屏模式下右键双击数字黑色背景，隐藏倒计时

在任务栏托盘中左键双击图标，切换显示/隐藏倒计时
