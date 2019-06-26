#include "bsp.h"

/*************定义所使用的IO口**************/
#define RCC_LED 	RCC_APB2Periph_GPIOB

/**************8位LED的IO口定义************/
#define PIN_KEY (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
/**************8位KEY的IO口定义************/
#define PIN_LED (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)

void LED_Init(void)
{
/*********定义一个GPIO_InitTypeDef 类型的结构体**********/
	GPIO_InitTypeDef GPIO_InitStructure;

/*********选择要控制的GPIOx的引脚**********/
	GPIO_InitStructure.GPIO_Pin = PIN_LED;

/*********设置引脚速率为50MHZ**********/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

/*********设置引脚模式为通用推完输出**********/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
/*打开LED使用的GPIO的时钟使能*/
	RCC_APB2PeriphClockCmd(RCC_LED, ENABLE);

/*初始化相应的GPIO*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void KEY_Init(void)
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=PIN_KEY;	 //定义所有管脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50M翻转速度
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/****************************************************************************
* Function Name  : LED_Sets
* Description    : 设置LED的状态：因我们只是用了8位，而STM32一次得设置16位，所
*以先读取在写入。
* Input          : data 
* Output         : None
* Return         : None
****************************************************************************/

void LED_Sets(uint8_t k)
{
	uint16_t setValue;

	setValue = GPIO_ReadOutputData(GPIOB)&0x00ff;		  //我们的LED使用的是16位中的高8位；即高八位清零，低八位不变					
	setValue |= (uint16_t)(1<<(k%8)) << 8;

	GPIO_Write(GPIOB,setValue);
}

uint8_t last_state=0x00;
uint8_t KEY_Gets()
{
	uint8_t value = (uint8_t)(GPIO_ReadInputData(GPIOB)&0x00f0);
	uint8_t jump = (last_state^value)&value;
	last_state = value;
	return jump;
}

void BSP_Init()
{
	LED_Init();
	KEY_Init();
}
