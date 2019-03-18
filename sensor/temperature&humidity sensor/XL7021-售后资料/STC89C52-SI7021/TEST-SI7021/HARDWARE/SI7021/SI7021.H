#ifndef	_SI7021_H
#define	_SI7021_H

#include "..\..\myType.h"
#include <reg52.h> 


//sbit	SI7021_SCLK	=	P3^4;
//sbit	SI7021_SDA	=	P3^3;
sbit	SI7021_SCLK	=	P1^0;
sbit	SI7021_SDA	=	P1^1;

#define	WRITE_CMD		0x80
#define	READ_CDM		0x81
#define	SALVE_ADDR		0x80

#define	HUMI_HOLD_MASTER	0xE5
#define	TEMP_HOLD_MASTER	0xE3
		
#define	HUMI_NOHOLD_MASTER	0xF5
#define	TEMP_NOHOLD_MASTER	0xF3

#define	SI7021_SCLK_HIGH()	SI7021_SCLK = BIT_HIGH
#define	SI7021_SCLK_LOW()	SI7021_SCLK = BIT_LOW

#define	SI7021_SDA_HIGH()	SI7021_SDA = BIT_HIGH
#define	SI7021_SDA_LOW()	SI7021_SDA = BIT_LOW


void measure_si7021 ( unsigned char model, union16 *value );



#endif//ifndef	_SI7021_H