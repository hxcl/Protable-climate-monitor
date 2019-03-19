

#ifndef	__MCU_STC11L04_H
#define	__MCU_STC11L04_H

#if 0
#define	SYSCLK	12000000
#define	BAUDRATE	57600//9600
#else
#define	SYSCLK	11059200
#define	BAUDRATE	57600//9600
#endif

//STC11L04扩展寄存器定义说明
sfr	BRT = 0x9C;//独立波特率发生器
sfr	AUXR = 0x8E;
sfr	AUXR1 = 0xA2;

#define	RELOAD	( 256 - (u8)(((SYSCLK/BAUDRATE)/32)+0.5) );

#define	MAX_UART_BUF	10
extern unsigned char gv_uart_buf[MAX_UART_BUF];
extern unsigned char gv_uart_buflen;

void uart_init ( void );
void send_data ( unsigned char indata );
void uart_send_buf ( int len, unsigned char *packet );

#define	UART_DEBUG 0
#if UART_DEBUG
void msg ( unsigned char *printf_msg );
#endif//if UART_DEBUG


#endif//ifndef	__MCU_STC11L04_H




