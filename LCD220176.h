#ifndef _LCD220176_H_
#define _LCD220176_H_
#include "stm32f2xx.h"
#include "charcter.h"

#define WHITE         	  0xFFFF
#define BLACK         	  0x0000	  
#define BLUE            	  0x001F  
#define BRED                      0XF81F
#define GRED 			  0XFFE0
#define GBLUE	           0X07FF
#define RED           	           0xF800
#define MAGENTA       	  0xF81F
#define GREEN         	  0x07E0
#define CYAN            	  0x7FFF
#define YELLOW                0xFFE0
#define BROBRREDWN     0XBC40 //棕色
#define BRRED 		  0XFC07 //棕红色
#define GRAY  		  0xD6BA //灰色

//定义宏
void SetCS(u8 temp){if(temp){GPIOE->BSRRL=(1<<12);}else{GPIOE->BSRRH=(1<<12);}}
void SetRS(u8 temp){if(temp){GPIOE->BSRRL=(1<<11);}else{GPIOE->BSRRH=(1<<11);}}
void SetWR(u8 temp){if(temp){GPIOE->BSRRL=(1<<10);}else{GPIOE->BSRRH=(1<<10);}}
void SetRD(u8 temp){if(temp){GPIOE->BSRRL=(1<<9);}else{GPIOE->BSRRH=(1<<9);}}
void SetRst(u8 temp){if(temp){GPIOE->BSRRL=(1<<8);}else{GPIOE->BSRRH=(1<<8);}}

void Delay (u32 nCount)
{
	volatile int i;	 	
	for (i=0;i<nCount*1000;i++);
}

void Delayns(u32 n)
{
	volatile int i;	 	
	for (i=0;i<n;i++);
}
void LCD_PinInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  GPIO_InitStructure.GPIO_Pin = 0x1FFF;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void LCD_Write_Bus(u8 VH,u8 VL)
{
	//GPIOE->BSRR=(VH & 0xFF)|(((~VH) & 0xFF)<<16);
	GPIOE->BSRRL=VH;
	GPIOE->BSRRH=(~VH)&0xFF; 
	SetWR(0);
	Delayns(1);
	SetWR(1);
	

	//GPIOE->BSRR=(VL & 0xFF)|(((~VL) & 0xFF)<<16);
	GPIOE->BSRRL=VL;
	GPIOE->BSRRH=(~VL)&0xFF;
	SetWR(0);
	Delayns(1);
	SetWR(1);
}

void LCD_Write_Com(u8 VH,u8 VL)
{
//SetCS(0);
SetRS(0);
//SetWR(1);
LCD_Write_Bus(VH,VL);
}

void LCD_Write_Data(u8 VH,u8 VL)
{
//SetCS(0);
SetRS(1);
//SetWR(1);
LCD_Write_Bus(VH,VL);
}

void  LCD_WR_REG(u16 Command,u16 Data)
{
LCD_Write_Com(Command>>8,Command);
LCD_Write_Data(Data>>8,Data);
}

void LCD_Init(void)
{
//复位

 SetRst(1);
 Delay(50);
 
 SetCS(0);
 SetRst(0);
 Delay(50);
 
 SetRst(1);
SetCS(1);
SetRD(1);
SetWR(1);

 Delay(50);
 SetCS(0);
 
  LCD_Write_Com(0x00,0x01);LCD_Write_Data(0x01,0x1c);
  LCD_Write_Com(0x00,0x02);LCD_Write_Data(0x01,0x00);
 // LCD_Write_Com(0x00,0x03);LCD_Write_Data(0x10,0x30);
   LCD_Write_Com(0x00,0x03);LCD_Write_Data(0x10,0x28);
  LCD_Write_Com(0x00,0x08);LCD_Write_Data(0x08,0x08);
  LCD_Write_Com(0x00,0x0c);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x0f);LCD_Write_Data(0x0d,0x01);
  LCD_Write_Com(0x00,0x20);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x21);LCD_Write_Data(0x00,0x00);
    Delay(50);
  LCD_Write_Com(0x00,0x10);LCD_Write_Data(0x0a,0x00);
  //LCD_Write_Com(0x00,0x11);LCD_Write_Data(0x10,0x38);
 LCD_Write_Com(0x00,0x11);LCD_Write_Data(0x10,0x3B);
   Delay(50);
  //LCD_Write_Com(0x00,0x12);LCD_Write_Data(0x11,0x21);
  LCD_Write_Com(0x00,0x12);LCD_Write_Data(0x31,0x21);
  LCD_Write_Com(0x00,0x13);LCD_Write_Data(0x00,0x66);
  LCD_Write_Com(0x00,0x14);LCD_Write_Data(0x5F,0x60);
  // LCD_Write_Com(0x00,0x14);LCD_Write_Data(0x49,0x5f);
  LCD_Write_Com(0x00,0x30);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x31);LCD_Write_Data(0x00,0xdb);
  LCD_Write_Com(0x00,0x32);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x33);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x34);LCD_Write_Data(0x00,0xdb);
  LCD_Write_Com(0x00,0x35);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x36);LCD_Write_Data(0x00,0xAF);
  //LCD_Write_Com(0x00,0x36);LCD_Write_Data(0x00,0x0a);
  LCD_Write_Com(0x00,0x37);LCD_Write_Data(0x00,0x00);
  //LCD_Write_Com(0x00,0x37);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x38);LCD_Write_Data(0x00,0xDB);
 // LCD_Write_Com(0x00,0x38);LCD_Write_Data(0x00,0xdb);
  LCD_Write_Com(0x00,0x39);LCD_Write_Data(0x00,0x00);
 // LCD_Write_Com(0x00,0x39);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x50);LCD_Write_Data(0x04,0x00);
  LCD_Write_Com(0x00,0x51);LCD_Write_Data(0x06,0x0b);
  LCD_Write_Com(0x00,0x52);LCD_Write_Data(0x0c,0x0a);
  LCD_Write_Com(0x00,0x53);LCD_Write_Data(0x01,0x0A);
  LCD_Write_Com(0x00,0x54);LCD_Write_Data(0x0a,0x08);
  LCD_Write_Com(0x00,0x55);LCD_Write_Data(0x0b,0x08);
  LCD_Write_Com(0x00,0x56);LCD_Write_Data(0x00,0x00);
  LCD_Write_Com(0x00,0x57);LCD_Write_Data(0x0A,0x00);
  LCD_Write_Com(0x00,0x58);LCD_Write_Data(0x10,0x07);
  LCD_Write_Com(0x00,0x59);LCD_Write_Data(0x07,0x10);
    Delay(50);
  LCD_Write_Com(0x00,0x07);LCD_Write_Data(0x10,0x17);
    Delay(50);
  LCD_Write_Com(0x00,0x22);
}

void Address_set(unsigned int m_x1, unsigned int  m_y1, unsigned int m_x2, unsigned int m_y2) 
{ 
u16 x_start,y_start,x1,x2,y1,y2;
//转换坐标
x_start = 175-m_y1;//176
y_start = m_x1;

x1 = 175-m_y2;//176
y1 = m_x1;
x2 = 175-m_y1;//176
y2 = m_x2;

LCD_Write_Com(0x00, 0x20); LCD_Write_Data(x_start>> 8, x_start); //设置X坐标位置 
LCD_Write_Com(0x00, 0x21); LCD_Write_Data(y_start>> 8, y_start); //设置Y坐标位置 

LCD_Write_Com(0x00, 0x37); LCD_Write_Data(x1 >> 8, x1); //开始X 
LCD_Write_Com(0x00, 0x39); LCD_Write_Data(y1 >> 8, y1); //开始Y 
LCD_Write_Com(0x00, 0x36); LCD_Write_Data(x2 >> 8, x2); //结束X 
LCD_Write_Com(0x00, 0x38); LCD_Write_Data(y2 >> 8, y2); //结束Y 

LCD_Write_Com(0x00, 0x22); 
} 

void LCD_DrawPoint(u8 x,u8 y,u16 color)
{
u16 x_start,y_start;
SetCS(0); //打开片选使能 
x_start = 176-y;
y_start = x;
Address_set(x,y,x+1,y+1); 
LCD_Write_Data(color>>8, color); 
SetCS(1); //关闭片选使能 
}

void LCD_Pant(u16 color) 
{ 
int i, j; 
SetCS(0); //打开片选使能 
Address_set(0,0,219,175); //220 176
for(i = 0; i < 220; i++) 
{ 
for (j = 0; j < 176; j++) 
{ 
LCD_Write_Data(color>>8, color); 
} 
} 
SetCS(1); //关闭片选使能 
} 
/*
void LCD_Pic1(void)
{
u32 i=0; 
SetCS(0); //打开片选使能 
Address_set(0,0,220,176); 
for(i=0;i<38720;i++)LCD_Write_Data(gImage_1[2*i+1],gImage_1[2*i]); 
SetCS(1); //关闭片选使能 
}

void LCD_Pic2(void)
{
u32 i=0; 
SetCS(0); //打开片选使能 
Address_set(0,0,220,176); 
for(i=0;i<38720;i++)LCD_Write_Data(gImage_2[2*i+1],gImage_2[2*i]); 
SetCS(1); //关闭片选使能 
}

void LCD_Pic3(void)
{
u32 i=0; 
SetCS(0); //打开片选使能 
Address_set(0,0,220,176); 
for(i=0;i<38720;i++)LCD_Write_Data(gImage_3[2*i+1],gImage_3[2*i]); 
SetCS(1); //关闭片选使能 
}
*/

void LCD_DrawRectangle(u8 x1,u8 y1,u8 x2,u8 y2,u16 color)
{
int i, j; 
SetCS(0); //打开片选使能 
Address_set(x1,y1,x2,y2); 
for(i = x1; i <= x2; i++) 
{ 
for (j =y1; j <= y2; j++) 
{ 
LCD_Write_Data(color>>8, color); 
} 
}
SetCS(1); //关闭片选使能 
}
/*
void LCD_en(u8 x,u8 y,u8 ch,u16 ch_color,u16 bg_color)
{
 	u8 i,j,var0;
	u8* pic;
	ch-=32;
        u8 transparent=0;//应用上没用上
	pic=(u8*)CHARLIB[ch];
	SetCS(0); //打开片选使能 
	for(i=0;i<16;i++)
	{
      var0=*(pic+i);
	  for(j=0;j<8;j++)
	  {
		if((var0&(0x01<<j))!=0)
		{
		LCD_DrawPoint(x+j,y+i, ch_color);
		}
		else
		{
			if(transparent !=1)//transparent为1，透明
				{
				LCD_DrawPoint(x+j,y+i, bg_color);
				}
		}
	  }
	}
	SetCS(1); //关闭片选使能 
}
*/

void LCD_en(u8 x,u16 y,u8 ch,u16 ch_color,u16 bg_color)
{
 	u8 i,j,var0;
	u8* pic;
        u8 transparent=0;//应用上没用上
	ch-=32;
	pic=(u8*)CHARLIB[ch];
	SetCS(0); //打开片选使能 
	Address_set(x,y,(x+7),(y+15)); 
	for(i=0;i<16;i++)
	{
      var0=*(pic+i);
	  for(j=0;j<8;j++)
	  {
		if((var0&(0x01<<j))!=0)
		{
		LCD_Write_Data(ch_color>>8, ch_color); 
		}
		else
		{
		LCD_Write_Data(bg_color>>8, bg_color); 
		}
	  }
	}
	SetCS(1); //关闭片选使能 
}

void LCD_String(u8 x,u8 y,u8* ch,u16 ch_color,u16 bg_color)
{
    while((*ch)!='\0')
    	{
    	  LCD_en(x,y+1,*ch,ch_color,bg_color);
	      ch++;
	      x+=8;
    	}
}

void LCD_3g(u8 x,u8 y,u16 num,u16 ch_color,u16 bg_color)
{
 u8 temp[3],i=0;
 	if(num>32767)
	{
	num	=	65536-num;
	LCD_en(x,y,'-',ch_color,bg_color);
	}
	else
	{
	LCD_en(x,y,' ',ch_color,bg_color);
	}
   for(i=0;i<3;i++)
   	{
   	temp[i]=num%10+48;
	num/=10;
	}
   	if(temp[2]==48)LCD_en(x+8,y,' ',ch_color,bg_color); else LCD_en(x+8,y,temp[2],ch_color,bg_color);
	if((temp[1]==48)&&(temp[2]==48))LCD_en((x+16),y,' ',ch_color,bg_color); else LCD_en((x+16),y,temp[1],ch_color,bg_color);
	LCD_en((x+24),y,temp[0],ch_color,bg_color);
}

void LCD_5g(u16 x,u16 y,u32 num,u16 ch_color,u16 bg_color)
{
 	u8 temp[6],i=0,flag=0;
	u8 NumSign=0;	//0就是正，1就是负
 	if(num>2147483647)
	{
	num	=	4294967296-num;
	NumSign	=	1;
	}

   	for(i=0;i<5;i++)
   	{
   	temp[i]=num%10+48;
	num/=10;
	}
	
	temp[5]=' ';
	for(i=5;i>0;i--)
	{
		if((temp[i-1]!=48)&&(flag==0))
		{
		if(NumSign==1)temp[i]='-';
		flag=1;
		}
		else if((flag==0)&&(i>1))
		{
		temp[i-1]=' ';
		}
		else if(temp[0]==48)
		{
		temp[0]='0';
		}
	}

	LCD_en(x,y,temp[5],ch_color,bg_color);
	LCD_en((x+8),y,temp[4],ch_color,bg_color);
	LCD_en((x+16),y,temp[3],ch_color,bg_color);
	LCD_en((x+24),y,temp[2],ch_color,bg_color);
	LCD_en((x+32),y,temp[1],ch_color,bg_color);
	LCD_en((x+40),y,temp[0],ch_color,bg_color);
}

void LCD_8g(u16 x,u16 y,u32 num,u16 ch_color,u16 bg_color)
{
 	u8 temp[9],i=0,flag=0;
	u8 NumSign=0;	//0就是正，1就是负
 	if(num>2147483647)
	{
	num	=	4294967296-num;
	NumSign	=	1;
	}

   	for(i=0;i<8;i++)
   	{
   	temp[i]=num%10+48;
	num/=10;
	}
	
	temp[8]=' ';
	for(i=8;i>0;i--)
	{
		if((temp[i-1]!=48)&&(flag==0))
		{
		if(NumSign==1)temp[i]='-';
		flag=1;
		}
		else if((flag==0)&&(i>1))
		{
		temp[i-1]=' ';
		}
		else if(temp[0]==48)
		{
		temp[0]='0';
		}
	}
	LCD_en(x,y,temp[8],ch_color,bg_color);
   	LCD_en(x+8,y,temp[7],ch_color,bg_color);
	LCD_en((x+16),y,temp[6],ch_color,bg_color);
	LCD_en((x+24),y,temp[5],ch_color,bg_color);
	LCD_en((x+32),y,temp[4],ch_color,bg_color);
	LCD_en((x+40),y,temp[3],ch_color,bg_color);
	LCD_en((x+48),y,temp[2],ch_color,bg_color);
	LCD_en((x+56),y,temp[1],ch_color,bg_color);
	LCD_en((x+64),y,temp[0],ch_color,bg_color);
}

u8 g_RollLine=0;
u8 g_RollRow=0;//g_RollLine是行，g_RollRow是列
u8 g_FlashState=0;

void LCD_LineBreak(void)
{

	//行
	g_RollLine++;
	if(g_RollLine>10)
	{
	g_RollLine=0;
	g_FlashState=1;
	}
	//列
	g_RollRow=0;
	return 1;
}


void LCD_RollString(u8* ch,u16 ch_color,u16 bg_color,u8 linebreak)
{
    u8 x=0;
	  if(g_FlashState==1){LCD_Pant(bg_color);g_FlashState=0;}
    while((*ch)!='\0')
    	{
    	  LCD_en(g_RollRow,g_RollLine*16+1,*ch,ch_color,bg_color);
	      ch++;
	      g_RollRow+=8;
    	}
	if(linebreak==1)
		{
		LCD_LineBreak();
		}

}

void LCD_Roll5bit(u32 num,u16 ch_color,u16 bg_color,u8 linebreak)
{
 u8 temp[5],i=0;
   if(g_FlashState==1){LCD_Pant(bg_color);g_FlashState=0;}
   for(i=0;i<5;i++)
   	{
   	temp[i]=num%10+48;
	num/=10;
	}
   for(i=0;i<5;i++)
   	{
   	LCD_en(g_RollRow,g_RollLine*16+1,temp[4-i],ch_color,bg_color);
	g_RollRow+=8;
   	}
   if(linebreak==1)
   	{
   	LCD_LineBreak();
   	}
}

/*
void LCD_3g(u16 x,u16 y,u32 num,u16 ch_color,u16 bg_color)
{
 u8 temp[3],i=0;
 	if(num>32767)
	{
	num	=	65536-num;
	LCD_en(x,y,'-',ch_color,bg_color,0);
	}
	else
	{
	LCD_en(x,y,' ',ch_color,bg_color,0);
	}
   for(i=0;i<3;i++)
   	{
   	temp[i]=num%10+48;
	num/=10;
	}
   	LCD_en(x+8,y,temp[2],ch_color,bg_color, 0);
	LCD_en((x+16),y,temp[1],ch_color,bg_color, 0);
	LCD_en((x+24),y,temp[0],ch_color,bg_color, 0);

}
*/
#endif