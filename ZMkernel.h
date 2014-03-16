#ifndef _ZMKERNEL_H_
#define _ZMKERNEL_H_

#include "stm32f2xx.h"

#ifndef   _PinFormat_H_
#define  _PinFormat_H_
//GPIOA GPIOB GPIOC GPIOD GPIOE
const  u32 portarray[5]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE};

struct select
{
unsigned type:4;// 硬件类型
unsigned group1:3;//第一针组号
unsigned bit1:4;//第一针位号
unsigned group2:3;//第二针组号
unsigned bit2:4;//第二针位号
unsigned group3:3;//第三针组号
unsigned bit3:4;//第三针位号
unsigned group4:3;//第四针组号
unsigned bit4:4;//第四针位号
};
#endif
/*
typedef struct
{
u8 head[2];
u8 AckCMD;
u8 TouchValid;
u8 TouchX;
u8 TouchY;
u8 Sound;
u8 PowerVotage;
u8 gSense_X;
u8 gSense_Y;
u8 gSense_Z;
u8 odd;
u8 end;
}SlaveMcuData_typeDef;

typedef struct
{
u8 head[2];
u8 AckCMD;
u8 WL_Data[8];
u8 odd;
u8 end;
}WirelessData_typeDef;
*/
vu8 g_MotorPowerFlag=0;
vu8 g_M1SpeedPer=100,g_M2SpeedPer=100,g_M3SpeedPer=100,g_M4SpeedPer=100;//调节马达输出的速度的百分比
//AI-Servo************************
#define Servo_EnableTx() 	GPIO_SetBits(GPIOD, GPIO_Pin_0)
#define Servo_DisableTx() 	GPIO_ResetBits(GPIOD, GPIO_Pin_0)

#define Servo_EnableRx() 	GPIO_SetBits(GPIOC, GPIO_Pin_12)
#define Servo_DisableRx()	GPIO_ResetBits(GPIOC, GPIO_Pin_12)

#define Motor1 1
#define Motor2 2
#define Motor3 3
#define Motor4 4

#define Motor12 5
#define Motor34 6

#define Servo1 12
#define Servo2 13
#define Servo3 14
#define Servo4 15

#define MotorUp		0
#define MotorDown	2
#define MotorStop		1
//X1RCU_Init
void X2RCU_Init(void);
//GPIO*************************
void GPIO_Setting(GPIO_TypeDef* port,u8 pin,u8 mode,u8 OType,u8 PuPd);
//*****************************
//ADC**************************
u8 Init_ADC(void);
u16 GetAdcResult(u8 chn);
//*****************************
//SERVO************************
void AIServo_Init(void);
void AIServo_SendChar(u8 ch);
u8  AIServo_RevChar(void);
void AIServo_SendCMD(u8 *pd);
//*********************************
//ComServo*************************
u8  ComServoInit(u8 ServoNo);
void ComServoAngle(u8 ServoX,u8 angle);
//EEPROM**************************
u16 ReadEEP(u16 addr);
void WriteEEP(u16 addr,u16 m_value);
//*********************************
//MotorX***************************
u8 Motor_Init(void);
void SetMotorX(u8 MotorX,u8 Dir,u8 Speed);

u8 MotorCodeM1M2_Init(void);
u8 MotorCodeM3M4_Init(void);
void SetMotorY(u8 MotorY,u8 Dir,u8 Speed);

void SetMotorCnt12Zero(void);
void SetMotorCnt34Zero(void);
	
vs32 GetMotorCnt12(void);
vs32 GetMotorCnt34(void);

void SetCodeServoAngle(u8 MotorY,u8 Dir,u8 speed,u32 Pulse);
//*********************************
//*******RS485*********************
#define Bus485_EnableTx() GPIO_SetBits(GPIOD, GPIO_Pin_10)
#define Bus485_EnableRx() GPIO_ResetBits(GPIOD, GPIO_Pin_10)

u8 Bus485_Init(void);
void Bus485_SendChar(u8 ch);
u8  Bus485_RevChar(void);
void Bus485_SendCmd(u8 *pd,u8 i);
//*********************************
u8  RTC_init(void);
void SetSystemTime(void);
u32 GetSystemTime(void);
void delayms(unsigned int ms);
#endif
