#include <Main.h>

/*******************************************************************/
static unsigned char ReadByteBCD(void)
{
	unsigned char DataBCD;
	DataBCD = SPIReadByte();
	return ((DataBCD&0x0f)+10*(DataBCD>>4));
}

static void SendByteHEX(unsigned char DataHEX)
{
	SPISendByte((DataHEX%10)+((DataHEX/10)<<4));
}

/*******************************************************************/
void DS1305Init(void)
{
	SPIOpen();
	SPISendByte(0x8f);
	SPISendByte(0x00);
	SPIClose();
	SPIOpen();
	SPISendByte(0x91);
	SPISendByte(0x00);//0xaa:OnCharge (5-2*0.7)/4k = 0.9mA; 0x00: offCharge
	SPIClose();
}

unsigned short DS1305ReadData(unsigned short* pData,unsigned short wLength)
{
	unsigned int i;
	unsigned short wDataH;
	unsigned short wDataL;
	unsigned short bValidRAM;
	SPIOpen();
	SPISendByte(0x20);
	bValidRAM = 1;
	if(SPIReadByte()!=(g_wDeviceType>>8)) bValidRAM = 0;
	if(SPIReadByte()!=(g_wDeviceType&0xff)) bValidRAM = 0;
	if(SPIReadByte()!=(g_wDeviceType>>8)) bValidRAM = 0;
	if(SPIReadByte()!=(g_wDeviceType&0xff)) bValidRAM = 0;
	if(bValidRAM)
	{
		for(i=0;i<wLength;i++)
		{
			wDataH = SPIReadByte();
			wDataL = SPIReadByte();
			*pData++ = (wDataH<<8)+wDataL;
		}
	}
	SPIClose();
	return bValidRAM;
}

void DS1305WriteData(unsigned short* pData,unsigned short wLength)
{
	unsigned int i;
	SPIOpen();
	SPISendByte(0xa0);
	SPISendByte(g_wDeviceType>>8);
	SPISendByte(g_wDeviceType&0xff);
	SPISendByte(g_wDeviceType>>8);
	SPISendByte(g_wDeviceType&0xff);
	for(i=0;i<wLength;i++)
	{
		SPISendByte((*pData)>>8);
		SPISendByte((*pData)&0xff);
		pData++;
	}
	SPIClose();
}

unsigned short DS1305ReadTime(struct DEVICETIME* pDeviceTime)
{
	pDeviceTime->wMilliSecond = 500;
	if(!DS1305ReadData(0,0))
	{
		pDeviceTime->wYear = 0;
		pDeviceTime->wMonth = 1;
		pDeviceTime->wDay = 1;
		pDeviceTime->wHour = 0;
		pDeviceTime->wMinute = 0;
		pDeviceTime->wSecond = 0;
		return 0;
	}
	SPIOpen();
	SPISendByte(0x00);
	pDeviceTime->wSecond = ReadByteBCD();
	pDeviceTime->wMinute = ReadByteBCD();
	pDeviceTime->wHour = ReadByteBCD();
	SPIReadByte();
	pDeviceTime->wDay = ReadByteBCD();
	pDeviceTime->wMonth = ReadByteBCD();
	pDeviceTime->wYear = ReadByteBCD();
	SPIClose();
	return 1;
}

void DS1305WriteTime(struct DEVICETIME* pDeviceTime)
{
	SPIOpen();
	SPISendByte(0x80);
	SendByteHEX(pDeviceTime->wSecond);
	SendByteHEX(pDeviceTime->wMinute);
	SendByteHEX(pDeviceTime->wHour);
	SPISendByte(0x01);
	SendByteHEX(pDeviceTime->wDay);
	SendByteHEX(pDeviceTime->wMonth);
	SendByteHEX(pDeviceTime->wYear);
	SPIClose();
}

/*******************************************
		ds1305电池充电
		每月1号充电一天
		充电电流wI_charge ：0.9mA
		0xaa: (5-2*0.7)/4k = 0.9mA;
		0x00: offCharge;
		void BatteryCharge(void)
********************************************/
void BatteryCharge(unsigned short wOnchargeDay)
{
	unsigned short wI_charge = 0x00;
	if(wOnchargeDay==1)	wI_charge = 0xaa;
	SPIOpen();
	SPISendByte(0x91);
	SPISendByte(wI_charge);		//0xaa: (5-2*0.7)/4k = 0.9mA; 0x00: offCharge
	SPIClose();
}