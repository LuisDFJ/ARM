.section .text

.global _main

_main:
    BKPT
    B       end
end:
    BX lr
