#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H	
#include "stm32f10x.h" 
void  Temperature_Configuration(void); //初始化内部温度
u16 Get_Temperature_Numerical(void);//获得内部温度的值
#endif 
