//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-03-29
//  ����޸�   : 
//  ��������   : OLED I2C�ӿ���ʾ����(STM32F0ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              SCL   PA0��SCL��
//              SDA   PA1��SDA��

// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018/3/16
//All rights reserved
//******************************************************************************/
#include "stm32f0xx.h"
#include "delay.h"
#include "oled.h"
#include "bmp.h"


int main(void)
{
	u8 t=' ';
  delay_init();
  OLED_Init();
  while (1)
  {
		OLED_ShowPicture(0,0,64,128,BMP1,1);
		OLED_Refresh();
		delay_ms(500);
		OLED_Clear();
    OLED_ShowChinese(8,0,0,16,1);//��
		OLED_ShowChinese(24,0,1,16,1);//��
		OLED_ShowChinese(40,0,2,16,1);//԰
		OLED_ShowChinese(0,16,3,16,1);//��
		OLED_ShowChinese(16,16,4,16,1);//��
		OLED_ShowChinese(32,16,5,16,1);//��
		OLED_ShowChinese(48,16,6,16,1);//��
		OLED_ShowString(0,32,"ZJY OLED",16,1);
		
		OLED_ShowString(0,48,"ASCII:",16,1);
		OLED_ShowString(0,64,"CODE:",16,1);
		OLED_ShowChar(48,48,t,16,1);//��ʾASCII�ַ�	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(40,64,t,3,16,1);
		
		OLED_ShowChinese(0,80,0,16,1);//16*16 ��
   	OLED_ShowChinese(20,80,0,24,1);//24*24 ��

		OLED_ShowString(0,104,"A",24,1);//6*12 ��ABC��
		OLED_ShowString(28,110,"B",16,1);//8*16 ��ABC��
		OLED_ShowString(44,113,"C",12,1);//12*24 ��ABC��
	  OLED_Refresh();
		delay_ms(500);
		OLED_ScrollDisplay(11,4,1);
	}
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
