/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp.c
* @author       liusen
* @version      V1.0
* @date         2015.01.03
* @brief        
* @details      
* @par History  
*                 
* version:	liusen_20170717
*/

#include "exti.h"
#include "ov7670.h"
#include "lcd.h"
#include "led.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
#include "bsp.h"
#include "stdio.h"
#include "OLED.h"


extern void NVIC_Configuration(void); 
void LCD_Init0(void);
void GPIO_UserInit(void);


/**
* Function       bsp_init
* @author        liusen
* @date          2015.01.03    
* @brief        
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History  
*/
void bsp_init(void)
{
	Colorful_GPIO_Init();//七彩灯初始化
	MOTOR_GPIO_Init();  				/*电机GPIO初始化*/
	Servo_GPIO_Init();				    /*舵机接口GPIO初始化*/	
	TIM1_Int_Init(9, 72);				/*100Khz的计数频率，计数到10为10us  */ 
	Ultrasonic_GPIO_Init();				/*超声波GPIO初始化*/
	bsp_Ultrasonic_Timer2_Init();		/*超声波TIM2初始化*/
	Uart1_init(115200);					/*调试接口串口 */
	Angle_J1 = 79;						/*初始化舵机�*/
	delay_init();
	ADC_GPIO_Init();
	Adc_Init();
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级	  
	while(OV7670_Init());//初始化OV7670		注意啦 当没有用到摄像头或者说摄像头没有安装的时候这句代码一定要注释掉，不然代码一直在这里初始化						  
	EXTI8_Init();						//使能定时器捕获
  OV7670_CS=0;			
	config_ov7670_OutPut(20,60,320,240,1);//设置摄像头模式以及摄像头采集的图像大小
	GPIO_UserInit();//OLED引脚初始化
	LCD_Init0();//OLED初始化
	Uart2_init(9600);
	Start_init();
}
