## 即日起请各位用户自行适配其它分辨率

------------
### 运行展示
###### 桌面模式下
![Snipaste_2021-06-23_13-41-00](https://user-images.githubusercontent.com/45707573/123045078-1112e580-d42d-11eb-82f8-6f51186a13c5.png)
###### 全屏模式
![Snipaste_2021-06-23_13-41-12](https://user-images.githubusercontent.com/45707573/123045093-153f0300-d42d-11eb-859e-f4dff95c7ffb.png)
![Snipaste_2021-06-23_13-41-29](https://user-images.githubusercontent.com/45707573/123045094-15d79980-d42d-11eb-8972-c328608358a6.png)

### 主要特性
- 自定义截止日期
- 自定义提示词
- 自定义字体
- 自定义闹铃
- 自定义考研院校logo
- 自定义考研大纲单词循环范围
- 无边框
- 置顶窗口
- 方便的鼠标事件
- 网络校时
- 可设置开机自启
- 倒计时结束提醒

### 释义
- 用户可以通过编辑同级目录下config.ini定义相关内容
- 用户在同级目录下增加院校logo，并命名为logo.png
- 内置铃声，如果需要更换则在同级目录下添加music.mp3文件
- 院校logo和考研大纲单词在全屏模式下运行

### 鼠标事件
- 左键双击进入全屏模式
- 右键双击隐藏倒计时
- 全屏模式下左键双击进行考研单词和院校logo跳动切换
- 全屏模式下右键双击退出全屏
- 双击任务托盘隐藏/显示倒计时

### config.ini文件结构
###### config内容修改需要严格遵守原格式
###### 文件格式混乱可以删除文件并重启软件
- word：提示词
- deadline：截止日期
- font_size：字体大小
- font_color：字体颜色
- font_family：字体族
- font_bold：是否加粗
- shining：时间分隔符是否闪烁
- music_volume：提示铃声的音量
- top_hint：是否置顶
- word_start：随记单词展示的开始值（闭区间）
- word_end：随记单词展示的结束值（闭区间）
