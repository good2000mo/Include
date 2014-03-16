#ifndef   _PinFormat_H_
#define  _PinFormat_H_

const  u32 portarray[5]={0x40020000,0x40020400,0x40020800,0x40020C00,0x40021000};

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
