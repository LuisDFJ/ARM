#define STM32F767xx
#include "stm32f7xx.h"
#include <stdint.h>

void delay(uint32_t ticks){
    for(uint32_t i = 0; i<ticks ; i++);
}

int main(void)
{
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB -> MODER |= GPIO_MODER_MODER7_0;
	GPIOB -> OTYPER &= ~(GPIO_OTYPER_OT7);
	GPIOB -> OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR7);
	GPIOB -> PUPDR &= ~(GPIO_PUPDR_PUPDR7);
	
	

    while (1)
    {
        asm("mov r4,r3");
        GPIOB -> BSRR |= 0x1<<7;
        delay(200000);
        GPIOB -> BSRR |= 0x1<<(7+16);
        delay(200000);

    }
    return 0;
}