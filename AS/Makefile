MACH=cortex-m7
CC=arm-none-eabi-gcc
CFLAGS=-Wall -c -mthumb -O0 -std=gnu11 -mcpu=$(MACH)
FFLAGS=-Wall -nostdlib -T linker_script.ld -Wl,-Map=final.map
SS=arm-none-eabi-objdump
SFLAGS=-D

CH=arm-none-eabi-objcopy
HFLAGS=-Wall -O ihex

export CPATH=$(PWD)/include


all: main.o _main.o startup_stm32f767xx.o final.elf final.hex

main.o: main.c
	@echo Include path: $(CPATH)
	$(CC) $(CFLAGS) -o $@ $^
_main.o: _main.s
	$(CC) $(CFLAGS) -o $@ $^
startup_stm32f767xx.o : ./include/startup_stm32f767xx.c
	$(CC) $(CFLAGS) -o $@ $^
final.elf: main.o  _main.o startup_stm32f767xx.o
	$(CC) $(FFLAGS) -o $@ $^
final.hex: final.elf
	$(CH) $(HFLAGS) $^ $@

dis: main.s startup_stm32f767xx.s

main.s: main.o
	$(SS) $(SFLAGS) $^ > $@
startup_stm32f767xx.s: startup_stm32f767xx.o
	$(SS) $(SFLAGS) $^ > $@

clean:
	rm -f *.o *.elf *.map *.hex

flash:
	st-flash --format ihex write final.hex

debug:
	openocd -f board/st_nucleo_f7.cfg