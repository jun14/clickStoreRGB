# 鼠标点击显示RGB并存储

## 功能说明

1. 读入图片文件并显示
2. 通过鼠标点击显示RGB
3. 把某点的RGB写入TXT文件
	
	r   g b 文件名        #frame	x   y  
	255 0 0 test0001.bmp -1		100 200  
	255 0 0 test0001.bmp -1		101 200  
	255 0 0 test0001.bmp -1		102 200  

4. 读入视频并播放
5. 通过点击视频显示RGB  
6. 把视频的RGB写入TXT  
	
	r   g b 文件名        #frame	x   y  
	255 0 0 test0001.avi 0		100 200  
	255 0 0 test0001.avi 1		101 200  
	255 0 0 test0001.avi 2		102 200  
	255 0 0 test0001.avi 3		103 200  

7. 按回车前进一帧, 按ESC退出并保存数据  
8. 按右键回复撤销最后的一条记录

记录文件位置在程序所在位置, 文件名是rgbStat.txt

## 版本说明:

### v1.0

完成功能8

### v0.3

2013年12月16日  
完成功能4,5,6,7  

### v0.2

2013年12月14日  
完成功能3

### v0.1

2013年12月14日  
完成功能1, 2
通过按ESC退出

说明文档后缀名不能是大写的MD, 要求还挺严格

## 许可

Copyright (c) 2013 Zhang Jun. 
See the LICENSE file for license rights and limitations (MIT).