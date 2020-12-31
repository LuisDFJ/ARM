MACH=cortex-m7
CC=arm-none-eabi-gcc
CFLAGS=-Wall -c -mthumb -O0 -std=gnu11 -mcpu=$(MACH)
FFLAGS=-Wall -nostdlib -T linker_script.ld -Wl,-Map=./debug/final.map
SS=arm-none-eabi-objdump
SFLAGS=-D

CH=arm-none-eabi-objcopy
HFLAGS=-Wall -O ihex

export CPATH=$(PWD)/include:$(PWD)/lib


all: main.o  startup_stm32f767xx.o RTOS.o setUpPSP.o SysTick_Handlers.o final.elf final.hex

main.o: main.c
	@echo Include path: $(CPATH)
	$(CC) $(CFLAGS) -o ./debug/$@ $^
startup_stm32f767xx.o: ./include/startup_stm32f767xx.c
	$(CC) $(CFLAGS) -o ./debug/$@ $^
RTOS.o: ./lib/RTOS.c
	$(CC) $(CFLAGS) -o ./debug/$@ $^
setUpPSP.o: ./lib/setUpPSP.s
	$(CC) $(CFLAGS) -o ./debug/$@ $^
SysTick_Handlers.o: ./lib/SysTick_Handler.s
	$(CC) $(CFLAGS) -o ./debug/$@ $^
final.elf: ./debug/main.o ./debug/startup_stm32f767xx.o ./debug/RTOS.o ./debug/setUpPSP.o ./debug/SysTick_Handlers.o
	$(CC) $(FFLAGS) -o ./debug/$@ $^
final.hex: ./debug/final.elf
	$(CH) $(HFLAGS) $^ ./debug/$@

clean:
	rm -f ./debug/*.o ./debug/*.elf ./debug/*.map ./debug/*.hex

flash:
	st-flash --format ihex write ./debug/final.hex

bug:
	openocd -f board/st_nucleo_f7.cfg