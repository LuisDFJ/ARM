.section .data
var:
    .word   18

.section .text
.global _main

_main:
    MOV     r10, lr
    B       _function
_function:
    LDR     r0, =adr_var
    LDR     r1, [r0]
    LDR     r0, [r1]
    MOV     r1, #0
    MOV     r2, #1
    CMP     r0, #1
    BGT     _loop
    
    B       end
    
_loop:
    ADD     r3, r1, r2
    MOV     r1, r2
    MOV     r2, r3
    SUB     r0, #1 
    CMP     r0, #1
    BGT     _loop
    B       end
end:
    BKPT
    MOV     lr, r10
    BX      lr

adr_var:
    .word   var

    