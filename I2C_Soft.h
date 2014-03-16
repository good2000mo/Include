#ifndef _I2C_SOFT_
 #define _I2C_SOFT_

 u32 SDA_PORT;
 u8 SDA_BIT;
 u32 SCL_PORT;
 u8 SCL_BIT;

 unsigned char I2C_SPEED;
 unsigned char pic_iic;
 #define Set_SDA_DDR GPIO_Setting((GPIO_TypeDef*)SDA_PORT,SDA_BIT,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL);
 #define Cls_SDA_DDR GPIO_Setting((GPIO_TypeDef*)SDA_PORT,SDA_BIT,GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_NOPULL)
 #define Set_SDA     GPIO_SetBits((GPIO_TypeDef*)SDA_PORT,(1<<SDA_BIT))
 #define Cls_SDA     GPIO_ResetBits((GPIO_TypeDef*)SDA_PORT,(1<<SDA_BIT))
 #define SDA_High    GPIO_ReadInputDataBit((GPIO_TypeDef*)SDA_PORT,(1<<SDA_BIT))
 #define SCL_High    GPIO_ReadInputDataBit((GPIO_TypeDef*)SCL_PORT,(1<<SCL_BIT))
 #define Set_SCL_DDR GPIO_Setting((GPIO_TypeDef*)SCL_PORT,SCL_BIT,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL)
 #define Cls_SCL_DDR GPIO_Setting((GPIO_TypeDef*)SCL_PORT,SCL_BIT,GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_NOPULL)
 #define Set_SCL     GPIO_SetBits((GPIO_TypeDef*)SCL_PORT,(1<<SCL_BIT))
 #define Cls_SCL     GPIO_ResetBits((GPIO_TypeDef*)SCL_PORT,(1<<SCL_BIT))

  static void Soft_I2C_Delay(void){
  volatile unsigned int ri;
   for( ri=0; ri<35; ri++ );
   if(pic_iic==1)for( ri=0; ri<35; ri++ );
 }
 
 /*
 void test_iic(void)
{
	unsigned char po=1;
	if(po==1)
	{
	SDA_BIT=7;
    SCL_BIT=9;
	Set_SDA_DDR;
    Set_SCL_DDR;
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, (1<<5) );
	po=0;

	}
	SDA_BIT=7;
    SCL_BIT=9;
	Set_SCL;
	Set_SDA;
	AT91F_PIO_SetOutput( AT91C_BASE_PIOA, (1<<5) );
	Soft_I2C_Delay();
	Cls_SDA;
	Cls_SCL;
	AT91F_PIO_ClearOutput( AT91C_BASE_PIOA, (1<<5) );
	Soft_I2C_Delay();
}
*/
 
 void Soft_I2C_Delayxd(void){
   int xri;
   for( xri=0; xri<2000; xri++ );
 }
 void Soft_I2C_Start(void){ 
   Set_SDA_DDR;
   Set_SCL_DDR;   
   Set_SDA;  
   Set_SCL;
   Soft_I2C_Delay();  
   Set_SCL;
   Soft_I2C_Delay();
   Cls_SDA;
   Soft_I2C_Delay();
   Cls_SCL;
   Soft_I2C_Delay();
 }
 
 void Soft_I2C_Stop(void){
   Set_SDA_DDR;
   Set_SCL_DDR;
   Cls_SDA;
   Soft_I2C_Delay();
   Set_SCL;
   Soft_I2C_Delay();
   Set_SDA;
   Soft_I2C_Delay();
 }
 
 unsigned char Soft_I2C_Write(unsigned char wb){
   unsigned char ack=0;
   int i;
   Set_SDA_DDR;
   Set_SCL_DDR;  
   for(i=0;i<8;i++){
     if( wb&0x80 ) {Set_SDA;}
     else {Cls_SDA;}
     wb=wb<<1;
     Soft_I2C_Delay();
     Set_SCL;
     Soft_I2C_Delay();
     Cls_SCL;
   }
   Cls_SDA_DDR;                                // releast data line
   Set_SDA;                                    // pull up for check
   Soft_I2C_Delay();
   Set_SCL;
   Soft_I2C_Delay();  
   if(SDA_High)ack=0;
   else ack=1;  
   Cls_SCL;
   Soft_I2C_Delay();
   return ack;    
 }
 
 unsigned char Soft_I2C_Read(unsigned char bEnd){
   unsigned char i,mb;
   mb=0;
   Cls_SDA_DDR;
   Set_SDA; 
   Set_SCL_DDR;    
   for(i=0;i<8;i++){
// for(i=0x80;i>0;i>>=1){
     Soft_I2C_Delay();
     Cls_SCL;
     Soft_I2C_Delay();
 	 Set_SCL;
//   Soft_I2C_Delay();
     mb=mb<<1;	
     if( SDA_High )
       mb++;
//   if( SDA_High ) mb|=i;
   }
   Soft_I2C_Delay();  
   Cls_SCL;  
   Set_SDA_DDR;  
   if( bEnd )
     {Set_SDA;}
   else
     {Cls_SDA;}
   Soft_I2C_Delay();
   Set_SCL;
   Soft_I2C_Delay();
   Cls_SCL;
   Soft_I2C_Delay();
   return mb;
 }

unsigned char Soft_I2C_ReadSlaver(unsigned char sbEnd){
   unsigned char j,sb;
   sb=0;
   Cls_SDA_DDR;
  Set_SDA; 
   Cls_SCL_DDR;
  Set_SCL;     
   for(j=0;j<8;j++){
    if(!SCL_High)
   {
 Soft_I2C_Delayxd();
 while(!SCL_High);
Soft_I2C_Delayxd();
   }
    
     sb<<=1;	
     if( SDA_High )
       sb++;
if(SCL_High)
  {    
     Soft_I2C_Delayxd();
   while(SCL_High);
Soft_I2C_Delayxd();
   }
 }
  

  if(!SCL_High)
   {
 Soft_I2C_Delayxd();
 while(!SCL_High);
Soft_I2C_Delayxd();
   }
   if( sbEnd )
    { Set_SDA;}
   else
     {Cls_SDA; } 
   Set_SDA_DDR; 
if(SCL_High)
  {    
     Soft_I2C_Delayxd();
   while(SCL_High);
Soft_I2C_Delayxd();
   } 
 Cls_SDA_DDR;
 Set_SDA;
  Soft_I2C_Delayxd();
   return sb;
 }
#endif
