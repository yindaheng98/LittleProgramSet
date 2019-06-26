#ifndef __BSP_H_
#define __BSP_H_

#include"stm32f10x.h"

/**********打开IO时钟和初始化GPIO**********/
void BSP_Init(void);

/**********设置八位LED的状态***************/
void LED_Sets(uint8_t k);

/**********获取八位KEY的状态***************/
uint8_t KEY_Gets(void);
#endif
