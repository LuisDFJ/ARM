.section    .text
.global     saveContext
.global     pCurrentTask

saveContext:
    MRS     r0,     psp
   // STMFD   sp!,    {r4-r7}
    MSR     psp,    r0
    BX      lr
    