#ifndef __BSP_H_
#define __BSP_H_

#include"stm32f10x.h"

/**********��IOʱ�Ӻͳ�ʼ��GPIO**********/
void BSP_Init(void);

/**********���ð�λLED��״̬***************/
void LED_Sets(uint8_t k);

/**********��ȡ��λKEY��״̬***************/
uint8_t KEY_Gets(void);
#endif
