# fplayer

A CLI multi-media player, supporting nearly all formats around the world (some encrypted formats included), based on mpv (mpv.io)
命令行多媒体播放器，支持几乎所有格式（包括网易云和酷狗加密格式）基于mpv

From fplayer 1.9, English is not officially supported.

# Forever Player 2.7 (English)

Usage:
    (Directly run the program or bind the corresponding audio and video file link to open it directly)
Command:
    player [ file / -playlist / -web] <switch/file/url> {<others...>}

Switches:
While using "-playlist"
    <file>            Specified Playlist File

While using "-web" 
    <url>             Play specified direct link media
当第一个命令为[媒体文件]时
    --start=<时间轴>   Locate the file at a specified timeline (format -> percentage / seconds / hh:mm:ss)
    --no-audio        Drop audio clip(s) (if existed)
    --no-video        Drop video clip(s) (if existed)
    --fullscreen      Fullscreen at the beginning
    --subtitle=<file> Specify a subtitle file
    --show-window     Run through a traditional window-style
    --end-exit        Auto-exit

    --full-help       Display full help
  [] is required,<>is optional, and {} is not required

# Forever Player 2.7

用法:
    (直接运行程序 或者绑定对应音视频文件链接直接打开)
命令行:
    fplayer [媒体文件 / -playlist / -web] <开关/file/url> {<额外函数...>}

开关:
当第一个命令为 -playlist 时
    <file>            指定播放列表文件

当第一个命令为 -web 时
    <url>             播放指定直链链接媒体
当第一个命令为[媒体文件]时
    --start=<时间轴>   在打开时直接定位到 (时间轴格式 -> 百分比 / 秒 / 时:分:秒)
    --no-audio        不播放音频 (如果存在)
    --no-video        不播放视频 (如果存在)
    --fullscreen      打开时自动全屏
    --subtitle=<file> 指定字幕文件
    --show-window     以Windows窗口形式运行
    --end-exit        播放结束自动退出

    --full-help       显示全部帮助列表
  [] 为必填项, <> 为可选项, {} 为不必选项


# 播放器内部操作快捷键列表  
(运行时对控制台或者视频窗口输入)

[鼠标右键] 单击    向右移动
[鼠标左键] 双击    切换暂停
[鼠标后退] 单击    快退10s
[鼠标前进] 单击    快进10s
[滚轮向上]         音量+
[滚轮向下]         音量-

[Q]/[SHIFT+ESC]  退出程序
[`]              打开控制台
[I]              临时显示统计信息
[TAB]            切换显示统计信息
[O]              临时显示进度条和时间码
[CTRL+O]         常驻显示进度条和时间码

[ALT+1]          对比度 -1
[ALT+2]          对比度 +1
[ALT+3]          亮度 -1
[ALT+4]          亮度 +1
[ALT+5]          伽马 -1
[ALT+6]          伽马 +1
[ALT+7]          饱和度 -1
[ALT+8]          饱和度 +1
[ALT+9]          色相 -1
[ALT+0]          色相 +1
[ALT+BackSpace]  重置视频均衡器

[CTRL+H]         切换解码器 (硬解/硬解+/软解) (默认硬解)
[CTRL+Left]      视频逆时针旋转90度
[CTRL+Right]     视频顺时针旋转90度
当输出旋转之后，垂直方向因跟随输出方向的变化而改变，输出旋转操作会启动缩略图重建进程
[NUM 4]          视频渲染向左移动
[NUM 6]          视频渲染向右移动
[NUM 8]          视频渲染向上移动
[NUM 2]          视频渲染向下移动
[*]              视频渲染放大
[/]              视频渲染缩小
[+]              视频窗口放大
[-]              视频窗口缩小
[NUM 1]          视频窗口重置

[Space]          切换播放暂停
[SHIFT+Space]    停止
[T]              切换置顶
[D]              逐帧步退
[F]              逐帧步进
[L]              设置/清除AB循环点
[L]              设置/清除AB循环点
[S]              原始截屏 (视频文件截图)
[CTRL+S]         窗口截屏 (窗口截图)
[Enter]          切换全屏

[Left]  / [,]    后退 5 秒 / 后退 1 秒
[Right] / [.]    前进 5 秒 / 前进 1 秒
[Up]             音量 +10
[Down]           音量 -10
[SHIFT+Left]     后退 60 秒
[SHIFT+Right]    前进 60 秒
[CTRL+PGUp]      播放列表上一个
[CTRL+PGDown]    播放列表下一个
[CTRL+ALT+PGUp]  上一章节
[CTRL+ALT+PGDown]下一章节

[PGUp]           播放速度 倍增 (x2)
[PGDown]         播放速度 半减 (x0.5)
[BackSpace]      播放速度 复原
[Insert]         播放速度 +0.05
[Delete]         播放速度 -0.05
[Home] / [<]     跳转到开始 (00:00:00 位置)
[End]  / [>]     跳转到末尾 (播放列表/文件)

[ALT+Z]          上一个音轨
[ALT+X]          下一个音轨
[CTRL+Z]         上一个字幕轨
[CTRL+X]         下一个字幕轨
[CTRL+NUM 8]     字幕移动 ↑
[CTRL+NUM 2]     字幕移动 ↓
[CTRL+NUM 4]     字幕缩小
[CTRL+NUM 6]     字幕放大
