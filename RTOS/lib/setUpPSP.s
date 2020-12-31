.section    .text

.global     pTaskMagic
.global     pTask

pTaskMagic:
    MOV     r2,     r0
    LDR     r0,     =pTask
    B       loop
loop:
    LDR     r1,     [r0]
    SUB     r1,     r1,#1
    STR     r1,     [r0]
    ADD     r0,     r0,#4
    SUB     r2,     r2,#1
    CMP     r2,     #0
    BGT     loop
    B       end
end:
    BX      lr     


