#ifndef __OLED_H
#define __OLED_H

#include "REG51.h"		  	 


//设置横屏或者竖屏显示 0   正向显示
//                     90  旋转90度显示
//                     180 旋转90度显示
//                     270 旋转270度显示

#define USE_HORIZONTAL 0

#if USE_HORIZONTAL==0||USE_HORIZONTAL==180 //竖屏显示
#define oled_x  64
#define oled_y  16
#else                                      //横屏显示
#define oled_x  128
#define oled_y  8
#endif



#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int
	
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

sbit OLED_SCL=P1^0;//SCL
sbit OLED_SDA=P1^1;//SDA
sbit OLED_RES =P1^2;//RES
sbit OLED_DC =P1^3;//DC
sbit OLED_CS=P1^4; //CS

//-----------------OLED端口定义----------------

#define OLED_SCL_Clr() OLED_SCL=0
#define OLED_SCL_Set() OLED_SCL=1

#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1

#define OLED_RES_Clr() OLED_RES=0
#define OLED_RES_Set() OLED_RES=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1


//OLED控制用函数
void delay_ms(unsigned int ms);
void OLED_ColorTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey);
u32 oled_pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey);
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey);
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[]);
void OLED_Init(void);

#endif  
	 



