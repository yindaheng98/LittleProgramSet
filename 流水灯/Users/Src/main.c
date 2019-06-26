#include"stm32f10x.h"
#include"bsp.h"
#include"ucos_ii.h"

#define STARTUP_TASK_PRIO 4
#define STARTUP_TASK_STK_SIZE 80

static void SystickInit()
{
	RCC_ClocksTypeDef  rcc_clocks;  
  RCC_GetClocksFreq(&rcc_clocks);
  SysTick_Config(rcc_clocks.HCLK_Frequency / OS_TICKS_PER_SEC);
}

uint8_t isflow=0;
uint8_t speed=0;
void LED_flow()
{
	uint8_t count = 0;
	SystickInit();
	while(1)
	{
		if(isflow%2==0)
			LED_Sets(count++);
		//OSTimeDlyHMSM(0,0,speed%3+1,0);//ͨ��ʱ������������ӳ�
		OSTimeDlyHMSM(0,0,speed%3+1,0);
	}
}

void LED_change()
{
	uint8_t value=0x00;
	SystickInit();
	while(1)
	{
		value=KEY_Gets();
		if(value&0x80)
			isflow+=1;
		if(value&0x40)
			speed+=1;
		OSTimeDlyHMSM(0,0,0,10);//ͨ��ʱ������������ӳ�
	}
}

static OS_STK task_LED_flow[STARTUP_TASK_STK_SIZE];
static OS_STK task_LED_change[STARTUP_TASK_STK_SIZE];

int main(void)
{
	/**********��IOʱ�Ӻͳ�ʼ��GPIO**********/
	BSP_Init();
	OSInit();
	OSTaskCreate(LED_flow,(void *)0,&task_LED_flow[STARTUP_TASK_STK_SIZE-1],STARTUP_TASK_PRIO);
	OSTaskCreate(LED_change,(void *)0,&task_LED_change[STARTUP_TASK_STK_SIZE-1],STARTUP_TASK_PRIO-1);
	OSStart();
	/*
	uint8_t value=0x00;
	while(1)
	{
		value=KEY_Gets();
		GPIO_Write(GPIOB,(((uint16_t)value)<<8)+0x00ff);
	}
	*/
}
