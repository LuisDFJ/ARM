CC=arm-none-eabi-gcc
CH=arm-none-eabi-objcopy
FF=-Wall -nostdlib -T linkerScript.ld -Wl,-Map=final.map
CF=-Wall -mthumb -c -O0 -std=gnu11 -mcpu=cortex-m7
HF=-Wall -O ihex

all:main.o startup_stm32f767xx.o final.elf final.hex

main.o:main.s
	$(CC) $(CF) -o $@ $^
startup_stm32f767xx.o:startup_stm32f767xx.c
	$(CC) $(CF) -o $@ $^
final.elf:main.o startup_stm32f767xx.o
	$(CC) $(FF) -o $@ $^
final.hex:final.elf
	$(CH) $(HF) $^ $@

clean:
	rm *.o *.elf *.hex *.map