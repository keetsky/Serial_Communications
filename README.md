# Serial_Communications


	http://blog.csdn.net/zhaodan19861107/article/details/7766338
	查看串口名称使用 ls -l /dev/ttyS*   
	查看串口设备：dmesg | grep ttyS*  可获得可用串口和波特率
	在Linux下如果出现Cannot open /dev/ttyS0: Permission denied.普通用户	没有权限读写串口设备。inux下的串口设备名通常是/dev/ttyS[0-9]或	者/dev/ttyUSB[0-9]，后者对应的是USB转串口的设备。
	$ sudo vim /etc/udev/rules.d/90-serials.rules 文件中写入
	KERNEL=="ttyS[0-9]",NAME="%k",GROUP="tty",MODE="0666"
	KERNEL=="ttyUSB[0-9]",NAME="%k",GROUP="tty",MODE="0666"
	重启电脑后即可
