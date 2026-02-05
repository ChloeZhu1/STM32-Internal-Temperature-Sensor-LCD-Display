#include "temperature.h"
void  Temperature_Adc_Init(void)//初始化内部温度
{ 	
   
	ADC_InitTypeDef ADC_InitStructure; 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );//开启ADC1通道时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //配置ADC时钟，为PCLK2的6分频，即12Hz

	ADC_DeInit(ADC1);  //复位ADC1
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//独立ADC模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//禁止扫描模式，扫描模式用于多通道采集,设置ADC转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件触发启动,不使用外部触发转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//要转换的通道数目1
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
    ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_55Cycles5);	//配置ADC1的通道16为55.5个采样周期，序列为1
	ADC_Cmd(ADC1, ENABLE);	//使能ADC1
    ADC_TempSensorVrefintCmd(ENABLE); //开启内部温度传感器
	ADC_ResetCalibration(ADC1);//复位校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));//等待校准寄存器复位完成
	ADC_StartCalibration(ADC1);//开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));//等待校准完成
}





//获得内部温度的值	
u16 Get_Temperature_value(void)
{
    u8 i;
	u32 Adc_value=0;//存储内部温度的值
	 for(i=0;i<19;i++)
	 {
	 	ADC_SoftwareStartConvCmd(ADC1,ENABLE);// 软件转换启动ADC开始转换
		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换完成
		Adc_value+=ADC_GetConversionValue(ADC1);//	得到转换以后的值
	 }
	return Adc_value/20; //经过滤波返回得到内部温度的值	
}
 	 










