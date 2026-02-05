/******************** ��ѧ�Ƽ� **************************
 * ʵ��ƽ̨��������STM32������
 * ��汾  ��ST3.5.0
 * ����    ����ѧ�Ƽ��Ŷ� 
 * �Ա�    ��http://shop102218275.taobao.com/
 * ������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
 *��Ȩ���У�����ؾ���
**********************************************************************************/
#include "usart1.h"
#include "lcd.h"
#include "text.h"

#include "temperature.h"
#include "delay.h"
int main(void)
{
   u16 temp;
   float temp_value;
	 float temperate;
	 char msg[15];
	
   USART1_Config();
   Temperature_Adc_Init();//��ʼ��
	 POINT_COLOR=BLUE;
   USART1_Config();	 
	 LCD_Init();
   LCD_Clear(WHITE);
	 LCD_ShowString(30,50,"Building Electricity",POINT_COLOR);	
   LCD_ShowString(30,70,"& Intelligence 1501",POINT_COLOR);	
	 LCD_ShowString(30,90,"2105150225",POINT_COLOR);	
	 LCD_ShowString(30,110,"ZhuFangJun",POINT_COLOR);
  
   while(1)
   {
    temp=Get_Temperature_value();//�õ��ڲ��¶ȵ���������ֵ
	  temperate=temp*(3.3/4095);//�����¶ȴ������ĵ�ѹֵ
    temp_value=(1.43-temperate)/0.0043+25;	//�õ�оƬ�ڲ����¶�
		Delay(50000);
    sprintf(msg,"Temperate=%7.3f",temp_value);
		LCD_ShowString(30,160,msg,RED);
   }
}	