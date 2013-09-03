/********************************************************************
 
Name	 : AT25320.C
Function : Provide the operations include Read and Write to the 
		   AT25320A, SPI-interface EEPROM with 32k bits,ATMEL Icn.
Author	 : Pan.L.F
Date	 : 2006-02-19
**********************************************************************/

/*********************************************************************

Modify	:
Version	:
Modifier:
Date	:
*********************************************************************/

#include "extern.h"
#include "Proto.h"
#include "constants.h"


/*---------------------------------------------------------
             AT25_GetStatusReg()

Function:  Read the Status Register of the AT25320A
Input:     None.
Output:    Content of the status register,as a return value.
-----------------------------------------------------------*/
void AT25_GetStatusReg(void)
{     
	
    *SPITXBUF =0x0500;       /*发送读命令*/   
    while (*SPISTS == 0){;}   
    AT25_Status=*SPIRXBUF;   
    *SPISTS=0xFF;            /*清除标志位*/   
    *SPITXBUF = 0xFF;           /*发送伪数据*/   
    while (*SPISTS == 0){;}   
    AT25_Status=*SPIRXBUF;   

}


/*---------------------------------------------------------
             AT25_IsReady()

Function:  Return 0 if AT25320A is busy and 1 if ready.
-----------------------------------------------------------*/
unsigned short AT25_IsReady(void)
{
//	AT25_GetStatusReg();
//	if(0x01 & AT25_Status) return 0;
//	else return 1;

      
    *SPITXBUF =0x0500;       /*发送读命令*/   
    while(*SPISTS & 0x20);
    AT25_Status=*SPIRXBUF;   
    *SPISTS=0xFF;            /*清除标志位*/   
    *SPITXBUF = 0xFF;           /*发送伪数据*/   
    while(*SPISTS & 0x20);
    AT25_Status=*SPIRXBUF;   
    *SPISTS=0xFF;            /*清除标志位*/   
   	if(0x01 & AT25_Status) return 0;
	else return 1; 
}


/*********************************************************************  
    函数名：    void EEPROM_Write_Enable(void)  
    目的：     EEPROM的写使能  
    输入：     无  
    输出：     无  
*********************************************************************/   
void EEPROM_Write_Enable(void)   
{   
    unsigned int i;   
    //判断SPI发送准备好   
   	while(*SPISTS & 0x20);	
    //发送SPI   
    	*SPITXBUF  = 0x0600;   
    //判断SPI发送准备好   
    	while(*SPISTS & 0x20);	 
}   

/*---------------------------------------------------------
             AT25_SetStatusReg()

Function:  Set the Status Register of the AT25320A
Input:     The Byte of the status register. NOTE: Only 
		   bit7(WPEN),bit3(BP1) and bit2(BP0) can be changed,
		   so this byte should in the form of: x000 xx00		
Output:    None. 
-----------------------------------------------------------*/
void AT25_SetStatusReg(unsigned short status_data)
{	
	/* wait when device is busy */
	while(!AT25_IsReady());

	/* make sure that the device is write enabled */
	WriteDallas2(WREN,1);
	WriteDallas2(WRSR,1);
	WriteDallas2(status_data & 0x8C,1);		
}







