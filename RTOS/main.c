#define     STM32F767xx
#define     NUM_TASKS       3
#define     SIZE_STACK      64

#include    "RTOS.h"
#include    <stdint.h>

//uint32_t    completed   =   0;
//uint8_t flag2   =   1;
//uint8_t flag1   =   1;
//extern  uint32_t tickCounter;
/*
void delay1(uint32_t counts){
    uint32_t i;
    for (i = 0 ; i < counts ; i++ )
    {

    }
    asm("bkpt");
}
*/
/*
void delay2(uint32_t counts){
    uint32_t i;
    for (i = 0 ; i < counts ; i++ );
}
*/

void task3(void)
{
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB -> MODER |= GPIO_MODER_MODER0_0;
	GPIOB -> OTYPER &= ~(GPIO_OTYPER_OT0);
	GPIOB -> OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0);
	GPIOB -> PUPDR &= ~(GPIO_PUPDR_PUPDR0);
	static uint32_t i;
    while(1)
    {
        GPIOB -> BSRR |= 0x1;
        for (i = 0 ; i < 100000 ; i++ );
        
        GPIOB -> BSRR |= 0x1<<(16);
        for (i = 0 ; i < 100000 ; i++ );
    }
}


void task2(void)
{
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB -> MODER |= GPIO_MODER_MODER7_0;
	GPIOB -> OTYPER &= ~(GPIO_OTYPER_OT7);
	GPIOB -> OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR7);
	GPIOB -> PUPDR &= ~(GPIO_PUPDR_PUPDR7);
	static uint32_t i;
    while(1)
    {
        //asm("BKPT");
        GPIOB -> BSRR |= 0x1<<7;
        for (i = 0 ; i < 200000 ; i++ );
        //delay1(2000000);
        GPIOB -> BSRR |= 0x1<<(7+16);
        //delay1(2000000);
        for (i = 0 ; i < 200000 ; i++ );
        /*
            if(flag2 && (tickCounter  >   1000)){
                flag2   =   0;
                asm("BKPT");
                //completed ++;
            }
        */
    }
}

void task1(void)
{
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB -> MODER |= GPIO_MODER_MODER14_0;
	GPIOB -> OTYPER &= ~(GPIO_OTYPER_OT14);
	GPIOB -> OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR14);
	GPIOB -> PUPDR &= ~(GPIO_PUPDR_PUPDR14);
    static uint32_t    i;
    while(1)
    {
        GPIOB -> BSRR |= 0x1<<14;
        for (i = 0 ; i < 400000 ; i++ );
        //delay2(2000000);
        GPIOB -> BSRR |= 0x1<<(14+16);
        for (i = 0 ; i < 400000 ; i++ );
        //delay2(2000000);
        /*
            if(flag1 && (tickCounter  >   5000)){
                flag1   =   0;
                //completed++;
                asm("BKPT");
            }
        */
    }
}

uint32_t    pTask[NUM_TASKS]    =   {(uint32_t)task1, (uint32_t)task2, (uint32_t)task3};

int main(void)
{
    //asm("bkpt");
    pTaskMagic(NUM_TASKS);
    //asm("bkpt");
    /*
    asm(
        "BKPT                           \n\t"
        "loop:                          \n\t"
        "   LDR    r0,     =pTask      \n\t"
        "   LDR    r1,     [r0]        \n\t"
        "   SUB    r1,     r1,#1       \n\t"
        "   STR    r1,     [r0]        \n\t"
        "   B      loop                \n\t"
        "BKPT"
    );
    */
    startRTOS(pTask);
    while (1)
    {

    }
    return 0;
}