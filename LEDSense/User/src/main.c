#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

uchar key_l,key_h;		//���̶˿ڶ���
uchar key;
unsigned int flag=0;	//������־λ
unsigned int time=5; 	//��ʱʱ��
sbit SOUND_in=P2^5;		//��������˿ڶ���
sbit LIGHT_in=P2^4;		//��������˿ڶ���
sbit HW_in=P2^2 ;		//��������˿ڶ���
sbit LED0 =P1^0; 		//������ʾ����˿�
sbit LED1 =P1^1;		//�����ڱ�־��
sbit DU =P2^6;  		//��ѡ�ź�
sbit WE =P2^7; 			//λѡ�ź�

sbit FM =P1^2; 			//��������
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
		 key_l=P3;			//��P3�˿ڵ�ֵ
		 key_l=key_l&0xf0;  //���4λ��λΪ0
	 	if(key_l!=0xf0)    //�ж��Ƿ��а�������
		 {
	 		delayms(10);
	 	 	if(key_l!=0xf0)
	 	 	{					//���а������£����л��ߵ�4λ�жϼ�ֵ
		 	  key_l=P3&0xf0;   //11100000	��ȡ��һ�μ�ֵ
			  key_l=key_l|0x0f;//11101111   
		 	  P3=key_l;        //�������ٶ�һ��
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
		while(LIGHT_in!=0)	   //�������
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