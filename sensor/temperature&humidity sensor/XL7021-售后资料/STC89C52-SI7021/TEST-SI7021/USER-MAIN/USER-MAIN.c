
#include "..\myConfig.h"
#include <intrins.h>
#include <string.h>
#include <reg52.h>
#include <reg52.h>


#define U8 unsigned char
#define U16 unsigned int

extern void ini_lcd(void);
extern void lcd_printf_char(U8 disp_char, U8 row_col);
extern void lcd_printf_string(U8 *disp_str, U8 row_len_col);


typedef	struct _si7021_value_{
	union16 temp;
	union16 humi;
	unsigned char crc;
}si7021_value_ST, *p_si7021_value_ST;

si7021_value_ST gv_si7021_value;

#define	CHECK_AA	0xAA
#define	CHECK_55	0x55

unsigned char temp_array[8] = "        ";
unsigned char Rf_Rec_Cnt;

unsigned long cal_temp_u32;
unsigned int cal_temp_u16;
unsigned char RH_value;

unsigned char TEMP_H;
unsigned char TEMP_L;


int main ( void )
{
	
	ini_lcd();
	delay_2us(50000);
#if 0	
   lcd_printf_string(" si7021 ", ROW(0x00)|LEN(0x08)|COL(0x00));
	lcd_printf_string("  htc   ", ROW(0x01)|LEN(0x08)|COL(0x00));
	Rf_Rec_Cnt=243;
	hex_to_assic(Rf_Rec_Cnt,temp_array);
	lcd_printf_string(temp_array, ROW(0x01)|LEN(0x03)|COL(0x00));
	
	lcd_printf_string(".       ", ROW(0x01)|LEN(0x01)|COL(0x03));
	
	Rf_Rec_Cnt=123;
	hex_to_assic(Rf_Rec_Cnt,temp_array);
	lcd_printf_string(temp_array, ROW(0x01)|LEN(0x03)|COL(0x04));
#endif
	
	uart_init ();

	EA = 1;

	while ( 1 )
	{

		//if ( gv_uart_buflen >= 5 )
		{
			measure_si7021 ( TEMP_HOLD_MASTER, (union16 *)(&gv_si7021_value.temp) );
			measure_si7021 ( HUMI_HOLD_MASTER, (union16 *)(&gv_si7021_value.humi) );
			gv_uart_buflen = 0;
			//if ( CHECK_AA==gv_uart_buf[0] && CHECK_55==gv_uart_buf[1] )
			{
				gv_uart_buf[2] = gv_si7021_value.temp.uchar[HSB];
				gv_uart_buf[3] = gv_si7021_value.temp.uchar[LSB];
				gv_uart_buf[4] = gv_si7021_value.humi.uchar[HSB];
				gv_uart_buf[5] = gv_si7021_value.humi.uchar[LSB];
				uart_send_buf ( 0x6, gv_uart_buf );
				//memset ( (unsigned char *)(&gv_uart_buf[0]), 0, MAX_UART_BUF );
//---------------------			 
            cal_temp_u16 = gv_uart_buf[4];
	         cal_temp_u16 = cal_temp_u16 <<8;
	         cal_temp_u16 += gv_uart_buf[5];
	
	         cal_temp_u32 =  cal_temp_u16;
	         cal_temp_u32 = 125* cal_temp_u32;
	         cal_temp_u32 = cal_temp_u32 >>16;
	         RH_value = cal_temp_u32;
	         RH_value = RH_value -6;
				
				hex_to_assic(RH_value,temp_array);
	         lcd_printf_string(temp_array, ROW(0x00)|LEN(0x08)|COL(0x00));
//------------------------				
				
	         cal_temp_u16 = gv_uart_buf[2];
	         cal_temp_u16 = cal_temp_u16 <<8;
	         cal_temp_u16 += gv_uart_buf[3];
	         cal_temp_u32 =  cal_temp_u16;
	         cal_temp_u32 = 17572* cal_temp_u32;
	         cal_temp_u32 = cal_temp_u32 >>16;
	         cal_temp_u32 = cal_temp_u32 -4685;
	         TEMP_H = cal_temp_u32/100;
	         TEMP_L = cal_temp_u32%100;
				hex_to_assic(TEMP_H,temp_array);
				lcd_printf_string(temp_array, ROW(0x01)|LEN(0x03)|COL(0x00));
				
				lcd_printf_string(".       ", ROW(0x01)|LEN(0x01)|COL(0x03));
				
				hex_to_assic(TEMP_L,temp_array);
				lcd_printf_string(temp_array, ROW(0x01)|LEN(0x03)|COL(0x04));
				
				
				delay_2us(50000);
         }
		}
	}
}
