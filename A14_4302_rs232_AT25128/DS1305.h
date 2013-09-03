extern void DS1305Init(void);
extern unsigned short DS1305ReadData(unsigned short* pData,unsigned short wLength);
extern void DS1305WriteData(unsigned short* pData,unsigned short wLength);
extern unsigned short DS1305ReadTime(struct DEVICETIME* pDeviceTime);
extern void DS1305WriteTime(struct DEVICETIME* pDeviceTime);
extern void BatteryCharge(unsigned short wOnchargeDay);

