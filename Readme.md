桌面模式下
![Snipaste_2021-06-23_13-41-00](https://user-images.githubusercontent.com/45707573/123042102-e161de80-d428-11eb-85c4-17cf507e354f.png)
全屏模式A下
![Snipaste_2021-06-23_13-41-12](https://user-images.githubusercontent.com/45707573/123042117-e7f05600-d428-11eb-9eb6-91568bafc6fa.png)
全屏模式B下
![Snipaste_2021-06-23_13-41-29](https://user-images.githubusercontent.com/45707573/123042156-f474ae80-d428-11eb-8ca3-a64df5a4a370.png)


v.0.8更新日志
增加全屏模式，可作屏保；
全屏下有跳动图片，可自定义；
增加鼠标事件，简化操作；
取消自定义位置；
取消拖拽操作；

-------配置文件内容--------
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
