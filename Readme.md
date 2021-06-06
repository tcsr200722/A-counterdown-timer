<img width="1280" alt="Snipaste_2021-06-06_13-26-00" src="https://user-images.githubusercontent.com/45707573/120913610-d25dfb00-c6ca-11eb-9e1a-80e1dfd01337.png">
<img width="121" alt="Snipaste_2021-06-06_13-26-14" src="https://user-images.githubusercontent.com/45707573/120913613-d5f18200-c6ca-11eb-8493-f8baec69164f.png">

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

x_axis : 在屏幕上显示的位置（x轴）

y_axis : 在屏幕上显示的位置  (y轴)

shining:

​	[true] 时间分隔符闪烁

​	[false] 时间分隔符不闪烁

music_volume: [0-100] 倒计时归零时，铃声的音量

如果同级目录下存在"music.mp3"，则优先播放"music.mp3"，否则默认播放内置铃声
