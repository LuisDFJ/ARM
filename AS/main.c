#define STM32F767xx
#define NUM_TASKS   2
#define STACK_SIZE  32
#define CORECLOCK   32768000 
#include "stm32f7xx.h"
#include <stdint.h>

int _main(void);

void SysTick_Handler(void){
    asm("bkpt 1");
}
/*
struct tcb {
    uint32_t     *pStack;
    struct tcb  *pNext;
};

typedef struct tcb tcb_t;
tcb_t tasks[NUM_TASKS];
tcb_t *pCurrent;
uint32_t tasks_stack[NUM_TASKS][STACK_SIZE];
uint32_t *stack1End;
uint32_t *stack2End;
uint32_t *stack1Start;
uint32_t *stack2Start;
*/

uint32_t stack[STACK_SIZE];
//uint32_t *pointer;
void    setUp  (void)
{
    /*asm(
        "LDR    r0,     =pointer    \n\t"
        "LDR    r0,     [r0]        \n\t"
        "MOV    r1,     #2          \n\t"
        "MSR    PSP,    r0          \n\t"
        "ISB                        \n\t"
        "MSR    CONTROL,r1          \n\t"
        "ISB                        \n\t"
        "BKPT"
    );*/
    SysTick_Config(CORECLOCK/1000);
    __set_PSP((uint32_t) &stack[STACK_SIZE-1]);
    __set_CONTROL(0x2);
    asm("BKPT");
}

/*void setUpScheduler(void){
    asm("cpsid i");
    tasks[0].pNext = &tasks[1];
    tasks[1].pNext = &tasks[0];
    tasks[0].pStack = &tasks_stack[0][STACK_SIZE-1];
    tasks[1].pStack = &tasks_stack[0][STACK_SIZE-1];
    pCurrent = &tasks[0];
    stack1End = &tasks_stack[0][STACK_SIZE-1];
    stack2End = &tasks_stack[1][STACK_SIZE-1];
    stack1Start = &tasks_stack[0][0];
    stack2Start = &tasks_stack[1][0];
    _main();
    SysTick_Config(CORECLOCK/1000);
    asm("cpsie i");
}*/

int main(void)
{
    setUp();
    //SysTick_Config(CORECLOCK/1000);
    //__set_PSP((uint32_t) &stack[STACK_SIZE-1]);
    //__set_CONTROL(0x2);
    //setUpScheduler();
    asm("BKPT");
    while (1)
    {
        asm(
            "MOV r0, #1 \n\t"
            "MOV r1, #2 \n\t"
            "MOV r2, #3 \n\t"
            "MOV r3, #4 \n\t"
        );
        //asm("bkpt");
    }
    return 0;
}