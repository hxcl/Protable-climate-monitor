/************************************************************************************
;copyrightn   :shenzhen coolwaveasia 
;filename     :lcd.h
;writeby      :dengyihong
;*************************************************************************************/

#ifndef _LCD_H
#define	_LCD_H

//#include "maindef.h"
//#include "io.h"

#define U8 unsigned char
#define U16 unsigned int




#define   ROW(x)       (0x80|(x << 0x06))
#define   COL(x)       (x)
#define   LEN(x)       ((x-0x01) << 0x03)

#define   LEN_MASK     0x38
#define   COL_MASK     0x07
#define   ROW_MASK     0xC0
#define   ROW_COL      (ROW_MASK|COL_MASK)
	
#define   HexDisp(x)   HexDispArray[x]
#define   BYTE_LOW(x)  (x & 0x0F) 
#define   BYTE_HIGH(x) ((x & 0xF0)>>0x04)
/*
void ini_lcd(void);
void lcd_printf_char(U8 disp_char, U8 row_col);
void lcd_printf_string(U8 *disp_str, U8 row_len_col);
void lcd_write_reg(U8 command);
void lcd_write_data(U8 value);
void lcd_wait(void);
*/

void delay_2us(U16 delay_cnt);

void ini_lcd(void);
void lcd_printf_char(U8 disp_char, U8 row_col);
void lcd_printf_string(U8 *disp_str, U8 row_len_col);
void lcd_write_reg(U8 command);
void lcd_write_data(U8 value);
void lcd_wait(void);
void hex_to_assic(U8 hex_data, U8 *str);

//extern void delay_2us(U16 delay_cnt);


#endif