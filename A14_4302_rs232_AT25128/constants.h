#include "f2407_c.h"

/*    DATA TYPE    */
#define tByte unsigned char
#define tWord unsigned int
#define tLong unsigned long

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
/*  AT25320 op_code */
#define	WREN	6	//	0000 x110,write enable
#define	WRDI	4	//	0000 x100,write disable
#define	RDSR	5	//	0000 x101,read status register
#define	WRSR	1	//	0000 x001,write status register
#define	READ	3	//	0000 x011,read sequence
#define	WRITE	2	//	0000 x010,write sequence

/* Sytem Definitions */
#define D1_MAXTEMP	350
#define D1_MINTEMP 120
#define D2_MAXTEMP 350
#define D2_MINTEMP 120
#define LAS_MAXTEMP 360
#define LAS_MINTEMP 120
//#############################
//#define ENV_MAXTEMP 350
#define ENV_MAXTEMP 400
//#############################
#define ENV_MINTEMP 120

#define BEEPER_BIT	0x0020

#define pwm_per  2000			/* period, 20KHz PWM, 40MHz CPUCLK 	*/
#define HALF 1000				/* 50% DUTY CYCLE 					*/
#define MAX_AMPS 300.0
#define MAX_CNTS 1000
#define INV_MAX_AMPS (1.0/500)
#define MAX_DISPLAY_AMPS 200

#define GATE (*PADATDIR & 0x0008)
#define KEYSW_ON (*PADATDIR & 0x0020)
#define VALUE_LENGTH 6

