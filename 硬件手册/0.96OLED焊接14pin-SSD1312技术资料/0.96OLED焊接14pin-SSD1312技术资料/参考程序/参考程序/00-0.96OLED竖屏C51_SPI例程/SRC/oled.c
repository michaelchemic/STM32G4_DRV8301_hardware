#include "oled.h"
#include "oledfont.h"  	 
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
void delay_ms(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}

//���Ժ���
void OLED_ColorTurn(u8 i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xA6,OLED_CMD);//������ʾ
		}
	if(i==1)
		{
			OLED_WR_Byte(0xA7,OLED_CMD);//��ɫ��ʾ
		}
}


//��ʱ
void IIC_delay(void)
{
	u8 t=1;
	while(t--);
}

//��ʼ�ź�
void I2C_Start(void)
{
	OLED_SDA_Set();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SDA_Clr();
	IIC_delay();
	OLED_SCL_Clr();
	 
}

//�����ź�
void I2C_Stop(void)
{
	OLED_SDA_Clr();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SDA_Set();
}

//�ȴ��ź���Ӧ
void I2C_WaitAck(void) //�������źŵĵ�ƽ
{
	OLED_SDA_Set();
	IIC_delay();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SCL_Clr();
	IIC_delay();
}

//д��һ���ֽ�
void Send_Byte(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		OLED_SCL_Clr();//��ʱ���ź�����Ϊ�͵�ƽ
		if(dat&0x80)//��dat��8λ�����λ����д��
		{
			OLED_SDA_Set();
    }
		else
		{
			OLED_SDA_Clr();
    }
		IIC_delay();
		OLED_SCL_Set();
		IIC_delay();
		OLED_SCL_Clr();
		dat<<=1;
  }
}

//����һ���ֽ�
//��SSD1306д��һ���ֽڡ�
//mode:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat,u8 mode)
{
	I2C_Start();
	Send_Byte(0x78);
	I2C_WaitAck();
	if(mode){Send_Byte(0x40);}
  else{Send_Byte(0x00);}
	I2C_WaitAck();
	Send_Byte(dat);
	I2C_WaitAck();
	I2C_Stop();
}

//��������

void OLED_Set_Pos(u8 x, u8 y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<oled_y;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<oled_x;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63				 
//sizey:ѡ������ 6x8  8x16
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey)
{      	
	u8 c=0,sizex=sizey/2;
	u16 i=0,size1;
	if(sizey==8)size1=6;
	else size1=(sizey/8+((sizey%8)?1:0))*(sizey/2);
	c=chr-' ';//�õ�ƫ�ƺ��ֵ
	OLED_Set_Pos(x,y);
	for(i=0;i<size1;i++)
	{
		if(i%sizex==0&&sizey!=8) OLED_Set_Pos(x,y++);
		if(sizey==8) OLED_WR_Byte(asc2_0806[c][i],OLED_DATA);//6X8�ֺ�
		else if(sizey==16) OLED_WR_Byte(asc2_1608[c][i],OLED_DATA);//8x16�ֺ�
//		else if(sizey==xx) OLED_WR_Byte(asc2_xxxx[c][i],OLED_DATA);//�û�����ֺ�
		else return;
	}
}
//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ����
//x,y :�������
//num:Ҫ��ʾ������
//len :���ֵ�λ��
//sizey:�����С		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey)
{         	
	u8 t,temp,m=0;
	u8 enshow=0;
	if(sizey==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(sizey/2+m)*t,y,' ',sizey);
				continue;
			}else enshow=1;
		}
	 	OLED_ShowChar(x+(sizey/2+m)*t,y,temp+'0',sizey);
	}
}
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey)
{
	u8 j=0;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j++],sizey);
		if(sizey==8)x+=6;
		else x+=sizey/2;
	}
}
//��ʾ����
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey)
{
	u16 i,size1=(sizey/8+((sizey%8)?1:0))*sizey;
	for(i=0;i<size1;i++)
	{
		if(i%sizey==0) OLED_Set_Pos(x,y++);
		if(sizey==16) OLED_WR_Byte(Hzk[no][i],OLED_DATA);//16x16�ֺ�
//		else if(sizey==xx) OLED_WR_Byte(xxx[c][i],OLED_DATA);//�û�����ֺ�
		else return;
	}				
}


//��ʾͼƬ
//x,y��ʾ����
//sizex,sizey,ͼƬ����
//BMP��Ҫ��ʾ��ͼƬ
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[])
{ 	
  u16 j=0;
	u8 i,m;
	sizey=sizey/8+((sizey%8)?1:0);
	for(i=0;i<sizey;i++)
	{
		OLED_Set_Pos(x,i+y);
    for(m=0;m<sizex;m++)
		{      
			OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
		}
	}
} 



//��ʼ��				    
void OLED_Init(void)
{
	OLED_RES_Clr();
  delay_ms(10);
	OLED_RES_Set();
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	
	OLED_WR_Byte(0x00,OLED_CMD);    /*set lower column address*/       
	OLED_WR_Byte(0x10,OLED_CMD);    /*set higher column address*/

	OLED_WR_Byte(0xB0,OLED_CMD);    /*set page address*/

	OLED_WR_Byte(0x81,OLED_CMD);    /*contract control*/
	OLED_WR_Byte(0x5f,OLED_CMD);    /*128*/
	
	if(USE_HORIZONTAL==0)
	{
		OLED_WR_Byte(0x20,OLED_CMD);    /* Set Memory addressing mode (0x20/0x21) */
		OLED_WR_Byte(0x09,OLED_CMD);     /* 0x09 */

		OLED_WR_Byte(0xA1,OLED_CMD);    /*set segment remap  0XA1 */
		OLED_WR_Byte(0xC8,OLED_CMD);    /*Com scan direction   0Xc8  */
	}
	else if(USE_HORIZONTAL==90)
	{
		OLED_WR_Byte(0x20,OLED_CMD);    /* Set Memory addressing mode (0x20/0x21) */
		OLED_WR_Byte(0x02,OLED_CMD);     /* 0x02 */

		OLED_WR_Byte(0xA1,OLED_CMD);    /*set segment remap  0XA1 */
		OLED_WR_Byte(0xC0,OLED_CMD);    /*Com scan direction   0Xc0  */
	}
	else if(USE_HORIZONTAL==180)
	{
		OLED_WR_Byte(0x20,OLED_CMD);    /* Set Memory addressing mode (0x20/0x21) */
		OLED_WR_Byte(0x09,OLED_CMD);     /* 0x09 */

		OLED_WR_Byte(0xA0,OLED_CMD);    /*set segment remap  0XA0 */
		OLED_WR_Byte(0xC0,OLED_CMD);    /*Com scan direction   0Xc0  */
	}
	else if(USE_HORIZONTAL==270)
	{
		OLED_WR_Byte(0x20,OLED_CMD);    /* Set Memory addressing mode (0x20/0x21) */
		OLED_WR_Byte(0x02,OLED_CMD);     /* 0x02 */

		OLED_WR_Byte(0xA0,OLED_CMD);    /*set segment remap  0XA0 */
		OLED_WR_Byte(0xC8,OLED_CMD);    /*Com scan direction   0Xc8  */
	}
	
	OLED_WR_Byte(0xA4,OLED_CMD);    /*Disable Entire Display On (0xA4/0xA5)*/ 

	OLED_WR_Byte(0xA6,OLED_CMD);    /*normal / reverse*/

	OLED_WR_Byte(0xA8,OLED_CMD);    /*multiplex ratio*/
	OLED_WR_Byte(0x3F,OLED_CMD);    /*duty = 1/64*/

	OLED_WR_Byte(0xD3,OLED_CMD);    /*set display offset*/
	OLED_WR_Byte(0x00,OLED_CMD);    /*   0x20   */

	OLED_WR_Byte(0xD5,OLED_CMD);    /*set osc division*/
	OLED_WR_Byte(0x80,OLED_CMD);    

	OLED_WR_Byte(0xD9,OLED_CMD);    /*set pre-charge period*/
	OLED_WR_Byte(0x22,OLED_CMD);

	OLED_WR_Byte(0xDA,OLED_CMD);    /* Set SEG Pins Hardware Configuration */
	OLED_WR_Byte(0x10,OLED_CMD);

	OLED_WR_Byte(0xdb,OLED_CMD);    /*set vcomh*/
	OLED_WR_Byte(0x30,OLED_CMD);

	OLED_WR_Byte(0x8d,OLED_CMD);    /*set charge pump enable*/
	OLED_WR_Byte(0x72,OLED_CMD);    /* 0x12:7.5V; 0x52:8V;  0x72:9V;  0x92:10V */
	OLED_Clear();
	OLED_WR_Byte(0xAF,OLED_CMD);
}




