//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              SCL  P10��SCL��
//              SDA  P11��SDA��

//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/
#include "REG51.h"
#include "oled.h"
#include "bmp.h"

int main(void)
{	
	u8 t=' ';
	OLED_Init();//��ʼ��OLED
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
	while(1) 
	{		
		OLED_DrawBMP(0,0,64,128,BMP1);
		delay_ms(500);
		OLED_Clear();
    OLED_ShowChinese(8,0,0,16);//��
		OLED_ShowChinese(24,0,1,16);//��
		OLED_ShowChinese(40,0,2,16);//԰
		OLED_ShowChinese(0,2,3,16);//��
		OLED_ShowChinese(16,2,4,16);//��
		OLED_ShowChinese(32,2,5,16);//��
		OLED_ShowChinese(48,2,6,16);//��
		OLED_ShowString(0,4,"ZJY OLED",16);
		
		OLED_ShowString(0,6,"ASCII:",16);
		OLED_ShowString(0,8,"CODE:",16);
		OLED_ShowChar(48,6,t,16);//��ʾASCII�ַ�	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(40,8,t,3,16);
		delay_ms(500);
		OLED_Clear();
	}
}

	