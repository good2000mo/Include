//*********************************************************
//        Joinmax Digital Module library 1.0
//*********************************************************
// File                 : JMLib.c 
// Version              :  V1.0
// Compiler             : GCCARM
// Target               : STM32F207VET6
// Author               : TQB
// Support telephone    : +86 20 84134792 (JoinMax digital)
// Support fax          : +86 20 84134890 (JoinMax digital)
//********************  Module List  **********************
//   SetCentiS
//   SetNS
//   SetTenthS
//   GetIRDist        _IRDISTANCE_
//   GetIRDete        _IRDETECT_
//   GetPhoto         _PHOTOSENSOR_
//   GetRemoIR        _FLAMEDETECT_
//   GetADScable      _SCABLEAD_
//   GetTentacle      _TOUCH_
//   GetTouch         _TOUCH_
//   SetIR            _IRAUTO_
//   SetLCD1Char      _CHARLCD_
//   SetLCD3Char      _CHARLCD_
//   SetLCD8Char      _CHARLCD_
//   SetLCD16Char     _CHARLCD_
//   SetLCDBack       _CHARLCD_
//   GetUaByte
//   GetSelector      _SELECTOR_
//   SetUaByte
//   SetFan           _FAN_
//   SetLED           _LED_
//   SetMotor         _MOTOR_
//   SetMotor2 
//   SetServo         _SERVO_
//   SetSpkFreq       _SPEAKER_
//   GetSysTime
//   SetSysTime
//   GetCompassB      _COMPASS_
//   SetSCUServo      _SERVOCTRL_
//   GetVolume        _MICROPHONE_
//   GetTemperature   _TEMPERATURE_
//   GetCompoI        _COMPOUNDEYE_
//   GetUltrasound    _ULTRASOUND_
//   GetWireless      _WIRELESS_
//   SetWireless      _WIRELESS_
//   Setdata
//   Getdata
//   SetSwtich        _SWITCH_
//   GetADextend      _ADEXTEND_
//   GetCalendar      _CALENDAR_
//   setCalendar      _CALENDAR_
//   SetBE2560LCD1       _CALENDAR_
//   SetBE2560LCD3      _CALENDAR_
//   SetBE2560LCD8      _CALENDAR_
//   SetBE2560Back      _CALENDAR_
//   SetBE2560spk      _CALENDAR_
//   GetRFIDlastdata	_RFID_
//   SetRFIDAddress	_RFID_
//   SetRFIDData	_RFID_
//   GetRFIDData	_RFID_
//   GetMp3No		_MP3_
//   SetMp3No		_MP3_
//   GetInfrared        _PYIFRARED_
//   GetHumidity        _HUMIDITY_ 
//   GetAcceleration	_ACCELERATION_
//   GetTrace           _TRACE_
//   GetTraceRef        _TRACE_      
//   SetBuzzer          _TRACE_
//   SetIntegrateMotor	_INTEGRATE_	//BE1729
//	 GetIntegrateAdc	_INTEGRATE_	//BE1729
//	 GetColorSensor		_COLOR_
//	 SetColorSensor		_COLOR_
//*********************************************************
//IIC总线模块的地址(十六进制)
//模块名    十六进制地址				
//BE-2610 ： 3B
//BE-5221 :  02
//BE-1721 :  03
//BE-6301 :  04
//BE-9231 :  05
//BE-1311 :  06
//BE-4200 :  07
//BE-2560 :  07
//BE-9240 :  07
//BE-2203 :  63
//BE-2620 :  38
//BE-1118 :  0A
//BE-1118B:  0B 
//BE-1128 :  0C
//BE-1729 :  18
//**********************  HISTORY  ************************


//*********************************************************
#include "ZMkernel.h"
#include <math.h>
#include "command.h"

SlaveMcuData_typeDef SlaveMcuData;
vu8 TTSC_Flag;
//==SetNSec Readding ID:  == DON'T DELETE!! ==

#ifdef _SETTHOUSANDTHS_
#ifndef  _SETTHOUSANDTHS_EXISTS_
#define _SETTHOUSANDTHS_EXISTS_
  void SetThousandthS(u8 s){
    u32 endtime;
    endtime=(u32)s;
    delayms(endtime);
  }
 #endif
#endif

//==SetCentiSec Readding ID:  == DON'T DELETE!! ==

#ifdef _SETCENTIS_
 #ifndef  _SETCENTIS_EXISTS_
  #define _SETCENTIS_EXISTS_
  void SetCentiS(u8 s){
    u32 endtime;
    endtime = (u32)s*10;
    delayms(endtime);
  }
 #endif
#endif

//==SetTenthSec Readding ID:  == DON'T DELETE!! ==

#ifdef _SETTENTHS_
 #ifndef  _SETTENTHS_EXISTS_
  #define _SETTENTHS_EXISTS_
  void SetTenthS(u8 s){
    u32 endtime;
    endtime=(u32)s*100;
    delayms(endtime);
  }
 #endif
#endif


//==SetNSec Readding ID:  == DON'T DELETE!! ==

#ifdef _SETNS_
 #ifndef  _SETNS_EXISTS_
  #define _SETNS_EXISTS_
  void SetNS(u8 s){
    u32 endtime;
    endtime=(u32)s*1000;
    delayms(endtime);
  }
 #endif
#endif

//==GetIRDist Readding ID:  == DON'T DELETE!! ==

#ifdef _GETIRDIST_
 #ifndef  _GETIRDIST_EXISTS_
  #define _GETIRDIST_EXISTS_
  #ifndef _IRDISTANCE_
   #define _IRDISTANCE_ unsigned long
  #endif

  u16 GetIRDist(_IRDISTANCE_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
    u16 i;
    u8 channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return (u16)i;
  }
 #endif
#endif

//==GetIRDete Readding ID:  == DON'T DELETE!! ==

#ifdef _GETIRDETE_
 #ifndef  _GETIRDETE_EXISTS_
  #define _GETIRDETE_EXISTS_
  #ifndef _IRDETECT_
   #define _IRDETECT_ u32
  #endif

  u8 GetIRDete(_IRDETECT_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);
    u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    if(value)
      return 0;
    else
      return 1;
  }
 #endif
#endif

//==GetVolume Readding ID:  == DON'T DELETE!! ==

#ifdef _GETVOLUME_
 #ifndef  _GETVOLUME_EXISTS_
  #define _GETVOLUME_EXISTS_
  #ifndef _MICROPHONE_
   #define _MICROPHONE_ u32
  #endif

  u16 GetVolume(_MICROPHONE_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
   u16 i;
   u8 channel;
   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
   channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return (u16)i;
  }
 #endif
#endif

//==GetPhoto Readding ID:  == DON'T DELETE!! ==

#ifdef _GETPHOTO_
 #ifndef  _GETPHOTO_EXISTS_
  #define _GETPHOTO_EXISTS_
  #ifndef _PHOTOSENSOR_
   #define _PHOTOSENSOR_ u32
  #endif

  u16 GetPhoto(_PHOTOSENSOR_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
    u16 i;
    u8 channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return (u16)i;
  }
 #endif
#endif

//==GetRemoIR Readding ID:  == DON'T DELETE!! ==

#ifdef _GETREMOIR_
 #ifndef  _GETREMOIR_EXISTS_
  #define _GETREMOIR_EXISTS_
  #ifndef _FLAMEDETECT_
   #define _FLAMEDETECT_ u32
  #endif

  u16 GetRemoIR(_FLAMEDETECT_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
    u16 i;
    u8 channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return (u16)i;
  }
 #endif
#endif

//==GetADScable10 Readding ID:  == DON'T DELETE!! ==

#ifdef _GETADSCABLE10_
 #ifndef  _GETADSCABLE10_EXISTS_
  #define _GETADSCABLE10_EXISTS_
  #ifndef _SCABLEAD_
   #define _SCABLEAD_ unsigned long
  #endif

  u16 GetADScable10(_SCABLEAD_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
    u16 i;
    u8 channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return i;
  }
 #endif
#endif

//==GetTemperature Readding ID:  == DON'T DELETE!! ==

#ifdef _GETTEMPERATURE_
 #ifndef  _GETTEMPERATURE_EXISTS_
  #define _GETTEMPERATURE_EXISTS_
  #ifndef _TEMPERATURE_
   #define _TEMPERATURE_ u32
  #endif

  u16 GetTemperature(_TEMPERATURE_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
    u16 i;
    u8 channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return (u16)i;
  }
 #endif
#endif

#ifdef _GETDIGITALTEMPERATURE_
 #ifndef  _GETDIGITALTEMPERATURE_EXISTS_
  #define _GETDIGITALTEMPERATURE_EXISTS_
  #include <DS18B20.h>
  #ifndef _DIGITALTEMPERATURE_
   #define _DIGITALTEMPERATURE_ unsigned long
  #endif

  unsigned char GetDigitalTemperature(_DIGITALTEMPERATURE_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    Dtemp_port=port1;
    Dtemp_Pin=bit1;
        unsigned char tempL,tempH,wendu;
	unsigned int x;
	resetDS18B20();
	write_charDS18B20(0xcc); 	        //跳过ROM
	write_charDS18B20(0x44);		//启动温度转换
	delay1us(1);
	resetDS18B20();
	write_charDS18B20(0xcc);		//跳过ROM
	write_charDS18B20(0xbe);		//读数据
	tempL=read_charDS18B20();
	tempH=read_charDS18B20();
        tempH=tempH&0x07;
	tempL=tempL>>4;
	tempH=tempH<<4;
	wendu=tempH|tempL;
	return(wendu);
  }
 #endif
#endif

//==GetTentacle Readding ID:  == DON'T DELETE!! ==

#ifdef _GETTENTACLE_
 #ifndef  _GETTENTACLE_EXISTS_
  #define _GETTENTACLE_EXISTS_
  #ifndef _TOUCH_
   #define _TOUCH_ u32
  #endif

  u8 GetTentacle(_TOUCH_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);
     u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    
    if(value)
      return 0;
    else
      return 1;
  }
 #endif
#endif

//==GetTouch Readding ID:  == DON'T DELETE!! ==

#ifdef _GETTOUCH_
 #ifndef  _GETTOUCH_EXISTS_
  #define _GETTOUCH_EXISTS_
  #ifndef _TOUCH_
   #define _TOUCH_ unsigned long
  #endif

  unsigned char GetTouch(_TOUCH_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
  GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);
    u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    if(value)
      return 0;
    else
      return 1;
  }
 #endif
#endif

//==GetCompassB Readding ID:  == DON'T DELETE!! ==

#ifdef _GETCOMPASSB_
 #ifndef  _GETCOMPASSB_EXISTS_
  #define _GETCOMPASSB_EXISTS_
  #include "I2C_Soft.h"
  #ifndef _COMPASS_
   #define _COMPASS_ unsigned long
  #endif

    u16 GetCompassB(_COMPASS_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    u8 low;
    u8 high;
    u16 angle;
    Soft_I2C_Start();
    Soft_I2C_Write(0x76);
    Soft_I2C_Write(0x01);
    Soft_I2C_Stop();

    Soft_I2C_Start();
    Soft_I2C_Write(0x77);
    high=Soft_I2C_Read(0);
    low=Soft_I2C_Read(1);
    Soft_I2C_Stop();

    if(high==1)
      angle=256+low;
    else
      if(high==0)
        angle=low;
      else
        angle=9999;
    return angle;
  }
 #endif
#endif


//==SetSCUServo Readding ID:  == DON'T DELETE!! ==

#ifdef _SETSCUSERVO_
 #ifndef  _SETSCUSERVO_EXISTS_
  #define _SETSCUSERVO_EXISTS_
  #include "I2C_Soft.h"
  #ifndef _SERVOCTRL_
   #define _SERVOCTRL_ unsigned long
  #endif

  unsigned char SetSCUServo(_SERVOCTRL_ which,unsigned char broadno,unsigned char channel,unsigned char angle){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char ack=1;
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x04);
    ack &=Soft_I2C_Write(0xff);
    ack &=Soft_I2C_Write((broadno<<4)|channel);
    ack &=Soft_I2C_Write(angle);
    Soft_I2C_Stop();
    return ack;
  }
 #endif
#endif

//==GetUaByte Readding ID:  == DON'T DELETE!! ==
 
#ifdef _GETUABYTE_
 #ifndef  _GETUABYTE_EXISTS_
  #define _GETUABYTE_EXISTS_
u8 GetUaByte(unsigned char br){
u32 BaudRate;
  switch(br)
  {
	case 0:BaudRate=9600  ;break;
	case 1:BaudRate=14400 ;break;
	case 2:BaudRate=19200 ;break;
	case 3:BaudRate=38400 ;break;
	case 4:BaudRate=57600 ;break;
	case 5:BaudRate=76800 ;break;
	case 6:BaudRate=115200;break;;
  }
  Uart4_configuration(BaudRate);
  return Uart4_GetData();
  }
 #endif
#endif

//==SetUaByte Readding ID:  == DON'T DELETE!! ==

#ifdef _SETUABYTE_
 #ifndef  _SETUABYT_EXISTS_
  #define _SETUABYT_EXISTS_

  void SetUaByte(unsigned char c,unsigned char br){
u32 BaudRate;
  switch(br)
  {
	case 0:BaudRate=9600  ;break;
	case 1:BaudRate=14400 ;break;
	case 2:BaudRate=19200 ;break;
	case 3:BaudRate=38400 ;break;
	case 4:BaudRate=57600 ;break;
	case 5:BaudRate=76800 ;break;
	case 6:BaudRate=115200;break;
  }
  Uart4_configuration(BaudRate);
   Uart4_SendData(c);
  }
 #endif
#endif

//==SetLCDBack Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCDBACK_
 #ifndef  _SETLCDBACK_EXISTS_
  #define _SETLCDBACK_EXISTS_
  void SetLCDBack(u8 led){
    if (led)
	SendCMD(Cmd_LcdBackOn);
    else
    SendCMD(Cmd_LcdBackOff);
  }
 #endif
#endif

//==SetLCD1Char Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCD1CHAR_
 #ifndef  _SETLCD1CHAR_EXISTS_
  #define _SETLCD1CHAR_EXISTS_
  #include "LCD220176.h"

  void SetLCD1Char(u8 x,u8 y,u8 data,u16 ch_color, u16 bg_color){
  SendCMD(Cmd_LcdBackOn);//
  LCD_en(x,y,data,ch_color, bg_color);
  }

 #endif
#endif

//==SetLCD3Char Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCD3CHAR_
 #ifndef  _SETLCD3CHAR_EXISTS_
  #define _SETLCD3CHAR_EXISTS_
  #include "LCD220176.h"

  void SetLCD3Char(u8 x,u8 y,u16 data,u16 ch_color, u16 bg_color)
  {
	SendCMD(Cmd_LcdBackOn);
   LCD_3g(x,y,data,ch_color,bg_color);
  }

 #endif
#endif

//==SetLCD5Char Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCD5CHAR_
 #ifndef  _SETLCD5CHAR_EXISTS_
  #define _SETLCD5CHAR_EXISTS_
  #include "LCD220176.h"

  void SetLCD5Char(u8 x,u8 y,u32 data,u16 ch_color,u16 bg_color){
  SendCMD(Cmd_LcdBackOn);
     LCD_5g(x,y,data,ch_color,bg_color);
  }

 #endif
#endif


//==SetLCD5Char Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCD5CHARSIGN_
 #ifndef  _SETLCD5CHARSIGN_EXISTS_
  #define _SETLCD5CHARSIGN_EXISTS_
  #include "LCD220176.h"

  void SetLCD5CharSign(u8 x,u8 y,u32 data,u16 ch_color,u16 bg_color){
     LCD_5bit(x,y,data,ch_color,bg_color);
  }

 #endif
#endif

//==SetLCD8Char Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCD8CHAR_
#ifndef  _SETLCD8CHAR_EXISTS_
#define _SETLCD8CHAR_EXISTS_
#include "LCD220176.h"

  void SetLCD8Char(u8 x,u8 y,u32 data,u16 ch_color,u16 bg_color)
  {
	SendCMD(Cmd_LcdBackOn);
     LCD_8g(x,y,data,ch_color,bg_color);
  }
 #endif
#endif

//==SetLCDString Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCDSTRING_
#ifndef  _SETLCDSTRING_EXISTS_
#define _SETLCDSTRING_EXISTS_

#include "LCD220176.h"

  void SetLCDString(u8 x,u8 y,u8* pic,u16 ch_color,u16 bg_color){
  SendCMD(Cmd_LcdBackOn);
   LCD_String(x,y,pic,ch_color,bg_color);
  }
 #endif
#endif

//==SetLCD1Chinese Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCD1CHINESE_
#ifndef  _SETLCD1CHINESE_EXISTS_
#define _SETLCD1CHINESE_EXISTS_

#include "LCD220176.h"

  void SetLCD1Chinese(u8 x,u8 y,u8* pic){
    Display_char_cn(x,y,pic);
  }
 #endif
#endif

//==SetLCDColume Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCDCOLUME_
#ifndef  _SETLCDCOLUME_EXISTS_
#define _SETLCDCOLUME_EXISTS_

#include "LCD220176.h"
void SetLCDColume(u8 x,u8 y,u8 ch){
Display_Colume(x,y,ch);
  }
 #endif
#endif

//==SetLCDpic Readding ID:  == DON'T DELETE!! ==

#ifdef   _SETLCDPIC_
#ifndef  _SETLCDPIC_EXISTS_
#define  _SETLCDPIC_EXISTS_

#include "LCD220176.h"
void SetLCDpic(u8* pic){
    Display_Picture(pic);
}
#endif
#endif

//==SetLCDClear Readding ID:  == DON'T DELETE!! ==

#ifdef   _SETLCDCLEAR_
#ifndef  _SETLCDCLEAR_EXISTS_
#define  _SETLCDCLEAR_EXISTS_

#include "LCD220176.h"
void SetLCDClear(u32 color){
SendCMD(Cmd_LcdBackOn);
    LCD_Pant(color);
}
#endif
#endif

#ifdef _SETLED_
 #ifndef  _SETLED_EXISTS_
  #define _SETLED_EXISTS_
  
  
  #ifndef _LED_
  #define _LED_ u32
  #endif

  void SetLED(_LED_ which,u8 state){
   struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;

   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
   if(state)
   GPIO_SetBits((GPIO_TypeDef*)port1,(1<<bit1));
   else
   GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
  }
 #endif
#endif

//==SetSwitch Readding ID:  == DON'T DELETE!! ==

#ifdef _SETSWITCH_
 #ifndef  _SETSWITCH_EXISTS_
  #define _SETSWITCH_EXISTS_
  
  
  #ifndef _SWITCH_
   #define _SWITCH_ u32
  #endif

  void SetSwitch(_SWITCH_ which,u8 state){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
    if(state>0){
      GPIO_SetBits((GPIO_TypeDef*)port1,(1<<bit1));
    }
    else{
      GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
    }
  }
 #endif
#endif

//==SetIR Readding ID:  == DON'T DELETE!! ==

#ifdef _SETIR_
 #ifndef  _SETIR_EXISTS_
  #define _SETIR_EXISTS_
  #ifndef _IRAUTO_
   #define _IRAUTO_ u32
  #endif

  void SetIR(_IRAUTO_ which,u8 state){
    struct select *information=&which;
   volatile unsigned int i=0;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
   for(i=0;i<9999;i++);
 if(state>0){
      GPIO_SetBits((GPIO_TypeDef*)port1,(1<<bit1));
   for(i=0;i<9999;i++);
    }
    GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
  }
 #endif
#endif

//==SetFan Readding ID:  == DON'T DELETE!! ==

#ifdef _SETFAN_
 #ifndef  _SETFAN_EXISTS_
  #define _SETFAN_EXISTS_
  
  
  #ifndef _FAN_
   #define _FAN_ u32
  #endif

  void SetFan(_FAN_ which,u8 state){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
   GPIO_Setting((GPIO_TypeDef*)port2,bit2,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
    switch(state){
      case 0:
	     GPIO_SetBits((GPIO_TypeDef*)port1,(1<<bit1));
	     GPIO_ResetBits((GPIO_TypeDef*)port2,(1<<bit2));
             break;
      case 1:
	     GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
	     GPIO_ResetBits((GPIO_TypeDef*)port2,( 1<<bit2));
             break;
      case 2:
	     GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
	     GPIO_SetBits((GPIO_TypeDef*)port2,(1<<bit2));
            break;
    }
  }

 #endif
#endif

#ifdef _SETMOTOR_
 #ifndef  _SETMOTOR_EXISTS_
 #define _SETMOTOR_EXISTS_
 
  #ifndef _MOTOR_
  #define _MOTOR_ u32
  #endif

void SetMotor(_MOTOR_ which,u8 state,u8 speed)
{
   struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;
   
   if(speed>99)speed=99;
   
   if((bit1==8&&port1==GPIOD)||(port2==GPIOC&&bit2==6))//M1
   {
		if(g_MotorPowerFlag)	speed=g_M1SpeedPer*speed/100;
		SetMotorX(1,state,speed);
   }
   if((bit1==9&&port1==GPIOD)||(port2==GPIOC&&bit2==7))//M2
   {
		if(g_MotorPowerFlag)	speed=g_M2SpeedPer*speed/100;
		SetMotorX(2,state,speed);
   }
   if((bit1==1&&port1==GPIOD)||(port2==GPIOC&&bit2==8))//M3
   {
		if(g_MotorPowerFlag)	speed=g_M3SpeedPer*speed/100;
		SetMotorX(3,state,speed);
   }
   if((bit1==2&&port1==GPIOD)||(port2==GPIOC&&bit2==9))//M4
   {
		if(g_MotorPowerFlag)	speed=g_M4SpeedPer*speed/100;
		SetMotorX(4,state,speed);
   }
   if((bit1==13&&port1==GPIOD)||(port2==GPIOD&&bit2==15))
   {
		SetMotor4(0,state,speed);
   }
    if((bit1==12&&port1==GPIOD)||(port2==GPIOD&&bit2==14))
   {
		SetMotor4(1,state,speed);
   }
}
 #endif
#endif

#ifdef _SETMOTOR2_
 #ifndef  _SETMOTOR2_EXISTS_
 #define _SETMOTOR2_EXISTS_
 
  #ifndef _MOTOR2_
  #define _MOTOR2_ u32
  #endif
void SetMotor2(u8 motor,s8 speed)
{
	if(g_MotorPowerFlag)
	{
		switch(motor)
		{
			case 1:speed=(s8)((s16)g_M1SpeedPer*speed/100);break;
			case 2:speed=(s8)((s16)g_M2SpeedPer*speed/100);break;
			case 3:speed=(s8)((s16)g_M3SpeedPer*speed/100);break;
			case 4:speed=(s8)((s16)g_M4SpeedPer*speed/100);break;
		}
	}
	if(speed==0)
	{
		SetMotorX(motor,1,speed);
	}
	else if(speed>0)
	{
		if(speed>99)speed=99;
		SetMotorX(motor,0,speed);
	}
	else
	{
		speed=-speed;
		if(speed>99)speed=99;
		SetMotorX(motor,2,speed);
	} 
}
 #endif
#endif

#ifdef _SETMOTORFREQ_
 #ifndef  _SETMOTORFREQ_EXISTS_
 #define _SETMOTORFREQ_EXISTS_

void SetMotorFreq(u16 m_Freq)
{
	SetPwmFreq(m_Freq);
}
 #endif
#endif

#ifdef _SETMOTORPOWER_
 #ifndef _SETMOTORPOWER_EXISTS_
 #define _SETMOTORPOWER_EXISTS_

void SetMotorPower(u8 m_Per1,u8 m_Per2,u8 m_Per3,u8 m_Per4)//调节输出马达功率
{
	g_MotorPowerFlag=1;
	g_M1SpeedPer=m_Per1;//M1
	g_M2SpeedPer=m_Per2;//M2
	g_M3SpeedPer=m_Per3;//M3
	g_M4SpeedPer=m_Per4;//M4
}	
 #endif
#endif

#ifdef _SETMOTOR_CODE_
 #ifndef  _SETMOTOR_CODE_EXISTS_
 #define _SETMOTOR_CODE_EXISTS_
 
  void SetMotor_Code(u8 motor,u8 state,u8 speed)
  {
	if(speed>99)speed=99;
	if(motor==1)
	{
		MotorCodeM1M2_Init();
		if(g_MotorPowerFlag)	speed=g_M1SpeedPer*speed/100;
	}
	else
	{
		MotorCodeM3M4_Init();
		if(g_MotorPowerFlag)	speed=g_M2SpeedPer*speed/100;
	}

	SetMotorY(motor+4,state,speed); //motor12为5，motor34为6
  }
 #endif
#endif

#ifdef _SETMOTORCODE0_
#ifndef _SETMOTORCODE0_EXISTS_
#define _SETMOTORCODE0_EXISTS_

void SetMotorCode0(u8 motor)
{
	if(motor==1)
	{
		MotorCodeM1M2_Init();
		SetMotorCnt12Zero();
	}
	else
	{
		MotorCodeM3M4_Init();
		SetMotorCnt34Zero();
	}
}

 #endif
#endif

#ifdef _GETMOTORCODE_
#ifndef _GETMOTORCODE_EXISTS_
#define _GETMOTORCODE_EXISTS_

vs32 GetMotorCode(u8 motor)
{
     vs32 value;
     if(motor==1)
	{
		MotorCodeM1M2_Init();
		value = GetMotorCnt12();
	}
     else
	{
		MotorCodeM3M4_Init();
		value = GetMotorCnt34();
	}
	return value;
}
 #endif
#endif

#ifdef _SETMOTORSERVO_
#ifndef _SETMOTORSERVO_EXISTS_
#define _SETMOTORSERVO_EXISTS_

void SetMotorServo(u8 motor,u8 dir,u8 speed,u32 pulse)
{
  if(motor==1)
  {
	MotorCodeM1M2_Init();
	SetMotorServoMode(5);
	if(g_MotorPowerFlag)	speed=g_M1SpeedPer*speed/100;
  }
  else
  {
	MotorCodeM3M4_Init();
	SetMotorServoMode(6);
	if(g_MotorPowerFlag)	speed=g_M2SpeedPer*speed/100;
  }
  SetCodeServoAngle(motor+4,dir,speed,pulse);//motor12为5，motor34为6
}
 #endif
#endif

#ifdef _SETWAITFORANGLE_
#ifndef _SETWAITFORANGLE_EXISTS_
#define _SETWAITFORANGLE_EXISTS_ 

#include "LCD220176.h"
void SetWaitForAngle(u8 motor,u8 dir,u8 speed,u32 pulse)
{
  int m_CV;
  if(motor==1)
  {
	MotorCodeM1M2_Init();
	SetMotorServoMode(5);
	if(g_MotorPowerFlag)	speed=g_M1SpeedPer*speed/100;
  }
  else
  { 
	MotorCodeM3M4_Init();
	SetMotorServoMode(6);
	if(g_MotorPowerFlag)	speed=g_M2SpeedPer*speed/100;
  }//初始化
  SetCodeServoAngle(motor+4,dir,speed,pulse);//motor12为5，motor34为6

  do
  {
		switch(motor)
		{
			case 1 :m_CV = GetMotorCnt12();	break;
			case 2 :m_CV = GetMotorCnt34();	break;
		}
		if(m_CV>=0)
		{
			if(m_CV>(pulse-3))break;
		} 
		else
		{
			if((0-m_CV)>(pulse-3))break;
		}
  }while(1);

}
 #endif
#endif

//==SetServo Readding ID:  == DON'T DELETE!! ==

#ifdef _SETSERVO_
 #ifndef  _SETSERVO_EXISTS_
  #define _SETSERVO_EXISTS_
  
  #ifndef _SERVO_
   #define _SERVO_ u32
  #endif

  void SetServo(_SERVO_ which,u8 angle){
    u16 temp;
    struct select *information=&which;
    u8 bit1=information->bit1;
	if((which==384)||(which==256)||(which==128)||(which==0))bit1+=7;//A1-A4
    ComServoInit(bit1);
	if(angle==220)ComServoAngle(bit1,0);//掉电不保持
	else ComServoAngle(bit1,(angle+50));
  }
 #endif
#endif

//==SetAIServo Readding ID:  == DON'T DELETE!! ==

#ifdef _SETAISERVO_
 #ifndef  _SETAISERVO_EXISTS_
  #define _SETAISERVO_EXISTS_
  
  void SetAIServo(u8 ID,u16 angle,u8 speed)
  {
     	AIServoCMD[2]=ID;
	AIServoCMD[4]=angle/256;
	AIServoCMD[5]=angle%256;
	AIServoCMD[7]=speed;
	AIServoCMD[8]=AIServoCMD[2]+AIServoCMD[3]+AIServoCMD[4]+AIServoCMD[5]+AIServoCMD[7];
	AIServo_SendCMD(AIServoCMD);
  }
 #endif
#endif

//==SetAIMotor Readding ID:  == DON'T DELETE!! ==

#ifdef _SETAIMOTOR_
 #ifndef  _SETAIMOTOR_EXISTS_
  #define _SETAIMOTOR_EXISTS_
  
  void SetAIMotor(u8 ID,u8 dir,u8 speed)
  {
	AIMotorCMD[2]=ID;
	AIMotorCMD[4]=dir;
	AIMotorCMD[5]=speed;
	AIMotorCMD[8]=AIMotorCMD[2]+AIMotorCMD[3]+AIMotorCMD[4]+AIMotorCMD[5];
        AIServo_SendCMD(AIMotorCMD);
  }
 #endif
#endif

//==SetAICode Readding ID:  == DON'T DELETE!! ==

#ifdef _SETAICODE_
 #ifndef  _SETAICODE_EXISTS_
  #define _SETAICODE_EXISTS_
  
  void SetAICode(u8 ID,u8 dir,u8 speed,u8 cicle,u8 M_round)
  {
	AICodeCMD[2]=ID;
	AICodeCMD[4]=dir;
	AICodeCMD[5]=speed;
	AICodeCMD[6]=cicle;
	AICodeCMD[7]=M_round;
	AICodeCMD[8]=AICodeCMD[2]+AICodeCMD[3]+AICodeCMD[4]+AICodeCMD[5]+AICodeCMD[6]+AICodeCMD[7];
        AIServo_SendCMD(AICodeCMD);
  }
 #endif
#endif
//==SetAIPowerDown Readding ID:  == DON'T DELETE!! ==

#ifdef _SETAIPOWERDOWN_
 #ifndef  _SETAIPOWERDOWN_EXISTS_
  #define _SETAIPOWERDOWN_EXISTS_
  
void SetAIPowerDown(u8 ID)//掉电不保持20131023
  {
    AIWriteCMD[2]=ID;
	AIWriteCMD[3]=0x05;
	AIWriteCMD[4]=0;
	AIWriteCMD[5]=0;
	AIWriteCMD[6]=0;
	AIWriteCMD[7]=0;
	AIWriteCMD[8]=AIWriteCMD[2]+AIWriteCMD[3]+AIWriteCMD[4]+AIWriteCMD[5]+AIWriteCMD[6]+AIWriteCMD[7];
	AIServo_SendCMD(AIWriteCMD);
  }
 #endif
#endif
//==SetAIPowerDown Readding ID:  == DON'T DELETE!! ==

#ifdef _GETAISERVO_
 #ifndef  _GETAISERVO_EXISTS_
  #define _GETAISERVO_EXISTS_
  //1~17
/*
1当前位置 1
2当前温度 2
3速度档位 3
4--
5--
6伺服ID   4=6-2
7角度最大值 5
8角度最小值 6
9输入电压最大值 7
10输入电压最小值 8
11角度偏差方向 9
12角度偏差值   10
13--
14校验和开关状态 11=14-3
15内部温度最大值 12
16伺服被使用次数 13/*/
u16 GetAIServo(u8 ID,u8 command)//回读20131023
{
	u8 i;
	u8 buflist[7];
	u16 sum=0;
	if(command==0||command>13)return 9999;
	if(command>3&&command<11)command+=2;
	else if(command>=11)command+=3;
    AIWriteCMD[2]=ID;
	AIWriteCMD[3]=command+0x23;
	AIWriteCMD[4]=0;
	AIWriteCMD[5]=0;
	AIWriteCMD[6]=0;
	AIWriteCMD[7]=0;
	AIWriteCMD[8]=AIWriteCMD[2]+AIWriteCMD[3];
	AIServo_SendCMD(AIWriteCMD);
	Servo_EnableRx();
	for(i=0;i<7;i++)
	{
		while(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET);
		buflist[i]=USART_ReceiveData(UART4);
	}
	Servo_DisableRx();
	if(buflist[0]==AIWriteCMD[0]&&buflist[1]==AIWriteCMD[1])//字头
	{
		sum=buflist[2]+buflist[3]+buflist[4]+buflist[5];
		if(sum==buflist[6]&&buflist[2]==ID&&buflist[3]==0x0d)
		{
			return(((u16)buflist[4]<<8)|buflist[5]);
		}		
	}
	return 9999;
 }
 #endif
#endif
//==SetMusicAddData Readding ID:  == DON'T DELETE!! ==

#ifdef _SETMUSICADDDATA_
 #ifndef  _MUSICADDDATA_EXISTS_
  #define _MUSICADDDATA_EXISTS_
  
  void SetMusicAddData(u8 mdata,u8 time){
   Music_AddData(mdata,time);
  }
 #endif
#endif

//==SetMusicAddtreble Readding ID:  == DON'T DELETE!! ==

#ifdef _SETMUSICADDTREBLE_
 #ifndef  _SETMUSICADDTREBLE_EXISTS_
  #define _SETMUSICADDTREBLE_EXISTS_
  

  void SetMusicAddtreble(u8 mdata,u8 time){
   Music_AddData((14+mdata),time);
  }
 #endif
#endif

//==SetMusicAddalto Readding ID:  == DON'T DELETE!! ==

#ifdef _SETMUSICADDALTO_
 #ifndef  _MUSICADDALTO_EXISTS_
  #define _MUSICADDALTO_EXISTS_
  

  void SetMusicAddalto(u8 mdata,u8 time){
   Music_AddData((7+mdata),time);
  }
 #endif
#endif

//==SetMusicAddbass Readding ID:  == DON'T DELETE!! ==

#ifdef _SETMUSICADDBASS_
 #ifndef  _MUSICADDBASS_EXISTS_
  #define _MUSICADDBASS_EXISTS_
  

void SetMusicAddbass(u8 mdata,u8 time){
   Music_AddData(mdata,time);
  }
 #endif
#endif

//==SetMusicStop Readding ID:  == DON'T DELETE!! ==

#ifdef _SETMUSICSTOP_
 #ifndef  _SETMUSICSTOP_EXISTS_
  #define _SETMUSICSTOP_EXISTS_
  

void SetMusicStop(u8 time){
   Music_AddData(0,time);
  }
 #endif
#endif

//==SetMusicRepeat Readding ID:  == DON'T DELETE!! ==

#ifdef _SETMUSICREPEAT_
 #ifndef  _SETMUSICREPEAT_EXISTS_
  #define _SETMUSICREPEAT_EXISTS_
  

  void SetMusicRepeat(u8 c)
 {
  Music_Repeat(c);
  }
 #endif
#endif

//==SetMusicClear Readding ID:  == DON'T DELETE!! ==

#ifdef _SETMUSICCLEAR_
 #ifndef  _SETMUSICCLEAR_EXISTS_
  #define _SETMUSICCLEAR_EXISTS_
  

  void SetMusicClear(void){
  Music_DataClear();
  }
 #endif
#endif

//==SetMusicPlay Readding ID:  == DON'T DELETE!! ==

#ifdef _SETMUSICPLAY_
 #ifndef  _MUSICPLAY_EXISTS_
  #define _MUSICPLAY_EXISTS_
  

  void SetMusicPlay(void)
  {
   Music_Play();
  }
 #endif
#endif

//==GetMusicState Readding ID:  == DON'T DELETE!! ==

#ifdef   _GETMUSICSTATE_
#ifndef  _GETMUSICSTATE_EXISTS_
#define  _GETMUSICSTATE_EXISTS_


u8 GetMusicState(void)
  {
   return Music_GetEndState();
  }
 #endif
#endif

//==GetSysTime Readding ID:  == DON'T DELETE!! ==

#ifdef _GETSYSTIME_
 #ifndef  _GETSYSTIME_EXISTS_
  #define _GETSYSTIME_EXISTS_
  u32 GetSysTime(void){
  return GetSystemTime()/10;
  }
 #endif
#endif

#ifdef _GETSYSTIMEMS_
 #ifndef  _GETSYSTIMEMS_EXISTS_
  #define _GETSYSTIMEMS_EXISTS_
  u32 GetSysTimeMs(void){
  return GetSystemTime();
  }
 #endif
#endif

//==SetSysTime Readding ID:  == DON'T DELETE!! ==

#ifdef _SETSYSTIME_
 #ifndef  _SETSYSTIME_EXISTS_
  #define _SETSYSTIME_EXISTS_
  void SetSysTime(void)
  {
    SetSystemTime();
  }
 #endif
#endif

//==GetCompoI Readding ID:  == DON'T DELETE!! ==

#ifdef _GETCOMPOI_
 #ifndef  _GETCOMPOI_EXISTS_
  #define _GETCOMPOI_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _COMPOUNDEYE_
   #define _COMPOUNDEYE_ u32
  #endif

  u8 GetCompoI(_COMPOUNDEYE_ which, u8 command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[12];
    unsigned char k;
    Soft_I2C_Start();
    Soft_I2C_Write(0x07);
    for(k=0;k<11;k++){
      data[k]=Soft_I2C_Read(0);
    }
    data[11]=Soft_I2C_Read(1);
    Soft_I2C_Stop();
    return data[command-1];
  }
 #endif
#endif

//==GetDBCompoI2 Readding ID:  == DON'T DELETE!! ==

#ifdef _GETCOMPOI2_
 #ifndef  _GETCOMPOI2_EXISTS_
  #define _GETCOMPOI2_EXISTS_
  
  #include "I2C_Soft.h"

  #ifndef _COMPOUNDEYE2_
   #define _COMPOUNDEYE2_ unsigned long
  #endif

  unsigned char GetCompoI2(_COMPOUNDEYE2_ which, unsigned char command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[12];
    unsigned char k;
    unsigned char ack=1;

     if(command==255)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x10);
    ack &=Soft_I2C_Write(command);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x11);  
    for(k=0;k<11;k++){
      data[k]=Soft_I2C_Read(0);
    }
    data[12]=Soft_I2C_Read(1);
    Soft_I2C_Stop();  
    }
 if(command<13)
    {
      Soft_I2C_Start();
      ack &=Soft_I2C_Write(0x10);
      ack &=Soft_I2C_Write(command-1);
      Soft_I2C_Stop();
      Soft_I2C_Start();
      Soft_I2C_Write(0x11);     
      data[0]=Soft_I2C_Read(1);
      Soft_I2C_Stop(); 
      if(data[0]==255)
       {
        Soft_I2C_Start();
        Soft_I2C_Write(0x07);
        for(k=0;k<11;k++){
        data[k]=Soft_I2C_Read(0);
       }
      data[11]=Soft_I2C_Read(1);
      Soft_I2C_Stop();
      return data[command-1];
    }
    return data[0];
    }
  }
 #endif
#endif

#ifdef _GETCOMPOI3_
 #ifndef  _GETCOMPOI3_EXISTS_
  #define _GETCOMPOI3_EXISTS_
  
  #include "I2C_Soft.h"

  #ifndef _COMPOUNDEYE3_
   #define _COMPOUNDEYE3_ unsigned long
  #endif

  unsigned char GetCompoI3(_COMPOUNDEYE3_ which, unsigned char command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
	
    unsigned char m_temp,m_fix;
    if(command<=15)
    {
    	if( command <= 7)
	{
	  switch(command)
	  {
	  case 1:m_fix = 4;
	  break;
	  case 2:m_fix = 3;
	  break;
	  case 3:m_fix = 2;
	  break;
	  case 4:m_fix = 1;
	  break;
	  case 5:m_fix = 7;
	  break;
	  case 6:m_fix = 6;
	  break;
	  case 7:m_fix = 5;
	  break;
	  }
	}
	else
	{
	m_fix = command;
	}

    Soft_I2C_Start();
    Soft_I2C_Write(0x02);
    Soft_I2C_Write(m_fix);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x03);     
    m_temp=Soft_I2C_Read(1);
    Soft_I2C_Stop(); 
    }
    if(m_fix == 8)
     {
     if(m_temp==255)return 255;
     return (8-m_temp);
     }
    else
     {
     return m_temp;
     }  
  }
 #endif
#endif

#ifdef _GETCOMPOI16_
 #ifndef  _GETCOMPOI16_EXISTS_
  #define _GETCOMPOI16_EXISTS_
  
  #include "I2C_Soft.h"

  #ifndef _COMPOUNDEYE16_
   #define _COMPOUNDEYE16_ unsigned long
  #endif

  unsigned int GetCompoI16(_COMPOUNDEYE16_ which, unsigned char command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[2];
    unsigned char ack=1;
    unsigned int value;
      Soft_I2C_Start();
      ack &=Soft_I2C_Write(0x10);
      ack &=Soft_I2C_Write(command-1);
      Soft_I2C_Stop();
      Soft_I2C_Start();
      Soft_I2C_Write(0x11);     
      data[0]=Soft_I2C_Read(0);
      data[1]=Soft_I2C_Read(1);
      Soft_I2C_Stop();
      value = data[0]*256+data[1];
      return value;
  }
 #endif
#endif

//==GetUltrasound (adr=04)Readding ID:  == DON'T DELETE!! ==

#ifdef _GETULTRASOUND_
 #ifndef  _GETULTRASOUND_EXISTS_
  #define _GETULTRASOUND_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _ULTRASOUND_
   #define _ULTRASOUND_ unsigned long
  #endif

  u16 GetUltrasound(_ULTRASOUND_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char dislow;
    unsigned char dishigh;
    unsigned int distance;
    Soft_I2C_Start();
    Soft_I2C_Write(0x08);
    Soft_I2C_Write(0x01);
    Soft_I2C_Start();
    Soft_I2C_Write(0x09);
    dishigh=Soft_I2C_Read(0);
    dislow=Soft_I2C_Read(1);
    Soft_I2C_Stop();
    if(dishigh==0)
     {distance=dislow;}
    else if(dishigh==1)
   { distance=256+dislow;}
   else if(dishigh==2)
    {distance=888;}
   else
   {distance=999;}
    return distance;
  }
 #endif
#endif

#ifdef _GETADULTRASOUND_
 #ifndef  _GETADULTRASOUND_EXISTS_
  #define _GETADULTRASOUND_EXISTS_
  
  #ifndef _ADULTRASOUND_
   #define _ADULTRASOUND_ unsigned long
  #endif

  u16 GetAdUltrasound(_ADULTRASOUND_ which)
{
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
    u16 i,j,n;
	u32 s=0;
    u8 channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
   
    return i;
  }
 #endif
#endif


//==GETWIRELESS REC ==
#ifdef _GETWIRELESS_
 #ifndef  _GETWIRELESS_EXISTS_
  #define _GETWIRELESS_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _WIRELESS_
   #define _WIRELESS_ u32
  #endif

  u16 GetWireless(_WIRELESS_ which){
   struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned int wiredata;
    unsigned char wiredatalow;
    unsigned char wiredatahigh;
    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    wiredatahigh=Soft_I2C_Read(0);
    wiredatalow=Soft_I2C_Read(1);
    Soft_I2C_Stop();
    if(wiredatahigh==0)
    {wiredata=wiredatalow;}
    else if(wiredatahigh==1)
    {wiredata=888;}
    else{wiredata=999;}
    return wiredata;

  }
 #endif
#endif

//==SetWIRELESS SEND ==
#ifdef _SETWIRELESS_
 #ifndef  _SETWIRELESS_EXISTS_
  #define _SETWIRELESS_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _WIRELESS_
   #define _WIRELESS_ u32
  #endif

  u8 SetWireless(_WIRELESS_ which,u8 wdata){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char ack=1;
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0a);
    ack &=Soft_I2C_Write(wdata);
    Soft_I2C_Stop();
    delayms(200);
    return ack;

  }
 #endif
#endif

//==GetADextend Readding adr:07  == DON'T DELETE!! ==

#ifdef _GETADEXTEND_
 #ifndef  _GETADEXTEND_EXISTS_
  #define _GETADEXTEND_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _ADEXTEND_
   #define _ADEXTEND_ u32
  #endif

  u8 GetADextend(_ADEXTEND_ which, u8 command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[13];
    unsigned char k;
    unsigned char ack=1;

    if(command==255)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(command);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x0f);  
    for(k=0;k<12;k++){
      data[k]=Soft_I2C_Read(0);
    }
    data[12]=Soft_I2C_Read(1);
    Soft_I2C_Stop();  
    }
 if(command<14)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(command-1);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x0f);     
    data[0]=Soft_I2C_Read(1);
    Soft_I2C_Stop(); 
   if ((command==9)||(command==11))
   {
    data[0]++;
   }  
    return data[0];
    }
  }
 #endif
#endif

//==calendar Readding adr:07  == DON'T DELETE!! ==

#ifdef _GETCALENDAR_
 #ifndef  _GETCALENDAR_EXISTS_
  #define _GETCALENDAR_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _CALENDAR_
   #define _CALENDAR_ u32
  #endif

  u8 GetCalendar(_CALENDAR_ which, u8 command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data;
    unsigned char temph,templ;
    unsigned char ack=1;    
 if((command>=30)&&(command<=41))
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(command);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x0f);     
    data=Soft_I2C_Read(1);
    Soft_I2C_Stop(); 
    if(command<37)
    {
     templ=data;
     temph=data;
     templ=templ&0x0f;       
     temph=temph>>4;
     data=temph*10+templ;
    }
    return data;
    }
 else
   {
    return 888;
   }
  }
 #endif
#endif

//==calendar write adr:07  == DON'T DELETE!! ==

#ifdef _SETCALENDAR_
 #ifndef  _SETCALENDAR_EXISTS_
  #define _SETCALENDAR_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _CALENDAR_
   #define _CALENDAR_ unsigned long
  #endif

 void SetCalendar(_CALENDAR_ which, unsigned char sec,unsigned char min,unsigned char hour,unsigned char date,unsigned char month,unsigned char year)
  {
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    unsigned char ack=1; 
    unsigned char buf[4];
    unsigned long temp;
    unsigned int temp1;
    
 //if(command==49)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(49);    //COMMAND=49
    ack &=Soft_I2C_Write(year);    
    ack &=Soft_I2C_Write(month);
    ack &=Soft_I2C_Write(date);
    ack &=Soft_I2C_Write(hour); 
    ack &=Soft_I2C_Write(min);
    ack &=Soft_I2C_Write(sec);     
    Soft_I2C_Stop();
    } 
 }
 #endif
#endif

//== write calendaradr lcd:07  == DON'T DELETE!! ==

#ifdef _SETBE2560LCD1_
 #ifndef  _SETBE2560LCD1_EXISTS_
  #define _SETBE2560LCD1_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _CALENDAR_
   #define _CALENDAR_ unsigned long
  #endif

 void SetBE2560LCD1(_CALENDAR_ which, unsigned char command,unsigned char lx,unsigned char lxdchar)
  {
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    unsigned char ack=1;
    unsigned char led;
 
if(command==50)
    {
   
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(command);  
    ack &=Soft_I2C_Write(lx);   
    ack &=Soft_I2C_Write(lxdchar); 
    Soft_I2C_Stop();
    }

if(command==54)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(command); 
    Soft_I2C_Stop();
    }
if(command==55)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(command);    
    ack &=Soft_I2C_Write(lx); 
    Soft_I2C_Stop();
    }
 }

 #endif
#endif

//== write calendaradr lcd:07  == DON'T DELETE!! ==

#ifdef _SETBE2560BACK_
 #ifndef  _SETBE2560BACK_EXISTS_
  #define _SETBE2560BACK_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _CALENDAR_
   #define _CALENDAR_ unsigned long
  #endif

 void SetBE2560Back(_CALENDAR_ which, unsigned char led)
  {
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    unsigned char ack=1;
    
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(53);    
    ack &=Soft_I2C_Write(led); 
    Soft_I2C_Stop();
    
 }

 #endif
#endif

//== write calendaradr lcd:07  == DON'T DELETE!! ==

#ifdef _SETBE2560LCD3_
 #ifndef  _SETBE2560LCD3_EXISTS_
  #define _SETBE2560LCD3_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _CALENDAR_
   #define _CALENDAR_ unsigned long
  #endif

 void SetBE2560LCD3(_CALENDAR_ which, unsigned char lx,unsigned int lxdint)
  {
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    unsigned char ack=1; 
    unsigned char buf[2];
    unsigned int temp1;

    temp1=lxdint;
    buf[0]=(unsigned char)temp1;
    temp1=lxdint;  
    temp1=temp1>>8;
    buf[1]=(unsigned char)temp1;
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(51);
    ack &=Soft_I2C_Write(lx);     
    ack &=Soft_I2C_Write(buf[0]); 
    ack &=Soft_I2C_Write(buf[1]); 
    Soft_I2C_Stop();
  
 }

 #endif
#endif

//== write calendaradr lcd:07  == DON'T DELETE!! ==

#ifdef _SETBE2560LCD8_
 #ifndef  _SETBE2560LCD8_EXISTS_
  #define _SETBE2560LCD8_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _CALENDAR_
   #define _CALENDAR_ unsigned long
  #endif

 void SetBE2560LCD8(_CALENDAR_ which, unsigned char lx,unsigned long lxdlong)
  {
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    unsigned char ack=1; 
    unsigned char buf[4];
    unsigned long temp1;

    temp1=lxdlong;
    buf[0]=(unsigned char)temp1;

    temp1=lxdlong;  
    temp1=temp1>>8;
    buf[1]=(unsigned char)temp1;

    temp1=lxdlong;
    temp1=temp1>>16;
    buf[2]=(unsigned char)temp1;

    temp1=lxdlong;  
    temp1=temp1>>24;
    buf[3]=(unsigned char)temp1;
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(52);
    ack &=Soft_I2C_Write(lx);     
    ack &=Soft_I2C_Write(buf[0]); 
    ack &=Soft_I2C_Write(buf[1]); 
    ack &=Soft_I2C_Write(buf[2]); 
    ack &=Soft_I2C_Write(buf[3]); 
    Soft_I2C_Stop();
  
 }

 #endif
#endif

//== set calendaradr speaker:07  == DON'T DELETE!! ==

#ifdef _SETBE2560SPK_
 #ifndef  _SETBE2560SPK_EXISTS_
  #define _SETBE2560SPK_EXISTS_
  
  #include "I2C_Soft.h"

  #ifndef _CALENDAR_
   #define _CALENDAR_ unsigned long
  #endif

 void SetBE2560spk(_CALENDAR_ which, unsigned char time,unsigned int freq)
  {
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    unsigned char ack=1; 
    unsigned char buf[2];
    unsigned int temp1;
    
    temp1=freq;
    buf[0]=(unsigned char)temp1;
    temp1=freq;  
    temp1=temp1>>8;
    buf[1]=(unsigned char)temp1;
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
    ack &=Soft_I2C_Write(56);
    ack &=Soft_I2C_Write(time);     
    ack &=Soft_I2C_Write(buf[0]); 
    ack &=Soft_I2C_Write(buf[1]); 
    Soft_I2C_Stop();
  
 }

 #endif
#endif

#ifdef _GETRFIDLASTDATA_
 #ifndef _GETRFIDLASTDATA_EXISTS_
  #define _GETRFIDLASTDATA_EXISTS_
  
  #include "I2C_Soft.h"
   #ifndef _RFID_
    #define _RFID_ unsigned long
   #endif

   unsigned int GetRFIDlastdata(_RFID_ which){
    unsigned int wiredata;
    unsigned int ri,rt;
    unsigned char v;
    unsigned char wiredatalow;
    unsigned char wiredatahigh;
    
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    Soft_I2C_Start();
    Soft_I2C_Write(0x0a);
    Soft_I2C_Write(0x0d); 
    Soft_I2C_Write(0);
    Soft_I2C_Stop();
    for(rt=0;rt<300;rt++);
    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    wiredatalow=Soft_I2C_Read(0);
    wiredatahigh=Soft_I2C_Read(0);
    v=Soft_I2C_Read(1);
    Soft_I2C_Stop();
    if(v==0)
      wiredata=(unsigned int)(wiredatalow*256);
    wiredata+=wiredatahigh;
    if(v==1||v==255)
      wiredata=999;
    if(v==2)
      wiredata=888;
    return wiredata;
   }
 #endif
#endif

#ifdef _SETRFIDADDRESS_
 #ifndef _SETRFIDADDRESS_EXISTS_
  #define _SETRFIDADDRESS_EXISTS_
  
  #include "I2C_Soft.h"
   #ifndef _RFID_
    #define _RFID_ unsigned long
   #endif

  unsigned char SetRFIDAddress(_RFID_ which, unsigned int Address){
    unsigned char wiredata;
    unsigned char wiredatalow;
    unsigned char wiredatahigh;
    unsigned char v1,v2,v;
    unsigned int ri,rt;
    
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    v1=(unsigned char)(Address/256);
    v2=(unsigned char)(Address%256);
    
    Soft_I2C_Start();
    Soft_I2C_Write(0x0a);
    Soft_I2C_Write(0x0e); 
    Soft_I2C_Write(v1); 
    Soft_I2C_Write(v2); 
    Soft_I2C_Stop();
    
    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    wiredatalow=Soft_I2C_Read(0);
    wiredatahigh=Soft_I2C_Read(0);
    v=Soft_I2C_Read(1);
    Soft_I2C_Stop();
    
   //wiredata=(unsigned int)(wiredatahigh*256);
    //wiredata+=wiredatalow;
    if(v==255||v==1||v==2)
    wiredata=0;
    else wiredata=1;
    
    return wiredata;
   }
 #endif
#endif

#ifdef _SETRFIDDATA_
 #ifndef _SETRFIDDATA_EXISTS_
  #define _SETRFIDDATA_EXISTS_
  
  #include "I2C_Soft.h"
   #ifndef _RFID_
    #define _RFID_ unsigned long
   #endif
  unsigned char SetRFIDData(_RFID_ which, unsigned char setdata, unsigned int Address){
    unsigned long wiredata;	
    unsigned int ri,rt;
    unsigned char wiredatalow;
    unsigned char wiredatahigh;
    struct select *information=&which;
    unsigned char v1,v2,v;	

   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    v1=(unsigned char)(Address/256);
    v2=(unsigned char)(Address%256); 
    Soft_I2C_Start();
    Soft_I2C_Write(0x0a);
    Soft_I2C_Write(0x0B); 
    Soft_I2C_Write(v1); 
    Soft_I2C_Write(v2); 
    Soft_I2C_Stop();   
    Soft_I2C_Start();
    Soft_I2C_Write(0x0A);
    Soft_I2C_Write(0x0A); 
    Soft_I2C_Write(setdata);
    Soft_I2C_Write(0);
    Soft_I2C_Stop();
    for( ri=0; ri<3000; ri++ )
    for(rt=0;rt<2000;rt++);
    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    wiredatalow=Soft_I2C_Read(0);
    wiredatahigh=Soft_I2C_Read(0);
    v=Soft_I2C_Read(1);
    Soft_I2C_Stop();
    if(v==0)
    v1=1;
    if(v==1||v==255)
    v1=0;
    if(v==2)
    v1=0;
    return v1;    
   }
 #endif
#endif

#ifdef _GETRFIDDATA_
 #ifndef _GETRFIDDATA_EXISTS_
  #define _GETRFIDDATA_EXISTS_
  
  #include "I2C_Soft.h"
   #ifndef _RFID_
    #define _RFID_ unsigned long
   #endif
    unsigned int GetRFIDData(_RFID_ which, unsigned int Address){
    unsigned int ri,rt;
    unsigned int wiredata;
    unsigned char wiredatalow;
    unsigned char wiredatahigh;
    unsigned char v,v1,v2;
    
    struct select *information=&which;

   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    v1=(unsigned char)(Address/256);
    v2=(unsigned char)(Address%256);
    
    Soft_I2C_Start();
    Soft_I2C_Write(0x0a);
    Soft_I2C_Write(0x0B); 
    Soft_I2C_Write(v1); 
    Soft_I2C_Write(v2); 
    Soft_I2C_Stop();
 

    Soft_I2C_Start();
    Soft_I2C_Write(0x0a);
    Soft_I2C_Write(0x0c); 
    Soft_I2C_Write(0);
    Soft_I2C_Stop();
    for( ri=0; ri<3000; ri++ )
    for(rt=0;rt<2000;rt++);
    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    wiredatalow=Soft_I2C_Read(0);
    wiredatahigh=Soft_I2C_Read(0);
    v=Soft_I2C_Read(1);
    Soft_I2C_Stop();
    wiredata=wiredatalow;
    if(v==1||v==255)
     wiredata=999;
    if(v==2)
     wiredata=888;
    
    return  wiredata;  
   }
 #endif
#endif


#ifdef _GETMP3NO_
 #ifndef _GETMP3NO_EXISTS_
  #define _GETMP3NO_EXISTS_
  
  #include "I2C_Soft.h"
  #include "Mp3.h"
   #ifndef _MP3_
    #define _MP3_ unsigned long
   #endif
   unsigned char GetMp3No(_MP3_ which){
    struct select *information=&which;

   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    DELAY();
    I2C_SPEED=50;
    send_command2(0x5f,0x01);
    get_data(6);	
    return g_cReceBuf[4];
    I2C_SPEED=30;
   }
 #endif
#endif

#ifdef _SETMP3NO_
 #ifndef _SETMP3NO_EXISTS_
  #define _SETMP3NO_EXISTS_
  
  #include "I2C_Soft.h"
  #include "Mp3.h"
   #ifndef _MP3_
    #define _MP3_ unsigned long
   #endif
   unsigned char SetMp3No(_MP3_ which, unsigned char status, unsigned char PlayNO){
struct select *information=&which;

   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char i,x,y,t,count;
    unsigned char td=0;
    I2C_SPEED=50;
    DELAY();
    send_command2(0x5f,0x01);
    get_data(6);
    DELAY();

    if(PlayNO>g_cReceBuf[4]&&status==1)
    {
        if(g_cReceBuf[4]==0)
        g_cReceBuf[4]++;
	count=PlayNO-g_cReceBuf[4];
	x=count/10;
	y=count%10;
	for(i=0;i<x;i++)
	{
		send_command4(0x55,0x05,0x00,0x00);
		DELAY();
	}
	for(i=0;i<y;i++)
	{	
		send_command4(0x55,0x01,0x00,0x00);
		DELAY();
	}	 	
    }

    if(PlayNO<g_cReceBuf[4]&&status==1)
    {
        if(g_cReceBuf[4]==0)
        g_cReceBuf[4]++;        
	count=g_cReceBuf[4]-PlayNO;
	x=count/10;
	y=count%10;
        if(count<=9)
        y=y+1;   
	for(i=0;i<x;i++)
	{
	 send_command4(0x55,0x06,0x00,0x00);
	 DELAY();
	}
	for(i=0;i<y;i++)
	{	
	 send_command4(0x55,0x02,0x00,0x00);
	 DELAY();
	}	 	
     }	
    if(status==1)
    play();
    if(status==0)
    stop();
    I2C_SPEED=30;
   }
 #endif
#endif

#ifdef _GETINFRARED_
 #ifndef  _GETINFRARED_EXISTS_
  #define _GETINFRARED_EXISTS_
  

  #ifndef _PYIFRARED_
   #define _PYIFRARED_ u32
  #endif

  u16 GetInfrared(_PYIFRARED_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    u16 i;
    u8 channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return (u16)i;
  }
 #endif
#endif

#ifdef _GETHUMIDITY_
 #ifndef  _GETHUMIDITY_EXISTS_
  #define _GETHUMIDITY_EXISTS_
  

  #ifndef _HUMIDITY_
   #define _HUMIDITY_ unsigned long
  #endif

  u16 GetHumidity(_HUMIDITY_ which){
    u16 i,j;
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
   u8 channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel)/4;
    j=i;
    i=GetAdcResult(channel)/4;
    if(i>j)
    j=i;
    i=GetAdcResult(channel)/4;  
    if(i>j)
    j=i;  
    i=GetAdcResult(channel)/4;  
    if(i>j)
    j=i;  
    j=j/6;
    return (u16)j;
  }
 #endif
#endif

//==GetSelector Readding ID:  == DON'T DELETE!! ==

#ifdef _GETSLOPE_
 #ifndef  _GETSLOPE_EXISTS_
  #define _GETSLOPE_EXISTS_
  

  #ifndef _SLOPE_
   #define _SLOPE_ unsigned long
  #endif

  unsigned char GetSlope(_SLOPE_ which){
    struct select *information=&which;
    
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
GPIO_Setting((GPIO_TypeDef*)port2,bit1,GPIO_Mode_AIN);

    u16 i,j;
    u8 value;
    u8 channel1,channel2;
channel1=GetAdcResult(information->group1,bit1);
channel2=GetAdcResult(information->group2,bit2);

     i=GetAdcResult(channel1);
     j=GetAdcResult(channel2);
     i=i/4;
     j=j/4;
	if(i==1023)value=4;
	else if(i==0)value=3;
	else if(j==1023)value=2;
	else if(j==0)value=1;
        else value=0;
    return (u8)value;
  }
 #endif
#endif

#ifdef _GETACCELERATION_
 #ifndef _GETACCELERATION_EXISTS_
  #define _GETACCELERATION_EXISTS_
  
  #include "I2C_Soft.h"
   #ifndef _ACCELERATION_
    #define _ACCELERATION_ u32
   #endif

    u8 GetAcceleration( _ACCELERATION_ which, u8 ACCDirection){
    unsigned int rt;
    unsigned char wiredatalow;
    unsigned char wiredatahigh;
    
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    Soft_I2C_Start();
    Soft_I2C_Write(0x70);
    Soft_I2C_Write(0x14);
    Soft_I2C_Write(0x80);
    Soft_I2C_Stop();

    Soft_I2C_Start();
    Soft_I2C_Write(0x70);
    Soft_I2C_Write(0x0a);
    Soft_I2C_Write(0x00);
    Soft_I2C_Stop();

    Soft_I2C_Start();
    Soft_I2C_Write(0x70);
    if(ACCDirection==1)
    Soft_I2C_Write(0x02);
    else if(ACCDirection==2)
    Soft_I2C_Write(0x04);
    else if(ACCDirection==3)
    Soft_I2C_Write(0x06);    
    Soft_I2C_Stop();
    for(rt=0;rt<2000;rt++);
    Soft_I2C_Start();
    Soft_I2C_Write(0x71);
    wiredatalow=Soft_I2C_Read(0);
    wiredatahigh=Soft_I2C_Read(1);

    if(wiredatahigh>=128)
    wiredatahigh=(~wiredatahigh)+129;
    else
    wiredatahigh=128-wiredatahigh;
    return  wiredatahigh;  
   }
 #endif
#endif

#ifdef _GETTRACE_
 #ifndef _GETTRACE_EXISTS_
  #define _GETTRACE_EXISTS_
  
  #include "I2C_Soft.h"
   #ifndef _TRACE_
    #define _TRACE_ u32
   #endif

    u8 GetTrace( _TRACE_ which, u8 command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data;
    unsigned char k;
    unsigned char ack=1;

 if(command<10)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x14);
    ack &=Soft_I2C_Write(command-1);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x15);     
    data=Soft_I2C_Read(1);
    Soft_I2C_Stop(); 

    return data;
 
   }
 else if(command<=20)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x14);
    ack &=Soft_I2C_Write(command-2);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x15);     
    data=Soft_I2C_Read(1);
    Soft_I2C_Stop(); 

    return data;
 
   }


}
 #endif
#endif


#ifdef _SETTRACEREF_
 #ifndef _SETTRACEREF_EXISTS_
  #define _SETTRACEREF_EXISTS_
  
  #include "I2C_Soft.h"

   #ifndef _TRACE_
    #define _TRACE_ unsigned long
   #endif

    void SetTraceRef( _TRACE_ which, unsigned char ch0,unsigned char ch1,unsigned char ch2,unsigned char ch3,unsigned char ch4,unsigned char ch5,unsigned char ch6,unsigned char ch7){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data;
    unsigned char k;
    unsigned char ack=1;
    
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x14);
    ack &=Soft_I2C_Write(0x33);
    ack &=Soft_I2C_Write(ch0);
    ack &=Soft_I2C_Write(ch1);
    ack &=Soft_I2C_Write(ch2);
    ack &=Soft_I2C_Write(ch3);
    ack &=Soft_I2C_Write(ch4);
    ack &=Soft_I2C_Write(ch5);
    ack &=Soft_I2C_Write(ch6);
    ack &=Soft_I2C_Write(ch7);
    Soft_I2C_Stop();
}
 #endif
#endif

#ifdef _SETBUZZER_
 #ifndef _SETBUZZER_EXISTS_
  #define _SETBUZZER_EXISTS_
  
  #include "I2C_Soft.h"
   #ifndef _TRACE_
    #define _TRACE_ unsigned long
   #endif

    void SetBuzzer( _TRACE_ which, unsigned char Ltime){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data;
    unsigned char k;
    unsigned char ack=1;

    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x14);
    ack &=Soft_I2C_Write(0x34);
    ack &=Soft_I2C_Write(Ltime);
    Soft_I2C_Stop();
}
 #endif
#endif

//==kick Readding ID:  == DON'T DELETE!! ==

#ifdef _KICKFOOTBALL_
 #ifndef  _KICKFOOTBALL_EXISTS_
  #define _KICKFOOTBALL_EXISTS_
  

  #ifndef _KICK_
   #define _KICK_ u32
  #endif

  void Kickfootball(_KICK_ which,unsigned char kick_num){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

  GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
  GPIO_Setting((GPIO_TypeDef*)port2,bit2,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
    if(kick_num==0){
    GPIO_SetBits((GPIO_TypeDef*)port1,(1<<bit1));
    GPIO_ResetBits((GPIO_TypeDef*)port2,( 1<<bit2));
    delayms(40);
   GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
   GPIO_ResetBits((GPIO_TypeDef*)port2,( 1<<bit2));
    }
    if(kick_num==1){
   GPIO_SetBits((GPIO_TypeDef*)port2,(1<<bit2));
   GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
   delayms(40);
   GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
   GPIO_ResetBits((GPIO_TypeDef*)port2,( 1<<bit2));

    }
    else{
      GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
      GPIO_ResetBits((GPIO_TypeDef*)port2,( 1<<bit2));

    }
  }
 #endif
#endif

//==Charge Readding ID:  == DON'T DELETE!! ==

#ifdef _CHARGE_
 #ifndef _CHARGE_EXISTS_
  #define _CHARGE_EXISTS_
  

  #ifndef _KICK_
   #define _KICK_ u32
  #endif

  void Charge(_KICK_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;
   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
   GPIO_Setting((GPIO_TypeDef*)port2,bit2,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);

   GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
   GPIO_ResetBits((GPIO_TypeDef*)port2,( 1<<bit2));
;
  }
 #endif
#endif


#ifdef _SETBEEP_
 #ifndef  _SETBEEP_EXISTS_
  #define _SETBEEP_EXISTS_
  #ifndef _BEEP_
  #define _BEEP_ u32
  #endif

  void SetBEEP(_BEEP_ which,unsigned char state){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
    if(state>0){
    GPIO_SetBits((GPIO_TypeDef*)port1,(1<<bit1));
        }
    else{
    GPIO_ResetBits((GPIO_TypeDef*)port1,( 1<<bit1));
    }
  }
 #endif
#endif

#ifdef _GETSMOKE_
 #ifndef  _GETSMOKE_EXISTS_
  #define _GETSMOKE_EXISTS_
 
  #ifndef _SMOKE_
   #define _SMOKE_ u32
  #endif

  u16 GetSmoke(_SMOKE_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);
    u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    if(value)
      return 1;
    else
      return 0;
  }
 #endif
#endif

#ifdef _GETSOUNDINT_
 #ifndef  _GETSOUNDINT_EXISTS_
  #define _GETSOUNDINT_EXISTS_
  

  #ifndef _SOUNDINT_
   #define _SOUNDINT_ 32
  #endif

  u16 GetSoundint(_SOUNDINT_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    u16 i;
    u8  channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return (u16)i;
  }
 #endif
#endif

//==GetIRDete Readding ID:  == DON'T DELETE!! ==

#ifdef _GETIRONE_
 #ifndef  _GETIRONE_EXISTS_
  #define _GETIRONE_EXISTS_
  

  #ifndef _IRONE_
   #define _IRONE_ u32
  #endif

  u8 GetIRone(_IRONE_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);
    u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    if(value)
      return 0;
    else
      return 1;
  }
 #endif
#endif

#ifdef _GETMAGNET_
 #ifndef  _GETMAGNET_EXISTS_
  #define _GETMAGNET_EXISTS_
  

  #ifndef _MAGNET_
   #define _MAGNET_ u32
  #endif

  unsigned char GetMagnet(_MAGNET_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);
   u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    if(value)
      return 0;
    else
      return 1;
  }
 #endif
#endif

#ifdef _GETVIB_
 #ifndef  _GETVIB_EXISTS_
  #define _GETVIB_EXISTS_
  

  #ifndef _VIB_
   #define _VIB_ u32
  #endif

  u8 GetVib(_VIB_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);
    u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    if(value)
      return 0;
    else
      return 1;
  }
 #endif
#endif

#ifdef _GETDOOR_
 #ifndef  _GETDOOR_EXISTS_
  #define _GETDOOR_EXISTS_
  #ifndef _DOOR_
   #define _DOOR_ unsigned long
  #endif

  u8 GetDoor(_DOOR_ which){
    struct select *information=&which;
    u32 port1=portarray[information->group1];
    u8 bit1=information->bit1;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);
    u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    if(value)
      return 0;
    else
      return 1;
  }
 #endif
#endif

#ifdef _GETCLOSE_
 #ifndef  _GETCLOSE_EXISTS_
  #define _GETCLOSE_EXISTS_
 
  #ifndef _CLOSE_
   #define _CLOSE_ unsigned long
  #endif

  u8 GetClose(_CLOSE_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u8 bit1=information->bit1;
   GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_IN,0,GPIO_PuPd_UP);

    u8 value=GPIO_ReadInputDataBit((GPIO_TypeDef*)port1,(1<<bit1));
    if(value)
      return 0;
    else
      return 1;
  }
 #endif
#endif

#ifdef _GETMICROTRACE_
 #ifndef _GETMICROTRACE_EXISTS_
  #define _GETMICROTRACE_EXISTS_
  
  #include "I2C_Soft.h"
   #ifndef _MICROTRACE_
    #define _MICROTRACE_ unsigned long
   #endif
    unsigned char GetMicroTrace( _MICROTRACE_ which, unsigned char command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data;
    unsigned char k;
    unsigned char ack=1;

 if(command<10)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x16);
    ack &=Soft_I2C_Write(command-1);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x17);     
    data=Soft_I2C_Read(1);
    Soft_I2C_Stop(); 

    return data;
 
   }
 else if(command<=20)
    {
    Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x16);
    ack &=Soft_I2C_Write(command-2);
    Soft_I2C_Stop();
    Soft_I2C_Start();
    Soft_I2C_Write(0x17);     
    data=Soft_I2C_Read(1);
    Soft_I2C_Stop(); 

    return data;
 
   }

}
 #endif
#endif
//==GetADextend Readding adr:07  == DON'T DELETE!! ==

#ifdef _GETADEXTEND14_
 #ifndef  _GETADEXTEND14_EXISTS_
  #define _GETADEXTEND14_EXISTS_
  #ifndef _ADEXTEND14_
   #define _ADEXTEND14_ unsigned long
  #endif
  #include "I2C_Soft.h"
  unsigned char GetADextend14(_ADEXTEND14_ which, unsigned char command){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[19];
    unsigned char k;
    unsigned char ack=1;
    
 if(command<20)
    {
     pic_iic=1;
     Soft_I2C_Start();
    ack &=Soft_I2C_Write(0x0e);
     ack &=Soft_I2C_Write(command);
    Soft_I2C_Stop();

    Soft_I2C_Start();
   Soft_I2C_Write(0x0f);   
   data[0]=Soft_I2C_Read(1);
   Soft_I2C_Stop();    
    return data[0];
    }
  pic_iic=0;
  }
 #endif
#endif

//==Getdata Readding eeprom ==

#ifdef _GETDATA_
 #ifndef  _GETDATA_EXISTS_
  #define _GETDATA_EXISTS_
  

u16 GetData(u8 dataadr){
  if((dataadr>0)&&(dataadr<=200))
  return ReadEEP(dataadr);
  else
  return 888;
}
 #endif
#endif

//==Setdata write data to eeprom ==

#ifdef _SETDATA_
 #ifndef  _SETDATA_EXISTS_
  #define _SETDATA_EXISTS_
  

void SetData(u8 dataadr,u16 datacode)
{
	if(datacode>4095)datacode=4095;
	if((dataadr>0)&&(dataadr<=200))
	WriteEEP(dataadr,datacode);
}
 #endif
#endif

#ifdef _GETDIGITALTEMPERATURE_
 #ifndef  _GETDIGITALTEMPERATURE_EXISTS_
  #define _GETDIGITALTEMPERATURE_EXISTS_
  
  #include <DS18B20.h>

  #ifndef _DIGITALTEMPERATURE_
   #define _DIGITALTEMPERATURE_ unsigned long
  #endif

  unsigned char GetDigitalTemperature(_DIGITALTEMPERATURE_ which){
    struct select *information=&which;
        u32 port1=portarray[information->group1];
        u8 bit1=information->bit1;
        Dtemp_Pin=bit1;
	Dtemp_port=port1;
        unsigned char tempL,tempH,wendu;
	unsigned int x;
	resetDS18B20();
	write_charDS18B20(0xcc); 	        //跳过ROM
	write_charDS18B20(0x44);		//启动温度转换
	delay1us(1);
	resetDS18B20();
	write_charDS18B20(0xcc);		//跳过ROM
	write_charDS18B20(0xbe);		//读数据
	tempL=read_charDS18B20();
	tempH=read_charDS18B20();
        tempH=tempH&0x07;
	tempL=tempL>>4;
	tempH=tempH<<4;
	wendu=tempH|tempL;
	return(wendu);
  }
 #endif
#endif

//==GetButton1 Readding ID:  == DON'T DELETE!! ==
#ifdef   _GETBUTTON1_
#ifndef  _GETBUTTON1_EXISTS_
#define _GETBUTTON1_EXISTS_

u8 GetButton1(void)
{  
 GPIO_Setting(GPIOE,15,GPIO_Mode_IN,0,GPIO_PuPd_UP);
 u8 value=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15);
    if(value)
      return 0;
    else
      return 1;

}
#endif
#endif

//==GetButton2 Readding ID:  == DON'T DELETE!! ==
#ifdef   _GETBUTTON2_
#ifndef  _GETBUTTON2_EXISTS_
#define _GETBUTTON2_EXISTS_
    
u8 GetButton2(void)
{
 GPIO_Setting(GPIOE,14,GPIO_Mode_IN,0,GPIO_PuPd_UP);
 u8 value=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14);
    if(value)
      return 0;
    else
      return 1;

}
#endif
#endif

//==GetButton3 Readding ID:  == DON'T DELETE!! ==
#ifdef   _GETBUTTON3_
#ifndef  _GETBUTTON3_EXISTS_
#define _GETBUTTON3_EXISTS_
    
u8 GetButton3(void)
{
 GPIO_Setting(GPIOE,13,GPIO_Mode_IN,0,GPIO_PuPd_UP);
 u8 value=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13);
    if(value)
      return 0;
    else
      return 1;

}
#endif
#endif


//==Get PS2==
#ifdef _GETPS2BUTTON_
 #ifndef  _GETPS2BUTTON_EXISTS_
  #define _GETPS2BUTTON_EXISTS_
  
  #include "I2C_Soft.h"

  #ifndef _PS2_
   #define _PS2_ unsigned long
  #endif

    unsigned int GetPS2Button(_PS2_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[6];
    unsigned int wdata;

    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    data[0] = Soft_I2C_Read(0);
    data[1] = Soft_I2C_Read(1);
    Soft_I2C_Stop();
    wdata = data[1]*256 + data[0];
    return wdata;
  }
 #endif
#endif

//==Get PS2==
#ifdef _GETPS2LEFTROCKER_
 #ifndef  _GETPS2LEFTROCKER_EXISTS_
  #define _GETPS2LEFTROCKER_EXISTS_
  
  #include "I2C_Soft.h"

  #ifndef _PS2_
   #define _PS2_ unsigned long
  #endif

    unsigned int GetPS2LeftRocker(_PS2_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[6];
    unsigned int wdata;

    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    data[0] = Soft_I2C_Read(0);
    data[1] = Soft_I2C_Read(0);
    data[2] = Soft_I2C_Read(0);
    data[3] = Soft_I2C_Read(0);
    data[4] = Soft_I2C_Read(0);
    data[5] = Soft_I2C_Read(1);
    Soft_I2C_Stop();
    wdata = data[5]*256 + data[4];
    return wdata;
  }
 #endif
#endif

//==Get PS2==
#ifdef _GETPS2RIGHTROCKER_
 #ifndef  _GETPS2RIGHTROCKER_EXISTS_
  #define _GETPS2RIGHTROCKER_EXISTS_
  
  #include "I2C_Soft.h"

  #ifndef _PS2_
   #define _PS2_ unsigned long
  #endif

    unsigned int GetPS2RightRocker(_PS2_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[6];
    unsigned int wdata;

    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    data[0] = Soft_I2C_Read(0);
    data[1] = Soft_I2C_Read(0);
    data[2] = Soft_I2C_Read(0);
    data[3] = Soft_I2C_Read(1);
    Soft_I2C_Stop();
    wdata = data[3]*256 + data[2];
    return wdata;
  }
 #endif
#endif

//==Get PS2==
#ifdef _GETPS2ALL_
 #ifndef  _GETPS2ALL_EXISTS_
  #define _GETPS2ALL_EXISTS_
  
  #include "I2C_Soft.h"

  #ifndef _PS2_
   #define _PS2_ unsigned long
  #endif

extern  unsigned char m_Btn1,m_Btn2,m_joy1_X,m_joy1_Y,m_joy2_X,m_joy2_Y;

void GetPS2All(_PS2_ which){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char data[6];
    Soft_I2C_Start();
    Soft_I2C_Write(0x0B);
    data[0] = Soft_I2C_Read(0);
    data[1] = Soft_I2C_Read(0);
    data[2] = Soft_I2C_Read(0);
    data[3] = Soft_I2C_Read(0);
    data[4] = Soft_I2C_Read(0);
    data[5] = Soft_I2C_Read(1);
    Soft_I2C_Stop();
    m_Btn1 = data[0];
    m_Btn2 = data[1];
    m_joy1_X = data[2];
    m_joy1_Y = data[3];
    m_joy2_X = data[4];
    m_joy2_Y = data[5];
  }
 #endif
#endif

  #ifdef _GETTRACEV2I2C_
  #ifndef _GETTRACEV2I2C_EXISTS_
  #define _GETTRACEV2I2C_EXISTS_
  
  #include "I2C_Soft.h"
  #ifndef _TRACEV2_
  #define _TRACEV2_ u32
  #endif

   u8 GetTraceV2I2C( _TRACEV2_ which, u8 command){
   struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

    unsigned char m_ChannelState;
    Soft_I2C_Start();
    Soft_I2C_Write(0x18);
    Soft_I2C_Write(command);
    Soft_I2C_Stop();
    
    Soft_I2C_Start();
    Soft_I2C_Write(0x19);
    m_ChannelState=Soft_I2C_Read(1);
    Soft_I2C_Stop();
    
    return m_ChannelState;
}
 #endif
#endif

  #ifdef  _SETTRACEV2COLOR_
  #ifndef _SETTRACEV2COLOR_EXISTS_
  #define _SETTRACEV2COLOR_EXISTS_
  
  #include "I2C_Soft.h"
  #ifndef _TRACEV2_
  #define _TRACEV2_ u32
  #endif

  void SetTraceV2Color(_TRACEV2_ which,u8 ch1,u8 ch2,u8 ch3,u8 ch4,u8 ch5,u8 ch6,u8 ch7){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
   
    Soft_I2C_Start();
    Soft_I2C_Write(0x18);
    Soft_I2C_Write(51);
    Soft_I2C_Write(ch1);
    Soft_I2C_Write(ch2);
    Soft_I2C_Write(ch3);
    Soft_I2C_Write(ch4);
    Soft_I2C_Write(ch5);
    Soft_I2C_Write(ch6);
    Soft_I2C_Write(ch7);
    Soft_I2C_Stop();
    }
    #endif
    #endif

  #ifdef  _SETTRACEV2BEEPI2C_
  #ifndef _SETTRACEV2BEEPI2C_EXISTS_
  #define _SETTRACEV2BEEPI2C_EXISTS_
  
  #include "I2C_Soft.h"
  #ifndef _TRACEV2_
  #define _TRACEV2_ u32
  #endif

   void SetTraceV2BeepI2C( _TRACEV2_ which,u8 beeptime){
   struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
   
    unsigned char m_ChannelState;
    Soft_I2C_Start();
    Soft_I2C_Write(0x18);
    Soft_I2C_Write(52);
    Soft_I2C_Stop();
    
    Soft_I2C_Start();
    Soft_I2C_Write(0x18);
    Soft_I2C_Write(beeptime);
    Soft_I2C_Stop();
    
    }
    #endif
    #endif

  #ifdef  _SETTRACEV2PERCENTI2C_
  #ifndef _SETTRACEV2PERCENTI2C_EXISTS_
  #define _SETTRACEV2PERCENTI2C_EXISTS_
  
  #include "I2C_Soft.h"
  #ifndef _TRACEV2_
  #define _TRACEV2_ u32
  #endif

   void SetTraceV2PercentI2C( _TRACEV2_ which,u8 molecular,u8 denominator){
   struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
   
    Soft_I2C_Start();
    Soft_I2C_Write(0x18);
    Soft_I2C_Write(55);
    Soft_I2C_Write(molecular);
    Soft_I2C_Write(denominator);
    Soft_I2C_Stop();
    }
    #endif
    #endif

//==GetADScable3C Readding ID:  == DON'T DELETE!! ==

#ifdef _GETADSCABLE3C_
 #ifndef  _GETADSCABLE3C_EXISTS_
  #define _GETADSCABLE3C_EXISTS_
  

  #ifndef _SCABLEAD3C_
   #define _SCABLEAD3C_ unsigned long
  #endif

  unsigned int GetADScable3C(_SCABLEAD3C_ which,unsigned char state){
    struct select *information=&which;
   u32 port1=portarray[information->group1];
   u32 port2=portarray[information->group2];
   u8 bit1=information->bit1;
   u8 bit2=information->bit2;

    u16 data;
    u8 channel;
    GPIO_Setting((GPIO_TypeDef*)port1,bit1,GPIO_Mode_AN,0,0);
    GPIO_Setting((GPIO_TypeDef*)port2,bit2,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);
    if(state==1)
    {
     GPIO_SetBits(port2,1<<bit2);
    }
    else
    {
     GPIO_ResetBits(port2,1<<bit2);
    }
    channel=Adc_ReturChannel(information->group1,bit1);
    i=GetAdcResult(channel);
    return (u16)data;
  }
 #endif
#endif

//==GETTOUCHSCREENX Readding ID:  == DON'T DELETE!! ==

#ifdef _GETTOUCHSCREENX_
 #ifndef  _GETTOUCHSCREENX_EXISTS_
  #define _GETTOUCHSCREENX_EXISTS_
 
  #ifndef _GETTOUCHSCREENX_
   #define _GETTOUCHSCREENX_ unsigned long
  #endif

  unsigned char GetTouchScreenX(void)
  {
	/*/
	SendCMD(Cmd_Sensor);
	delayms(2);					//需要做一定的延时
	ScanData(&SlaveMcuData);//*/

	volatile unsigned int ri;
	u16 loop=300;//2.2ms
	SlaveMcuData.TouchX=0;
	SendCMD(Cmd_Sensor);
	do//超时处理
	{	
		for( ri=0; ri<35; ri++ );
		ScanData(&SlaveMcuData);
		if(SlaveMcuData.TouchX)break;
	}while(loop--);

	return SlaveMcuData.TouchX;

  }
 #endif
#endif

//==GETTOUCHSCREENY Readding ID:  == DON'T DELETE!! ==

/*#ifdef _GETTOUCHSCREENY_
 #ifndef  _GETTOUCHSCREENY_EXISTS_
  #define _GETTOUCHSCREENY_EXISTS_
 
  #ifndef _GETTOUCHSCREENY_
   #define _GETTOUCHSCREENY_ unsigned long
  #endif

  unsigned char GetTouchScreenY(void)
  {
	SendCMD(Cmd_Sensor);
	delayms(2);					//需要做一定的延时
	ScanData(&SlaveMcuData);

	return SlaveMcuData.TouchY;

  }
 #endif
#endif//*/
#ifdef _GETTOUCHSCREENY_
 #ifndef  _GETTOUCHSCREENY_EXISTS_
  #define _GETTOUCHSCREENY_EXISTS_
 
  #ifndef _GETTOUCHSCREENY_
   #define _GETTOUCHSCREENY_ unsigned long
  #endif

  unsigned char GetTouchScreenY(void)
  {
	u8 touchc=0;
	/*/
	SendCMD(Cmd_Sensor);
	delayms(2);					//需要做一定的延时
	ScanData(&SlaveMcuData);//*/
	
	volatile unsigned int ri;
	u16 loop=300;//2.2ms
	SlaveMcuData.TouchY=0;
	SendCMD(Cmd_Sensor);
	do//超时处理
	{	
		for( ri=0; ri<35; ri++ );
		ScanData(&SlaveMcuData);
		if(SlaveMcuData.TouchY)break;
	}while(loop--);
	
	if(TTSC_Flag)
	{
		if(SlaveMcuData.TouchY>175)SlaveMcuData.TouchY=175;
		if(SlaveMcuData.TouchY==0)SlaveMcuData.TouchY=175;
		touchc=175-SlaveMcuData.TouchY;
	}
	else touchc=SlaveMcuData.TouchY;
	
	return touchc;
  }
 #endif
#endif//*/
//==GETGETGSENSOR Readding ID:  == DON'T DELETE!! ==

#ifdef _GETGSENSOR_
 #ifndef  _GETGSENSOR_EXISTS_
  #define _GETGSENSOR_EXISTS_
 
  #ifndef _GETGSENSOR_
   #define _GETGSENSOR_ unsigned long
  #endif

int GetGSensor(unsigned char axis)
  {
	u8 value;
	int mData;
	SendCMD(Cmd_Sensor);
	delayms(2);					//需要做一定的延时
	ScanData(&SlaveMcuData);
	switch(axis)
	{
	case 1:value=SlaveMcuData.gSense_X;break;
	case 2:value=SlaveMcuData.gSense_Y;break;
	case 3:value=SlaveMcuData.gSense_Z;break;
	}
	//调整数值，在5位显示不会出现问题
	if(value>=128)
	{
	mData = (int)(value-256); 
	}
	else
	{
	mData = (int)value;
	}
	return mData;
  }
 #endif
#endif

//==GETINMIC Readding ID:  == DON'T DELETE!! ==

#ifdef _GETINMIC_
 #ifndef  _GETINMIC_EXISTS_
  #define _GETINMIC_EXISTS_
 
  #ifndef _GETINMIC_
   #define _GETINMIC_ unsigned long
  #endif

  unsigned int GetInMic(void)
  {
	unsigned char value;
	SendCMD(Cmd_Sensor);
	delayms(2);					//需要做一定的延时
	ScanData(&SlaveMcuData);
	return SlaveMcuData.Sound;
  }
 #endif
#endif

#ifdef _SETINBEEP_
 #ifndef  _SETINBEEP_EXISTS_
  #define _SETINBEEP_EXISTS_
 
  #ifndef _SETINBEEP_
   #define _SETINBEEP_ unsigned long
  #endif

void SetInBeep(u8 state)
  {
	if(state==1)
	{
	SendCMD(Cmd_BeepOn);
	}
	else
	{
	SendCMD(Cmd_BeepOff);
	}  
}
 #endif
#endif

//==GETINVOTAGE Readding ID:  == DON'T DELETE!! ==

#ifdef _GETINVOTAGE_
 #ifndef  _GETINVOTAGE_EXISTS_
  #define _GETINVOTAGE_EXISTS_
 
  #ifndef _GETINVOTAGE_
   #define _GETINVOTAGE_ unsigned long
  #endif

  unsigned int GetInVotage(void)
  {
	unsigned char value;
	SendCMD(Cmd_Sensor);
	delayms(2);					//需要做一定的延时
	ScanData(&SlaveMcuData);
	return SlaveMcuData.PowerVotage;
  }
 #endif
#endif


//==SETINWIRELESS Readding ID:  == DON'T DELETE!! ==

#ifdef _SETINWIRELESS_
 #ifndef  _SETINWIRELESS_EXISTS_
  #define _SETINWIRELESS_EXISTS_
 
  #ifndef _SETINWIRELESS_
   #define _SETINWIRELESS_ unsigned long
  #endif

  unsigned char SetInWireless(u8 data)
  {
	u8 k,odd;
	odd=0x60+data;
	SendWireless[3]=data;
	for(k=0;k<7;k++)
	{
	SendWireless[4+k] =0;
	}
	SendWireless[11]=odd;				//校验
	SendCMD(SendWireless);
	delayms(4);					//需要做一定的延时
	ScanData(&WirelessData);
	if(WirelessData.AckCMD==0x62)
	{
	return 1;
	}
	else
	{
	return 0;
	}
  }

  unsigned char SetInWireless_Original(u8* pBuf)
  {
	u8 k,odd;
	odd=0x60;
	for(k=0;k<8;k++)
	{
	SendWireless[3+k] = *(pBuf+k);
	odd+=*(pBuf+k);
	}
	SendWireless[11]=odd;				//校验
	SendCMD(SendWireless);
	delayms(4);					//需要做一定的延时
	ScanData(&WirelessData);
	if(WirelessData.AckCMD==0x62)
	{
	return 1;
	}
	else
	{
	return 0;
	}
  }
 #endif
#endif

//==GETINWIRELESS Readding ID:  == DON'T DELETE!! ==

#ifdef _GETINWIRELESS_
 #ifndef  _GETINWIRELESS_EXISTS_
  #define _GETINWIRELESS_EXISTS_
 
  #ifndef _GETINWIRELESS_
   #define _GETINWIRELESS_ unsigned long
  #endif

  unsigned char GetInWireless(void)
  {
	u8 i,value;
	SendCMD(RevWireless);
	delayms(3);					//需要做一定的延时
	ScanData(&WirelessData);
	value=WirelessData.WL_Data[0];
	WirelessData.WL_Data[0]=0;
	return value;
/*
	if(WirelessData.AckCMD==0x71)
	{
	for(i=0;i<8;i++)*(pBuf+i)=WirelessData.WL_Data[i];
	return 0;
	}
	else
	{
	for(i=0;i<8;i++)*(pBuf+i)=0;
	return 1;
	}
*/
  }

  unsigned char GetInWireless_Original(u8* pBuf)
  {
	u8 i,value;
	SendCMD(RevWireless);
	delayms(3);					//需要做一定的延时
	value=ScanData(&WirelessData);

	if(WirelessData.AckCMD==0x71)
	{
	for(i=0;i<8;i++)*(pBuf+i)=WirelessData.WL_Data[i];
	return 0;
	}
	else
	{
	for(i=0;i<8;i++)*(pBuf+i)=0;
	return 1;
	}
  }
 #endif
#endif

//==SetOneServo Readding ID:  == DON'T DELETE!! ==

#ifdef _SETONESERVO_
 #ifndef  _SETONESERVO_EXISTS_
  #define _SETONESERVO_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _SERVOCTRL_
   #define _SERVOCTRL_ unsigned long
  #endif
  
#define _SERVO2_ADDR_		(0x18)//0x18
void SetOneServo(_SERVOCTRL_ which,u8 Channel, u8 angle, u16 time)
{
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

	u8 timh,timl;
	
	timh=time>>8;
	timl=time&0xff;
    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    Soft_I2C_Start();
    Soft_I2C_Write(_SERVO2_ADDR_);
    Soft_I2C_Write(0xfa);
    Soft_I2C_Write( Channel);
    Soft_I2C_Write(angle);
    Soft_I2C_Write(timh);
    Soft_I2C_Write(timl);
    Soft_I2C_Stop();
}
 #endif
#endif


//==SetAllServo Readding ID:  == DON'T DELETE!! ==

#ifdef _SETALLSERVO_
 #ifndef  _SETALLSERVO_EXISTS_
  #define _SETALLSERVO_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _SERVOCTRL_
   #define _SERVOCTRL_ unsigned long
  #endif
  
#define _SERVO2_ADDR_		(0x18)//0x18
void SetAllServo(_SERVOCTRL_ which,u8 angle1,u8 angle2,u8 angle3,u8 angle4,u8 angle5,u8 angle6,u8 angle7,u8 angle8,u16 time)
{
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

	u8 timh,timl;
	
	timh=time>>8;
	timl=time&0xff;
    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
    Soft_I2C_Start();
    Soft_I2C_Write(_SERVO2_ADDR_);
    Soft_I2C_Write(angle1);
    Soft_I2C_Write(angle2);
    Soft_I2C_Write(angle3);
    Soft_I2C_Write(angle4);
    Soft_I2C_Write(angle5);
    Soft_I2C_Write(angle6);
    Soft_I2C_Write(angle7);
    Soft_I2C_Write(angle8);
    Soft_I2C_Write(timh);
    Soft_I2C_Write(timl);
    Soft_I2C_Stop();
}
 #endif
#endif

//==GETEXTGSENSOR Readding ID:0xa6  == DON'T DELETE!! == 外部3軸加速度

#ifdef _GETEXTGSENSOR_
 #ifndef  _GETEXTGSENSOR_EXISTS_
  #define _GETEXTGSENSOR_EXISTS_
	#include "I2C_Soft.h"
  
  #ifndef _EXTGSENSOR_
   #define _EXTGSENSOR_ unsigned long
  #endif
  
#define _GSENSOR_ADDR_  0xA6
//2:6.6ms;  4:9ms;  3:7.9ms
#define _GS_cnt_ 	4//均值滤波个数>=2
void ADXL345_Write(u8 Reg,u8 Data)
{

	Soft_I2C_Start();
	Soft_I2C_Write(_GSENSOR_ADDR_);
	Soft_I2C_Write(Reg);
	Soft_I2C_Write(Data);
	Soft_I2C_Stop();
}
void gSense_Init(void)
{
	ADXL345_Write(0x31, 0x00);	//设置测量范围
	ADXL345_Write(0x2C, 0x0A);  //设定速率
	ADXL345_Write(0x2D, 0x08);  //设定电源模式
	ADXL345_Write(0x1E, 0x00);  //X偏移量 0 用于校正
	ADXL345_Write(0x1F, 0x00);  //Y偏移量 0
	ADXL345_Write(0x20, 0x00);  //Z偏移量 0 
}
int GetExtGSensor(_EXTGSENSOR_ which,u8 axis)
{
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

	u8 i,j,m_temp[6];
	s16 GS_X,GS_Y,GS_Z;
	s8 g_x,g_y,g_z;
	s8 buf=0;
	s16 GS_Data[_GS_cnt_][3];  //重力加速度的历史记录，滑动滤波
	u8 GS_idx;
	
	
	gSense_Init();//初始化
	delayms(2);
	
	for(GS_idx=0;GS_idx<_GS_cnt_;GS_idx++)
	{
		Soft_I2C_Start();
		Soft_I2C_Write(_GSENSOR_ADDR_);
		Soft_I2C_Write(0x32);
		Soft_I2C_Start();
		Soft_I2C_Write(_GSENSOR_ADDR_+1);
		for(j=0;j<5;j++)m_temp[j]=Soft_I2C_Read(0);
		m_temp[5]=Soft_I2C_Read(1);
		Soft_I2C_Stop();

		GS_Data[GS_idx][0]	=	(m_temp[1]*256+m_temp[0]);
		GS_Data[GS_idx][1]	=	(m_temp[3]*256+m_temp[2]);
		GS_Data[GS_idx][2]	=	(m_temp[5]*256+m_temp[4]);
	}
	GS_X = 0;
	GS_Y = 0;
	GS_Z = 0;
	g_x = 0;
	g_y = 0;
	g_z = 0;
	
	for(i=0;i<_GS_cnt_;i++)
	{
		GS_X += GS_Data[i][0];
		GS_Y += GS_Data[i][1];
		GS_Z += GS_Data[i][2];
	}
	
	g_x	=(s8)(GS_X/4/_GS_cnt_);
	g_y	=(s8)(GS_Y/4/_GS_cnt_);
	g_z	=(s8)(GS_Z/4/_GS_cnt_);
	
	switch(axis)
	{
		case 1:buf=g_x;break;
		case 2:buf=g_y;break;
		case 3:buf=g_z;break;
	}
	return buf;
}
 #endif
#endif

//==SetLCDSolidCircle Readding ID:  == DON'T DELETE!! == 画实心圆

#ifdef _SETLCDSOLIDCIRCLE_
 #ifndef  _SETLCDSOLIDCIRCLE_EXISTS_
  #define _SETLCDSOLIDCIRCLE_EXISTS_
  #include "LCD220176.h"
  
void SetLCDSolidCircle(u8 x,u8 y,u8 radius,u16 color)
{
	u16 xs,xe,ix,ys,ye,iy,yb,ib;
	if(x>radius)xs=x-radius;
	else xs=0;
	xe=x+radius;
	SendCMD(Cmd_LcdBackOn);//
	for(ix=xs;ix<=xe;ix++)
	{
		if(ix>x)	ib=sqrt(radius*radius-(ix-x)*(ix-x));
		else ib=sqrt(radius*radius-(x-ix)*(x-ix));
		if(y>ib)ys=y-ib;
		else ys=0;
		ye=y+ib;
		if(ye>175)ye=175;
		LCD_DrawRectangle( ix,ys,ix, ye, color);
	}
}
 #endif
#endif

//==SetLCDFilledRectangle Readding ID:  == DON'T DELETE!! == 画实心矩形

#ifdef _SETLCDFILLEDRECTANGLE_
 #ifndef  _SETLCDFILLEDRECTANGLE_EXISTS_
  #define _SETLCDFILLEDRECTANGLE_EXISTS_
  #include "LCD220176.h"

void SetLCDFilledRectangle(u8 x1,u8 y1,u8 x2,u8 y2,u16 color)
{
	LCD_DrawRectangle(x1,y1,x2,y2,color);
}
 #endif
#endif

//==SetLCDRectangle Readding ID:  == DON'T DELETE!! == 画矩形

#ifdef _SETLCDRECTANGLE_
 #ifndef  _SETLCDRECTANGLE_EXISTS_
  #define _SETLCDRECTANGLE_EXISTS_
  #include "LCD220176.h"

void SetLCDRectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 w,u16 color)
{
	u8 wmx,wmy,wm;
	wmx=x2-x1;
	wmy=y2-y1;
	wm=(wmx<wmy)?wmx:wmy;
	if(w>wm)w=wm;
	if(w>0)w-=1;
	
	LCD_DrawRectangle( x1,y1,x2,y1+w, color);
	LCD_DrawRectangle( x1,y1+w,x1+w, y2, color);
	LCD_DrawRectangle( x1+w,y2-w,x2, y2, color);
	LCD_DrawRectangle( x2-w,y1+w,x2, y2-w, color);
}
 #endif
#endif

//==SETTOUCHTOSCREENCOORDINATE Readding ID:  == DON'T DELETE!! ==

#ifdef _SETTOUCHTOSCREENCOORDINATE_
 #ifndef  _SETTOUCHTOSCREENCOORDINATE_EXISTS_
  #define _SETTOUCHTOSCREENCOORDINATE_EXISTS_
  
void SetTouchToScreenCoordinate(void)
{
	TTSC_Flag=1;
}
 #endif
#endif

//==SetBluetooth Readding ID:  == DON'T DELETE!! ==

#ifdef _SETBLUETOOTH_
 #ifndef  _SETBLUETOOTH_EXISTS_
  #define _SETBLUETOOTH_EXISTS_

void SetBluetooth(u8 data)
{
	SendBTData(data);
}
 #endif
#endif

//==GetBluetooth Readding ID:  == DON'T DELETE!! ==

#ifdef _GETBLUETOOTH_
 #ifndef  _GETBLUETOOTH_EXISTS_
  #define _GETBLUETOOTH_EXISTS_
 
u16 GetBluetooth(void)
{
	u16 buf;
	buf=ReadBTData();
	return buf;
}
 #endif
#endif

//==SetLCD1CharBig Readding ID:  == DON'T DELETE!! ==

#ifdef _SETLCD1CHARBIG_
 #ifndef  _SETLCD1CHARBIG_EXISTS_
  #define _SETLCD1CHARBIG_EXISTS_
  //#define _LCD_BIG_
  #ifdef _LCD_BIG_
  //#define  CHARBIGLIB_METHOD 	1//完整字库开关
  #include "LCDBIG.h"

  void SetLCD1CharBig(u8 x,u8 y,u8 data,u16 ch_color, u16 bg_color)
  {
	SendCMD(Cmd_LcdBackOn);
	LCD_en_Big(x,y,data,ch_color, bg_color);
  }
  #endif
 #endif
#endif

//==SetIntegrateMotor Readding ID:  == DON'T DELETE!! == BE1729

#ifdef _SETINTEGRATEMOTOR_
 #ifndef  _SETINTEGRATEMOTOR_EXISTS_
  #define _SETINTEGRATEMOTOR_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _INTEGRATE_
   #define _INTEGRATE_ unsigned long
  #endif

void SetIntegrateMotor(_INTEGRATE_ which,u8 state)
{
    struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
    
	Soft_I2C_Start();
	Soft_I2C_Write(0x18);
	Soft_I2C_Write(state);
	Soft_I2C_Stop();
}
 #endif
#endif
//==GetIntegrateAdc Readding ID:  == DON'T DELETE!! == BE1729
#ifdef _GETINTEGRATEADC_
 #ifndef  _GETINTEGRATEADC_EXISTS_
  #define _GETINTEGRATEADC_EXISTS_
  #include "I2C_Soft.h"
  #ifndef _INTEGRATE_
   #define _INTEGRATE_ unsigned long
  #endif

vu8 ADC_Buffer[4];
u16 GetIntegrateAdc(_INTEGRATE_ which,u8 channel)
{
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;

	u8 data=0;
    Soft_I2C_Start();
    Soft_I2C_Write(0x19);
    ADC_Buffer[0]=Soft_I2C_Read(0);
    ADC_Buffer[1]=Soft_I2C_Read(0);
    ADC_Buffer[2]=Soft_I2C_Read(0);
    ADC_Buffer[3]=Soft_I2C_Read(1);
    Soft_I2C_Stop();

   if(channel==1)data= ADC_Buffer[0];
   else if(channel==2)data= ADC_Buffer[1];
   else if(channel==3)data= ADC_Buffer[2];
   else if(channel==4)data= ADC_Buffer[3];
   else data=999;
   return data;
}
 #endif
#endif

//=============== BE1128 寻迹卡 BUS485 ===============
#ifdef _GETTRACEV2BUS_
 #ifndef _GETTRACEV2BUS_EXISTS_
  #define _GETTRACEV2BUS_EXISTS_

u32 GetTraceV2Bus(u8 id, u8 command)//bus485 读寻迹卡
{
	u8 m_TxList[7];//校验
	u8 size=7;//发送数据包数据包大小
	u8 m_RxList[13]={0,0,0,0,0,0,0,0,0,0};
	vu16 dt=300,ri;//超时处理
	u8 i=0;
	u8 m_sum=0;
	SetBus485Baud(921600);
	//FistByte+SecondByte+Size+ID+parameter1+[sum]+Endbyte
	//Size:数据包的大小,不含FistByte,SecondByte,Size,Endbyte
	m_TxList[0]=0xaa;//字头
	m_TxList[1]=0x19;//从机地址0x18,LSB=1 计算检验和,LSB=0 不计算校验和
	m_TxList[2]=size-4;//数据包大小
	m_TxList[3]=id;//id号
	m_TxList[4]=command;//parameter1
	m_TxList[5]=m_TxList[2]+m_TxList[3]+m_TxList[4];//sum:校验和,sum=Size+ID+parameter1
	m_TxList[size-1]=0xf5;//字尾
	Bus485_SendCmd(&m_TxList,size);//发送数据
	
	//FistByte+SecondByte+SlaveAddr+ID+parameter1+parameter2+...+parameter8+Endbyte
	do
	{
		for( ri=0; ri<35; ri++ );
		i=RS485_ScanData(&m_RxList);
		if(i)break;
	}while(dt--);
	
	if(dt==0&&i==0)return 999;//超时
	//检验
	for(ri=3;ri<=10;ri++)	m_sum+=m_RxList[ri];//sum=ID+parameter1+parameter2+...+parameter8
	if(m_RxList[2]==m_TxList[1]&&m_RxList[3]==id&&(u8)m_sum==m_RxList[11])return m_RxList[4];//检验地址&ID&检验和
	return 999;
}
 #endif
#endif

#ifdef _SETTRACEV2COLORBUS_
 #ifndef _SETTRACEV2COLORBUS_EXISTS_
  #define _SETTRACEV2COLORBUS_EXISTS_

void SetTraceV2ColorBus(u8 id,u8 ch1,u8 ch2,u8 ch3,u8 ch4,u8 ch5,u8 ch6,u8 ch7)//bus485 设置寻迹卡LED状态
{
	u8 m_TxList[14];
	u8 size=14;//发送数据包数据包大小
	SetBus485Baud(921600);
	//FistByte+SecondByte+Size+ID+parameter1+[parameter2]+[...]+[sum]+Endbyte
	//Size:数据包的大小,不含FistByte,SecondByte,Size,Endbyte
	m_TxList[0]=0xaa;//字头
	m_TxList[1]=0x19;//从机地址0x18,LSB=1 计算检验和,LSB=0 不计算校验和
	m_TxList[2]=size-4;//数据包大小
	m_TxList[3]=id;//id号
	m_TxList[4]=51;//cmd
	m_TxList[5]=ch1;
	m_TxList[6]=ch2;
	m_TxList[7]=ch3;
	m_TxList[8]=ch4;
	m_TxList[9]=ch5;
	m_TxList[10]=ch6;
	m_TxList[11]=ch7;
	//sum:校验和,sum=Size+ID+parameter1+...
	m_TxList[12]=m_TxList[2]+m_TxList[3]+m_TxList[4]+m_TxList[5]+m_TxList[6]+m_TxList[7]+m_TxList[8]+m_TxList[9]+m_TxList[10]+m_TxList[11];
	m_TxList[size-1]=0xf5;//字尾
	Bus485_SendCmd(&m_TxList,size);//发送数据
}
 #endif
#endif

#ifdef _SETTRACEV2BEEPBUS_
 #ifndef _SETTRACEV2BEEPBUS_EXISTS_
  #define _SETTRACEV2BEEPBUS_EXISTS_

void SetTraceV2BeepBus(u8 id, u8 time)//bus485 设置寻迹卡蜂鸣器时长
{
	u8 m_TxList[8];
	u8 size=8;//发送数据包数据包大小
	SetBus485Baud(921600);
	//FistByte+SecondByte+Size+ID+parameter1+[parameter2]+[...]+[sum]+Endbyte
	//Size:数据包的大小,不含FistByte,SecondByte,Size,Endbyte
	m_TxList[0]=0xaa;//字头
	m_TxList[1]=0x19;//从机地址0x18,LSB=1 计算检验和,LSB=0 不计算校验和
	m_TxList[2]=size-4;//数据包大小
	m_TxList[3]=id;//id号
	m_TxList[4]=52;//cmd
	m_TxList[5]=time;
	//sum:校验和,sum=Size+ID+parameter1+...
	m_TxList[6]=m_TxList[2]+m_TxList[3]+m_TxList[4]+m_TxList[5];
	m_TxList[size-1]=0xf5;//字尾
	Bus485_SendCmd(&m_TxList,size);//发送数据
}
 #endif
#endif

#ifdef _SETTRACEV2PERCENTBUS_
 #ifndef _SETTRACEV2PERCENTBUS_EXISTS_
  #define _SETTRACEV2PERCENTBUS_EXISTS_

void SetTraceV2PercentBus(u8 id, u8 molecular, u8 denominator)//bus485 设置寻迹卡蜂阈值比例
{
	u8 m_TxList[9];
	u8 size=9;//发送数据包数据包大小
	SetBus485Baud(921600);
	//FistByte+SecondByte+Size+ID+parameter1+[parameter2]+[...]+[sum]+Endbyte
	//Size:数据包的大小,不含FistByte,SecondByte,Size,Endbyte
	m_TxList[0]=0xaa;//字头
	m_TxList[1]=0x19;//从机地址0x18,LSB=1 计算检验和,LSB=0 不计算校验和
	m_TxList[2]=size-4;//数据包大小
	m_TxList[3]=id;//id号
	m_TxList[4]=55;//cmd
	m_TxList[5]=molecular;//parameter2
	m_TxList[6]=denominator;//parameter3
	//sum:校验和,sum=Size+ID+parameter1+...
	m_TxList[7]=m_TxList[2]+m_TxList[3]+m_TxList[4]+m_TxList[5]+m_TxList[6];//sum:校验和,sum=Size+ID+parameter1
	m_TxList[size-1]=0xf5;//字尾
	Bus485_SendCmd(&m_TxList,size);//发送数据
}
 #endif
#endif

//==GetColorSensor Readding ID:  == DON'T DELETE!! == BE1130
//addr 10bit
#ifdef _GETCOLORSENSOR_
 #ifndef  _GETCOLORSENSOR_EXISTS_
  #define _GETCOLORSENSOR_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _COLOR_
   #define _COLOR_ unsigned long
  #endif

u32 GetColorSensor(_COLOR_ which,u8 id ,u8 cmd)
{   
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

	SDA_PORT=port2;
	SDA_BIT=bit2;
	SCL_PORT=port1;
	SCL_BIT=bit1;

	u32 m_val=0;
	u8 m_val1=0, m_val2=0, m_val3=0;
	u8 m_bit1=0, m_bit2=0;
	u8 first=0,end=0;
	u8 m_id=0;
	u8 sum=0,m_para1=0,m_para2=0;
	u8 addrh,addrl;
	
	u8 addr;
	if(id>8||id==0)return 999;//忽略不在指定范围的地址
	//if(cmd>20)return 999;//忽略不在指定范围的命令
	
	addr=id+0x50-1;//0xf650~0xf657
	
	//FistByte+cmd+parameter1+parameter2+sum
	Soft_I2C_Start();
	Soft_I2C_Write(0xf6);//SlaveAddrH
	Soft_I2C_Write(addr);//SlaveAddrL
	Soft_I2C_Write(0xFA);//0
	Soft_I2C_Write(cmd);//2
	
	//FistByte+id+parameter1+[parameter2]+[parameter3]+sum
	//if(cmd<20&&cmd>0)//接收数据
	//if((cmd<20&&cmd>0)||(cmd>60&&cmd<=71)||((cmd>=254)&&(cmd<=255)))
	{
		Soft_I2C_Start();//重复起始位
		Soft_I2C_Write(0xf7);//SlaveAddr|0x01
		first=Soft_I2C_Read(0);
		m_id=Soft_I2C_Read(0);//低八位地址
		m_val1=Soft_I2C_Read(0);
		if((cmd>=5&&cmd<=18)||(cmd>60&&cmd<=71)||(cmd==254))//2/3个byte
		{
			m_val2=Soft_I2C_Read(0);
			m_bit1=8;m_bit2=0;
		}
		if(cmd==5)//3byte
		{
			m_val3=Soft_I2C_Read(0);
			m_bit1=16;m_bit2=8;
		}
		end=Soft_I2C_Read(1);
	}	
	Soft_I2C_Stop();//停止位
	
	sum=m_id+m_val1+m_val2+m_val3;//校验和计算

	if(first==0xEA&&sum==end&&m_id==addr)	
	{
		m_val=(u32)(m_val1<<m_bit1)|(m_val2<<m_bit2)|(m_val3);
	}
	else 
	{
		m_val=999;
	}
	return m_val;
}
 #endif
#endif

//==GetColorSensorID Readding ID:  == DON'T DELETE!! == BE1130
//addr 10bit
#ifdef _GETCOLORSENSORID_
 #ifndef  _GETCOLORSENSORID_EXISTS_
  #define _GETCOLORSENSORID_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _COLOR_
   #define _COLOR_ unsigned long
  #endif

u16 GetColorSensorID(_COLOR_ which)
{   
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

	SDA_PORT=port2;
	SDA_BIT=bit2;
	SCL_PORT=port1;
	SCL_BIT=bit1;
    
	u8 sum=0;
	u8 addr=0x50;//临时地址的低八位
	u8 m_addrh,m_addrl;
	u8 first,m_id,end;
	u16 m_val;
	//sum=ID+cmd+parameter1+parameter2;
	u8 id=0,cmd=41;//41;
	sum=cmd+0xf6+addr;//sum=0+parameter1+parameter2+parameter3
	//从机地址为10Bite 0xf6xx:高2位固定为11,低八位为0x50~0x57,即实际使用的地址为0x350~0x357(0xf650~0xf657)
	//TX //FistByte+cmd+parameter1+parameter2+sum
	Soft_I2C_Start();
	Soft_I2C_Write(0);//广播地址
	Soft_I2C_Write(0xEA);//I2C_SetFirstByte
	Soft_I2C_Write(cmd);//写从机命令
	Soft_I2C_Write(0xf6);//写入临时地址 地址高八位固定为11
	Soft_I2C_Write(addr);//写入临时地址
	Soft_I2C_Stop();
	
	delayms(50);//延时等待设置成功
	
	//RX FistByte+id+parameter1+[parameter2]+sum
	Soft_I2C_Start();
	Soft_I2C_Write(0xf6);//写临时地址
	Soft_I2C_Write(addr);//
	Soft_I2C_Start();
	Soft_I2C_Write(0xf7);//读数据
	first=Soft_I2C_Read(0);
	m_id=Soft_I2C_Read(0);//该值为临时地址的低八位
	m_addrh=Soft_I2C_Read(0);//地址高八位应该为0xf6
	m_addrl=Soft_I2C_Read(0);//地址低八位
	end=Soft_I2C_Read(1);
	Soft_I2C_Stop();
	delayms(50);//延时等待设置成功
	//校验
	//id实际就是地址低八位SlaveAddr&0x00ff
	sum=(u8)(m_id+m_addrh+m_addrl);//sum=id+parameter1+[parameter2]+[parameter3]
	if(first==0xEA&&sum ==end&&m_addrh==0xf6&&m_id==addr)
	{
		//m_val=(u16)(m_addrh<<8)|(m_addrl);
		m_val=m_addrl-0x50+1;
	}
	else m_val=999;

	return m_val;
}
 #endif
#endif

//==SetColorSensor Readding ID:  == DON'T DELETE!! == BE1130
//addr 10bit
#ifdef _SETCOLORSENSOR_
 #ifndef  _SETCOLORSENSOR_EXISTS_
  #define _SETCOLORSENSOR_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _COLOR_
   #define _COLOR_ unsigned long
  #endif

u32 SetColorSensor(_COLOR_ which,u8 id ,u8 cmd,u16 parameter)
{   
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

	SDA_PORT=port2;
	SDA_BIT=bit2;
	SCL_PORT=port1;
	SCL_BIT=bit1;
    
	u8 sum=0;
	u8 addr=0x50;//临时地址的低八位
	u8 m_addrh,m_addrl;
	u8 first,m_id,end;
	u16 m_val;
	
	if(cmd==40||cmd==41)return;
	//sum=ID+cmd+parameter1+parameter2;
	//从机地址为10Bite 0xf6xx:高2位固定为11,低八位为0x50~0x57,即实际使用的地址为0x350~0x357(0xf650~0xf657)
	//TX FistByte+cmd+parameter1+parameter2
	Soft_I2C_Start();
	Soft_I2C_Write(0xf6);//写临时地址
	Soft_I2C_Write(addr);//
	Soft_I2C_Write(0xEA);//0I2C_SetFirstByte
	Soft_I2C_Write(cmd);//写从机命令
	Soft_I2C_Write(parameter>>8);//
	Soft_I2C_Write(parameter&0xff);//
	Soft_I2C_Stop();
	
	if((cmd>=31)&&(cmd<=37)||(cmd>=43&&cmd<=55))delayms(25);
	if(cmd==33||cmd==43)delayms(175);
}
 #endif
#endif

//==SetColorSensorID Readding ID:  == DON'T DELETE!! == BE1130
//addr 10bit
#ifdef _SETCOLORSENSORID_
 #ifndef  _SETCOLORSENSORID_EXISTS_
  #define _SETCOLORSENSORID_EXISTS_
  
  #include "I2C_Soft.h"
  
  #ifndef _COLOR_
   #define _COLOR_ unsigned long
  #endif

void SetColorSensorID(_COLOR_ which,u8 id,u16 value)
{   
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

	SDA_PORT=port2;
	SDA_BIT=bit2;
	SCL_PORT=port1;
	SCL_BIT=bit1;
    
	u8 sum=0,addr,id_addr=0;
	//FistByte+cmd+parameter1+parameter2
	if(value>8||value==0)return;//其他ID地址忽略
	addr=(u8)(value&0xff)+0x50-1;//value=1~8
	if(id)id_addr=id+0x50-1;
	id_addr|=0X80;//最高位为1写入数据之后马上修改地址,0只将地址写入模块不修改地址
	sum=id+40+addr;//sum=id+parameter1+parameter2+parameter3 id实际就是地址低八位SlaveAddr&0x00ff
	//从机地址为10Bite 0xf6xx:高2位固定为11,低八位为0x50~0x57,即实际使用的地址为0x350~0x357(0xf650~0xf657)
	//TX FistByte+cmd+parameter1+parameter2
	Soft_I2C_Start();
	Soft_I2C_Write(0);//广播地址
	Soft_I2C_Write(0xEA);//0I2C_SetFirstByte
	Soft_I2C_Write(40);//40写从机命令
	Soft_I2C_Write(id_addr);//需要修改ID的传感器,0则批量（广播）修改
	Soft_I2C_Write(addr);//ID的低八位
	Soft_I2C_Stop();
	delayms(50);//延时等待设置成功
}
 #endif
#endif


//==SETAHRS Readding ID:  == DON'T DELETE!! == 六轴

#ifdef _SETAHRS_
 #ifndef  _SETAHRS_EXISTS_
  #define _SETAHRS_EXISTS_
  
  #ifndef _AHRS_
   #define _AHRS_ unsigned long
  #endif

  #include "I2C_Soft.h"
void SetAHRS(_AHRS_ which,u8 command)
{
   	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
	
	Soft_I2C_Start();
	Soft_I2C_Write(0x3a);//addr
	Soft_I2C_Write(0xaa);
	Soft_I2C_Write(0x55);
	Soft_I2C_Write(command);
	Soft_I2C_Write(0);
	Soft_I2C_Write(0);
	Soft_I2C_Write(0);
	Soft_I2C_Write(0xcf);
	Soft_I2C_Stop();
	
	delayms(1000);
}
 #endif
#endif

//==GETAHRS Readding ID:  == DON'T DELETE!! == 六轴

#ifdef _GETAHRS_
 #ifndef  _GETAHRS_EXISTS_
  #define _GETAHRS_EXISTS_
  
  #ifndef _AHRS_
   #define _AHRS_ unsigned long
  #endif

  #include "I2C_Soft.h"
  
  #define RCU_WHICH_SIZE		4//硬件信息个数
  s16 g_AhrsRecBuf[RCU_WHICH_SIZE][9];
  u8 g_AhrsRecBufCnt[RCU_WHICH_SIZE];
  u8 g_AhrsFistRxFlag[RCU_WHICH_SIZE];
  u8 g_LastCmdList[RCU_WHICH_SIZE][9];
s16 GetAHRSRecBuf(u8 which,u8 cnt)//数据已经读出则返回8888
{
	s16 buf;
	if(cnt>RCU_WHICH_SIZE)return 9999;
	buf=g_AhrsRecBuf[which][cnt];
	g_AhrsRecBuf[which][cnt]=8888;
	if(buf!=8888)
	{
		g_AhrsRecBufCnt[which]++;
		g_LastCmdList[which][cnt]=1;
	}
	if(g_AhrsRecBufCnt[which]>8)//已经将缓存全部读出
	{
		g_AhrsRecBufCnt[which]=0;
		g_AhrsFistRxFlag[which]=0;
	}
	return buf;
}
u8 GetWhichNum(_AHRS_ which)
{
	switch(which)
	{
		case 117904:	case 150416:	return(0);	break;//D12
		case 101392:	case 133904:	return(1);	break;//D34
		case 253616:	case 221104:	return(2);	break;//D56
		case 237104:	case 204592:	return(3);	break;//D78
	}
}
s16 GetAHRS(_AHRS_ which,u8 command1,u8 command2)
{
	struct select *information=&which;
	u32 port1=portarray[information->group1];
	u32 port2=portarray[information->group2];
	u8 bit1=information->bit1;
	u8 bit2=information->bit2;

    SDA_PORT=port2;
    SDA_BIT=bit2;
    SCL_PORT=port1;
    SCL_BIT=bit1;
	
	u8 i,j;
	u8 ACK=0;
	s16 m_data;
	u8 m_AhrsRecBufList[22];
	u8 m_Rxflag=0;//接收一次命令
	u8 whichx=GetWhichNum(which);
	
	if(g_AhrsFistRxFlag[whichx]==0||command2||g_LastCmdList[whichx][command1-1])
	{
		m_Rxflag=1;//接收一次缓存
		if(command2==0)g_AhrsFistRxFlag[whichx]=1;
		else g_AhrsFistRxFlag[whichx]=0;
		for(i=0;i<9;i++)	{g_LastCmdList[whichx][i]=0;}//清零
		
		Soft_I2C_Start();
		Soft_I2C_Write(0x3b);//addr
		for(i=0;i<22;i++)
		{
			if(i==21) ACK =1;
			else  ACK = 0;
			m_AhrsRecBufList[i]=Soft_I2C_Read(ACK);  
		}  
		Soft_I2C_Stop();
	}
	if(m_Rxflag)//接收一次数据
    {
		g_AhrsRecBufCnt[whichx]=0;
		if(m_AhrsRecBufList[0]==0xaa && m_AhrsRecBufList[1]==0x55 && m_AhrsRecBufList[21]==0xcf)//正确数据包
		{
			g_AhrsFistRxFlag[whichx]=2;
			g_AhrsRecBuf[whichx][0]=(s16)(m_AhrsRecBufList[2])|(m_AhrsRecBufList[3]<<8);//roll//横滚角 degree（放大10倍）
			g_AhrsRecBuf[whichx][1]=(s16)(m_AhrsRecBufList[4])|(m_AhrsRecBufList[5]<<8);//pitch//仰俯角 degree（放大10倍）
			g_AhrsRecBuf[whichx][2]=(s16)(m_AhrsRecBufList[6])|(m_AhrsRecBufList[7]<<8);//yaw//偏航角 degree（放大10倍）
			g_AhrsRecBuf[whichx][3]=(s16)(m_AhrsRecBufList[8])|(m_AhrsRecBufList[9]<<8);//ax//加速度X g（放大100倍）
			g_AhrsRecBuf[whichx][4]=(s16)(m_AhrsRecBufList[10])|(m_AhrsRecBufList[11]<<8);//ay//加速度Y g（放大100倍）
			g_AhrsRecBuf[whichx][5]=(s16)(m_AhrsRecBufList[12])|(m_AhrsRecBufList[13]<<8);//az//加速度Z g（放大100倍）
			g_AhrsRecBuf[whichx][6]=(s16)(m_AhrsRecBufList[14])|(m_AhrsRecBufList[15]<<8);//gx//陀螺仪X  dps（放大100倍）
			g_AhrsRecBuf[whichx][7]=(s16)(m_AhrsRecBufList[16])|(m_AhrsRecBufList[17]<<8);//gy//陀螺仪Y  dps（放大100倍）
			g_AhrsRecBuf[whichx][8]=(s16)(m_AhrsRecBufList[18])|(m_AhrsRecBufList[19]<<8);//gz//陀螺仪Z  dps（放大100倍）
		}
		else 
		{
			g_AhrsFistRxFlag[whichx]=0;
			return 9999;//接收到非数据包
		}
		m_AhrsRecBufList[0]=0;		
		m_AhrsRecBufList[1]=0; 		
		m_AhrsRecBufList[21]=0;
   }
   if(g_AhrsFistRxFlag[whichx]==2)  m_data=GetAHRSRecBuf(whichx,command1-1);//command1=1~9
   else m_data=9999;
   return (s16)m_data;
}
 #endif
#endif