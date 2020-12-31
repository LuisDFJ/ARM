
#ifndef     STM32F767xx
    #define     STM32F767xx
#endif
#ifndef     NUM_TASKS
    #define     NUM_TASKS           3
#endif
#ifndef     SIZE_STACK
    #define     SIZE_STACK          32
#endif
#ifndef     CORECLOCK
    #define     CORECLOCK           32768000
#endif
#ifndef     CONTROL_MODE
    #define     CONTROL_MODE        0x2
#endif
#ifndef     TICK_COUNT_LIMIT
    #define     TICK_COUNT_LIMIT    0xFFFFFFFF
#endif

#include    <stdint.h>
#include    "stm32f7xx.h"



void        setUpPSP            (void);
void        setUpRTOS           (uint32_t[]);
void        startRTOS           (uint32_t[]);
void        pTaskMagic          (uint32_t);
//volatile uint32_t    getTickCounter      (void);
