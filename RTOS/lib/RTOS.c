#include    "RTOS.h"

/*<!    TCB TYPE DEFINITION     */
struct tcb {
    uint32_t    *pStack;
    struct tcb  *pNextTCB;
};
typedef struct tcb tcb_t;

/*<!    CURRENT TASK            */
tcb_t       *pCurrentTask;

/*<!    STACK DEFINITION        */
uint32_t    stackTasks  [NUM_TASKS][SIZE_STACK];
uint32_t    pTaskInit;

/*<!    TASKS DEFINITION        */
tcb_t   tasks   [NUM_TASKS];

/*<!    CONTROL MODE            */
uint32_t     controlMode    =   CONTROL_MODE;

/*<!    TICK COUNTER            */
//volatile uint32_t    tickCounter     =   0;


void    SysTick_Handler     (void)
{
    //asm("BKPT");
    asm("CPSID  i");
    //tickCounter++;
    //tickCounter     %=       TICK_COUNT_LIMIT;
    asm(
        "MRS    r1,     PSP             \n\t"
        "STMFD  r1!,    {r4-r6,r8-r11}  \n\t"
        "MSR    PSP,    r1              \n\t"
    );
    
    pCurrentTask->pStack    =   (uint32_t*)__get_PSP();
    pCurrentTask            =   pCurrentTask->pNextTCB;
    
    asm(
        "LDR    r0,     =pCurrentTask   \n\t"
        "LDR    r0,     [r0]            \n\t"
        "LDR    r0,     [r0]            \n\t"
        "MSR    PSP,    r0              \n\t"
        "ISB                            \n\t"
    );
    
    asm(
        "MRS    r1,     PSP             \n\t"
        "LDMFD  r1!,    {r4-r6,r8-r11}  \n\t"
        "MSR    PSP,    r1              \n\t"
    );
    asm("CPSIE  i");
}

/*
volatile uint32_t    getTickCounter  (void)
{
    return  tickCounter;
}
*/

void    scheduleRTOS    (void)
{
    for ( uint8_t i = 1 ; i < NUM_TASKS ; i++)
    {
        tasks[i-1].pNextTCB   =   &tasks[i];
    }
    tasks[NUM_TASKS-1].pNextTCB     =       &tasks[0];
}

void    setUpRTOS   (uint32_t pTasks[])
{
    for ( uint8_t i = 1 ; i < NUM_TASKS ; i++ ) 
    {
        stackTasks[i][SIZE_STACK-1]     =       0x01000000;
        stackTasks[i][SIZE_STACK-2]     =       pTasks[i];
        tasks[i].pStack     =   &stackTasks[i][SIZE_STACK-15];
    }
}

void    startRTOS   (uint32_t pTasks[])
{
    /*<!    DISABLE INTERRUPTS      */
    asm("CPSID  i");
    
    /*<!    RTOS SCHEDULE           */
    scheduleRTOS();
    /*
    tasks[0].pNextTCB   =   &tasks[1];
    tasks[1].pNextTCB   =   &tasks[0];
    */

    /*<!    ALLOCATE STACK          */
    setUpRTOS(pTasks);
    
    /*<!    INITIALIZE FIRST TASK   */
    tasks[0].pStack =   &stackTasks[0][SIZE_STACK-1];   
    pCurrentTask    =   &tasks[0];
    //pStackMain      =   &stackMain[SIZE_STACK-1];
    
    /*<!    SET PSP AS THREAD STACK */
    asm(
        "LDR    r0,     =pCurrentTask   \n\t"
        "LDR    r0,     [r0]            \n\t"
        "LDR    r0,     [r0]            \n\t"
        "MSR    PSP,    r0              \n\t"
        "ISB                            \n\t"
        "LDR    r0,     =controlMode    \n\t"
        "LDR    r0,     [r0]            \n\t"
        "MSR    CONTROL,r0              \n\t"
        "ISB                            \n\t"
    );

    pTaskInit   =   pTasks[0];
    SysTick_Config(CORECLOCK/1000);
    /*<!    ENABLE INTERRUPTS       */
    asm("CPSIE  i");
    //asm("BKPT");
    asm(
        "LDR    r0,     =pTaskInit      \n\t"
        "LDR    r0,     [r0]            \n\t"
        "MOV    PC,     r0              \n\t"
    );
}


