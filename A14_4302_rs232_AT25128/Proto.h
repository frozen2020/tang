
/*		DATE: APRIL,25 2005   */

#ifndef __PROTO_H__
#define __PROTO_H__
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void First( void );
void AT25_GetStatusReg(void);
unsigned short AT25_IsReady(void);
void Init_AT25320(unsigned short);
void AT25_SetStatusReg(unsigned short);
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void dspfun( void );
void message( char *);
void wait( short );
void num2ascii( unsigned long, short );
void wrtchrs( short );
void tempctl( void );
void Initialize( void );
void WriteData( void );
void WriteDallas2( unsigned short, short );
void ReadData( void );
unsigned short ReadDallas2( short  );
void clearstring( void );
unsigned short GETTEMP(float);
void EEPROM_Write_Enable(void)  ;
//RS232
void sciInit(void);
//id echo(char *);
void echo(void);
void echo2(void);
void runQuery(void);
void runCommand(void);
void sciPolling(void);
void longToString(unsigned long, char *);
unsigned long stringToLong(char *);
void shutterOff();
void qswonAction();
void diodeAction();
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void diodeAction_1(unsigned long,unsigned long,unsigned long,unsigned long);
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void alarmAction();
void resetAction();
void pulseRateAction();
void keyswOffAction (short *, short *, short *);
void qswextAction ();
void shtonAction();
void defaultAction(short *, short *);
void keyswFirstOnAction(short *, short *,short *);
void functionAction(short * );
void clearScreen(void);




#endif
