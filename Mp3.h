#ifndef _MP3_HEAD_
 #define _MP3_HEAD_
  #include "I2C_Soft.h"
    unsigned char g_cReceBuf[10];
    unsigned char td;
    unsigned int wiredata;
   void play(void)
	{
 	 Soft_I2C_Start();
     	 Soft_I2C_Write(0x86);
	 Soft_I2C_Write(0x50);
	 Soft_I2C_Write(0x01);
 	 Soft_I2C_Stop();
	}
    void stop(void)
	{
 	 Soft_I2C_Start();
     	 Soft_I2C_Write(0x86);
	 Soft_I2C_Write(0x50);
	 Soft_I2C_Write(0x03);
 	 Soft_I2C_Stop();
	}
    void send_command2(unsigned char ta,unsigned char tb)
	{
 	 Soft_I2C_Start();
	 Soft_I2C_Write(0x86);	//写入模块地址 写
	 Soft_I2C_Write(ta);	//read_command
	 Soft_I2C_Write(tb);
 	 Soft_I2C_Stop(); 	 
	}
    void send_command4(unsigned char ta,unsigned char tb,unsigned char tc,unsigned char td)
	{	 
 	 Soft_I2C_Start();
	 Soft_I2C_Write(0x86);	//写入模块地址 写
	 Soft_I2C_Write(ta);	//read_command
	 Soft_I2C_Write(tb);
	 Soft_I2C_Write(tc);
	 Soft_I2C_Write(td);
 	 Soft_I2C_Stop(); 	 
	}
     void get_data(unsigned char tc)
	{
	 Soft_I2C_Start();
	 Soft_I2C_Write(0x87);
	 for(td=1;td<tc;td++)	
	 {
	  g_cReceBuf[td]=Soft_I2C_Read(0);
	 }
	 g_cReceBuf[td]=Soft_I2C_Read(1); 
	 Soft_I2C_Stop();
	}
   void DELAY()
  {
       for(wiredata=0;wiredata<12000;wiredata++)
      {
          Soft_I2C_Delayxd();
      }
  }  
#endif