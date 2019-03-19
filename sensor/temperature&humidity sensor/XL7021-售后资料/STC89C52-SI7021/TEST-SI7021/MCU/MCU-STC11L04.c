#include "MCU-STC11L04.h"

#include <reg52.h>

//函数名称：
//函数功能：
//参数描述：
// 返 回 值：
void uart_init ( void )
{
#if 0	
	SCON = 0x50;	//UART 方式1 , 8位可变波特率，无奇偶校验位
	PCON |= 0x80;  
	BRT  = 256-(int)(SYSCLK/BAUDRATE/16+0.5);	
	AUXR = 0x15;  	//BRTR=1,启动独立波特率发生器
					// 1T模式	Baud=Fosc/(256-RELOAD_COUNT)/32
					// S1BRS	=1,串口1选择独立波特率发生器作为波特率发生器
//	AUXR1|=0x80;    //UART P3 switch to P1

	ES = 1;		//允许串口中断
	PS = 1;
#else
    TMOD = 0X021;        //T0 WORKING AT MODEL 1 16BITS COUNTER,t1--8bit autoload
    //ET0 = 1;             //PERMIT T0 INTERRUPT
    //ET1 = 0;
    EA = 1;              //ALL INTERRUPT PERMIT?
    //TR0 = 1;             //T0 START WORKING
    TL1 = 253;//0X0E8;
    TH1 = 253;//0X0E8;         //BAUD =11.0592M/12/32/(256-253)=9600B/S
    //TL1 = 0X0fc;
    //TH1 = 0X0fc;         //BAUD =1.8432M/12/32/(256-252)=1200B/S
    //TL1 = 0X0f8;
    //TH1 = 0X0f8;         //BAUD =1.8432M/12/32/(256-248)=600B/S
    TR1 = 1;             //T1 START WORKING
    PCON = 0X000;        //SMOD=1????,--2400b/s


    /*UART SETTING**************************************/
    SCON = 0X050;       //UART WORKING AT MODEL 1/????,ENABLE RECEIVING
    ES = 1;             //enable UART RECEIVING
#endif	
	
	
}
unsigned char gv_uart_buf[MAX_UART_BUF];
unsigned char gv_uart_buflen=0;
void uart_inter ( void ) interrupt 4 using 0
{
	if ( 1==RI )
	{
		RI = 0;

		gv_uart_buf[gv_uart_buflen] = SBUF;
		gv_uart_buflen ++;	
	}
}
//函数名称：
//函数功能：
//参数描述：
// 返 回 值：
void send_data ( unsigned char indata )
{
	SBUF = indata;
	while ( !TI );
	TI = 0;
}
//函数名称：
//函数功能：
//参数描述：
// 返 回 值：
void uart_send_buf ( int len, unsigned char *packet )
{
	if ( len==0 ) return ;
	do{
		send_data ( *packet ++ );
		len --;	
	}while ( len );
}

#if	UART_DEBUG
//函数名称：
//函数功能：
//参数描述：
// 返 回 值：
void msg ( unsigned char *printf_msg )
{
	while ( *printf_msg )
		send_data ( *printf_msg ++ );
}
#endif //if UART_DEBUG
