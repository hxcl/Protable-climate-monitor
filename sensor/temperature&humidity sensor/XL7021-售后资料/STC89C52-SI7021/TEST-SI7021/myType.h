
#ifndef	__myType_H
#define	__myType_H

typedef	unsigned char u8;
typedef	signed char s8;
typedef	unsigned int u16;
typedef	signed int s16;
typedef	long l32;
typedef	float f32;

typedef	union union16_{
	unsigned int uint;
	unsigned char uchar[2];
}union16;
typedef union union32_{
	long _long;
	unsigned int uint[2];
	unsigned char uchar[4];
}union32;

#define	HSB	0
#define	LSB	1

#define	BIT_HIGH 	1
#define	BIT_LOW		0

#endif//ifndef	__myType_H




