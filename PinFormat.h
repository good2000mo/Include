#ifndef   _PinFormat_H_
#define  _PinFormat_H_

const  u32 portarray[5]={0x40020000,0x40020400,0x40020800,0x40020C00,0x40021000};

struct select
{
unsigned type:4;// Ӳ������
unsigned group1:3;//��һ�����
unsigned bit1:4;//��һ��λ��
unsigned group2:3;//�ڶ������
unsigned bit2:4;//�ڶ���λ��
unsigned group3:3;//���������
unsigned bit3:4;//������λ��
unsigned group4:3;//���������
unsigned bit4:4;//������λ��
};
#endif
