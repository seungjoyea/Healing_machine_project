all: buzzertest.elf

buzzertest.elf: libMyPeri.a buzzertest.o
	arm-linux-gnueabi-gcc buzzertest.o -l MyPeri -L. -o buzzertest.elf

buzzertest.o: buzzertest.c buzzer.h
	arm-linux-gnueabi-gcc -c buzzertest.c -o buzzertest.o

libMyPeri.a: buzzer.o
	arm-linux-gnueabi-ar rc libMyPeri.a buzzer.o

buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc --static -c buzzer.c -o buzzer.o