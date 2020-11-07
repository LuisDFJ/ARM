.section .data
var1: .word 2
var2: .word 3

.section .text
.global _main
_main:
    ldr r0,adr_var1
    ldr r1,adr_var2
    ldr r2,[r0]
    ldr r3,[r1]
    

adr_var1: .word var1
adr_var2: .word var2
