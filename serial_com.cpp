#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>
#include <unistd.h>
using namespace std;
using namespace boost::asio;

int main(int argc, char* argv[])
{
        io_service iosev;
        //节点文件
       // serial_port sp(iosev, "/dev/pts/26");
	serial_port sp(iosev);
     	sp.open("/dev/ttyS0");///dev/ttyS0   /dev/pts/26  串口号
        // 设置参数
        sp.set_option(serial_port::baud_rate(115200));
        sp.set_option(serial_port::flow_control(serial_port::flow_control::none));
        sp.set_option(serial_port::parity(serial_port::parity::none));
        sp.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
        sp.set_option(serial_port::character_size(8));
        // 向串口写数据
/*
	for(int i=0;i<2;i++)
{
	char str[30] = "";
	//printf("%d",sizeof(float));
	float x = 1.1101, y = 2.2202, z = 3.3303;
	sprintf(str,"%.2f %.2f %.2f\n",x,y,z);
	int l =  strlen(str);
	printf("%d\n" , l);
        write(sp, buffer(str, l));
}
*/	//int c_times=0;
	while(true)
	{
		char str[30] = "";
		float x = 222.2222;
		sprintf(str,"%.4f\n",x);
		int l =  strlen(str);
		try
		{
		write(sp, buffer(str, l));
		//c_times++;
		//printf("count times is :%d\n",c_times);//查看通讯次数
		}
		catch(exception &e)
		{cout<<"serial port cannot connect"<<endl;
			sp.close();
			for(int i = 0; i < 3; i++)
			{
			sleep(10);
		/*通讯中断后，尝试每10秒连接一次，3次还未连接上则报错并准备退出程序，连接上则跳出本次循环*/
			try{
				sp.open("/dev/pts/26");
			   }

			catch(exception &e){}
			bool flag = sp.is_open();
			cout<<flag<<"\n"<<endl;
			if(flag) break;
			}
		}
		//cout<<sp.is_open()<<endl;
		if(!sp.is_open())
		{cout<<"losting connect,going to stop source!"<<endl;
		break;
		}

	// 从串口读数据
/*
        char buf[100];
        read(sp, buffer(buf));
	printf("buf[0] = %c\n",buf[0]);
*/	
	}	

        iosev.run();
        return 0;
}
