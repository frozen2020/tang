#include "constants.h"
#include "extern.h"
#include "Proto.h"

/********************** INTERRUPT SERVICE ROUTINES *********************/
/*1. TIMER 1 INTERRUPT ROUTINE   */
interrupt void timer1_isr(void)
{
	*EVAIFRA = 0x0080;      /* clear TIMER1 PERIOD INTERRUPT flagS */
	if( INTEST ) INTEST--;
	if( ADTIMER ) {ADTIMER--;
		if (ADTIMER % 500 ==0)
		{ 
		if( !(*ADCTRL2 & 0x1000) )    // MAKE SURE ADC READY
		{ 
		ADTEMP0[ADi] =	((((*RESULT0>>6)+(*RESULT8>>6))>>1) & 0x3FF);
		ADTEMP1[ADi] =	((((*RESULT1>>6)+(*RESULT9>>6))>>1) & 0x3FF);
		ADTEMP2[ADi] =	((((*RESULT2>>6)+(*RESULT10>>6))>>1) & 0x3FF);
		ADTEMP3[ADi] =	((((*RESULT3>>6)+(*RESULT11>>6))>>1) & 0x3FF);
		ADTEMP4[ADi] =	((((*RESULT4>>6)+(*RESULT12>>6))>>1) & 0x3FF);
		ADTEMP5[ADi] =	((((*RESULT5>>6)+(*RESULT13>>6))>>1) & 0x3FF);
		ADTEMP6[ADi] =	((((*RESULT6>>6)+(*RESULT14>>6))>>1) & 0x3FF);
		ADTEMP7[ADi] =	((((*RESULT7>>6)+(*RESULT15>>6))>>1) & 0x3FF);
   		}
		ADi++;
		if (ADi>=4)
		{
  		 ENVIR=(ADTEMP0[0]+ADTEMP0[1]+ADTEMP0[2]+ADTEMP0[3])/4;
			T1=(ADTEMP1[0]+ADTEMP1[1]+ADTEMP1[2]+ADTEMP1[3])/4;
			T2=(ADTEMP2[0]+ADTEMP2[1]+ADTEMP2[2]+ADTEMP2[3])/4;
			T3=(ADTEMP3[0]+ADTEMP3[1]+ADTEMP3[2]+ADTEMP3[3])/4;
			T4=(ADTEMP4[0]+ADTEMP4[1]+ADTEMP4[2]+ADTEMP4[3])/4;
			T5=(ADTEMP5[0]+ADTEMP5[1]+ADTEMP5[2]+ADTEMP5[3])/4;;
			T6=(ADTEMP6[0]+ADTEMP6[1]+ADTEMP6[2]+ADTEMP6[3])/4;;
	   	EXTDCUR=(ADTEMP7[0]+ADTEMP7[1]+ADTEMP7[2]+ADTEMP7[3])/4;;
			ADi=0;
		}	
	/*** START ADC SEQUENCE ***/
    *ADCTRL2 = *ADCTRL2 | 0x4000;
    wt = 0;
    *ADCTRL2 = *ADCTRL2 | 0x2000;
    }
}
	if(LOOP) LOOP--;
	if(BEEPER)
		{
		if(BTIME > 2) BTIME = 0;
		else BTIME++;
		if(!BTIME) *PFDATDIR = (*PFDATDIR ^ BEEPER_BIT);
	 	}
} 	

/*2. TRIGGER INTERRUPT ROUTINE   */   
interrupt void xint1(void)  //extern trigger: FREQ++, clear interrup
{  
    if((*XINT2CR) & 0x0004)
		{
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//*T4CMPR = FPS_LEVEL;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		*XINT2CR = 0x8001;
		}
	else
		{
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//*T4CMPR = 100;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		*XINT2CR = 0x8005;
		}	
}   
	
    //if((*PIRQR0)&0x0004)   //xint1
	//{
//		if( QSWEXT )
//		{
//		*XINT1CR = *XINT1CR | 0x8001;
 //		FREQ++;
   //		}   		
   	//	*PIACKR0=(*PIACKR0)|0x0004;
   	//}
//}
/*   	
   	else if( (*PIRQR0)&0x0008)   //xint2
   	{
   	if(*XINT2CR & 0x0004)
		{
		*T4CMPR = FPS_LEVEL<<2;
		*XINT2CR = 0x8001;
		}
	else
		{
		*T4CMPR = 400;
		*XINT2CR = 0x8005;
		}
	*PIACKR0=(*PIACKR0)|0x0008;		
	}   	
}		 /* End xint1() */


/*3. GATE INTERRUPT ROUTINE   */  
//interrupt void xint2(void)   //1. clear int. 2.set T4 compare register at array index.
//{    
//	if(*XINT2CR & 0x0004)
//		{
//		*T4CMPR = FPS_LEVEL<<2;
//		*XINT2CR = 0x8001;
//		}
//	else
//		{
//		*T4CMPR = 400;
//		*XINT2CR = 0x8005;
//		}
//} 	
/*4 RS232 INTERRUPT*/
interrupt	void    uarttr(void)    		//中断服务程序
{	switch (*PIVR)			//根据中断向量寄存器PVIR的值区别是接收还是发送中断
	{
        case 6:    sciPolling();break;	//如果PIVR=6，则发生了接收中断，执行接收服务程序
    	case 7:	   echo2(); break;//清除IFR中相应的中断标志 
	}
}
