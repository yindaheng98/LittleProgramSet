#include "bsp.h"

/*************������ʹ�õ�IO��**************/
#define RCC_LED 	RCC_APB2Periph_GPIOB

/**************8λLED��IO�ڶ���************/
#define PIN_KEY (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
/**************8λKEY��IO�ڶ���************/
#define PIN_LED (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)

void LED_Init(void)
{
/*********����һ��GPIO_InitTypeDef ���͵Ľṹ��**********/
	GPIO_InitTypeDef GPIO_InitStructure;

/*********ѡ��Ҫ���Ƶ�GPIOx������**********/
	GPIO_InitStructure.GPIO_Pin = PIN_LED;

/*********������������Ϊ50MHZ**********/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

/*********��������ģʽΪͨ���������**********/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
/*��LEDʹ�õ�GPIO��ʱ��ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_LED, ENABLE);

/*��ʼ����Ӧ��GPIO*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void KEY_Init(void)
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=PIN_KEY;	 //�������йܽ�
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50M��ת�ٶ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/****************************************************************************
* Function Name  : LED_Sets
* Description    : ����LED��״̬��������ֻ������8λ����STM32һ�ε�����16λ����
*���ȶ�ȡ��д�롣
* Input          : data 
* Output         : None
* Return         : None
****************************************************************************/

void LED_Sets(uint8_t k)
{
	uint16_t setValue;

	setValue = GPIO_ReadOutputData(GPIOB)&0x00ff;		  //���ǵ�LEDʹ�õ���16λ�еĸ�8λ�����߰�λ���㣬�Ͱ�λ����					
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
