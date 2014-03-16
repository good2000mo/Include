#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_  1

#include "stm32f2xx_conf.h"
/*
#define FLASH_CHREAD 0x0B
#define FLASH_CLREAD 0x03
#define FLASH_PREAD	0xD2

#define FLASH_BUFWRITE1 0x84
#define FLASH_IDREAD 0x9F
#define FLASH_STATUS 0xD7
#define PAGE_ERASE 0x81
#define PAGE_READ 0xD2
#define MM_PAGE_TO_B1_XFER 0x53				// 将主存储器的指定页数据加载到第一缓冲区
#define BUFFER_2_WRITE 0x87					// 写入第二缓冲区
#define B2_TO_MM_PAGE_PROG_WITH_ERASE 0x86	// 将第二缓冲区的数据写入主存储器（擦除模式）
*/
//Dataflash指令表
#define Cmd_DF_PageRead           0xD2
#define Cmd_DF_Buffer1Read      0xD1
#define Cmd_DF_Buffer2Read      0xD3
#define Cmd_DF_WriteBuffer1      0x84
#define Cmd_DF_WriteBuffer2      0x87
#define Cmd_DF_Buffer1ToPage  0x83
#define Cmd_DF_Buffer2ToPage  0x86
#define Cmd_DF_PageErase          0x81
#define Cmd_DF_BlockErase          0x50        
#define Cmd_DF_SectorErase        0x7C 
#define Cmd_DF_AllErase               0xC7          
#define Cmd_DF_ReadState           0xD7
#define Cmd_DF_ReadID                0x9F


#define Dummy_Byte 0xFF

/* Select SPI FLASH: ChipSelect pin low  */
#define Select_Flash()      GPIO_ResetBits(GPIOB,GPIO_Pin_12)
/* Deselect SPI FLASH: ChipSelect pin high */
#define NotSelect_Flash()    GPIO_SetBits(GPIOB,GPIO_Pin_12)

void sFlash_Init(void);	//SPI初始化
u8 sFlash_ReadByte(void);		//flash操作基本函数，读一个字节
u8 sFlash_SendByte(u8 byte);		//	FLASH操作基本函数，发送一个字节
void sFlashPageEarse(u16 page);	//擦除指定的页,页范围0-4095

void sFlashPageRead(u16 page,u8 *Data);		//读取整页，页范围0-4095
void sFlashPageWrite1(u16 page,u8 *Data);		//写一整页，页范围0-4095
void sFlashPageWrite2(u16 page, u8 * Data);

void sFlashWaitBusy(void);			//Flash忙检测
void sFlashReadID(u8 *ProdustID);		//读取flashID四个字节
u8 sFlashReadState(void);	
void sFlashModity512bytes(void);
void sFlashMultiRead(u8 *buf,u32 addr,u16 page_len);
#endif
