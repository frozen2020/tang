/**********************************************

Name	: includes.h
Function: Data type,constant and something else.
***********************************************/

#include <reg51.h>


//----------Pin for YM1602C-------------
#define LCD_DataPort P2
sbit LCD_RS=P3^4;  //�Ĵ���(����/ָ��)ѡ���ź�
sbit LCD_RW=P3^5;  //��дѡ��
sbit LCD_E =P3^7;  //���ݶ�������


//----------Pin for AT25320A-----------
sbit AT25320_SI=P1^1;
sbit AT25320_SO=P1^0;
sbit AT25320_SCK=P1^2;
sbit AT25320_CS=P1^3;


/*    DATA TYPE    */
#define tByte unsigned char
#define tWord unsigned int
#define tLong unsigned long

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

