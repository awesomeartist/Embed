#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

uchar key_l,key_h;		//键盘端口读入
uchar key;
unsigned int flag=0;	//灯亮标志位
unsigned int time=5; 	//定时时间
sbit SOUND_in=P2^5;		//声音输入端口定义
sbit LIGHT_in=P2^4;		//红外输入端口定义
sbit HW_in=P2^2 ;		//红外输入端口定义
sbit LED0 =P1^0; 		//灯亮显示输出端口
sbit LED1 =P1^1;		//有人在标志灯
sbit DU =P2^6;  		//段选信号
sbit WE =P2^7; 			//位选信号

sbit FM =P1^2; 			//主板设置
sbit EN =P2^5; 
sbit RST =P1^2; 

uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void delayms(uint);
void SHOW_TIME(unsigned int time);

void main()
{
	while(1)
	{
	     P3=0xf0;
		 key_l=P3;			//读P3端口的值
		 key_l=key_l&0xf0;  //令低4位置位为0
	 	if(key_l!=0xf0)    //判断是否有按键按下
		 {
	 		delayms(10);
	 	 	if(key_l!=0xf0)
	 	 	{					//若有按键按下，则切换高低4位判断键值
		 	  key_l=P3&0xf0;   //11100000	获取第一次键值
			  key_l=key_l|0x0f;//11101111   
		 	  P3=key_l;        //反过来再读一次
		 	  key_h=P3;        
		 	  key_h=key_h&0x0f;//00001110
		 	  key_l=key_l&0xf0;//11100000
		 	  key=key_h+key_l; //11101110
	  		}
	 	}
		 switch (key)
		 {
			  case 0xee:time=0;break;
			  case 0xde:time=1;break;
			  case 0xbe:time=2;break;
			  case 0x7e:time=3;break;
			  case 0xed:time=4;break;
			  case 0xdd:time=5;break;
			  case 0xbd:time=6;break;
			  case 0x7d:time=7;break;
			  case 0xeb:time=8;break;
			  case 0xdb:time=9;break;
		 } 
		while(LIGHT_in!=0)	   //光敏阻断
		 {   
		  	if(HW_in==1)
			 { 
			 	LED0=0;	
				flag=1;
			 }
			 if(flag==1&&HW_in==0)
			{	
					SHOW_TIME(time);
					LED0=1;
					flag=0;
			}
		}		 
	}
}
void SHOW_TIME(unsigned int time)
{
	uint i,j;
	for(i=time;i>=0;i--)
		{
			DU=1;
			P0=table[i];
			DU=0;
			P0=0xff;
			WE=1;
			P0=0xfe; //1111 1110
			WE=0;
				for(j=20;j>0;j--)
				{
					delayms(50);	  	
				}
		}
}
void delayms(uint xms)
{
 uint i,j;
 for(i=xms;i>0;i--)
    for(j=120;j>0;j--);
}												 