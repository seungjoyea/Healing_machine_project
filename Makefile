all:main_led_jo.elf
	
main_led_jo.elf: libMyPeri.a ledtest.o
	arm-linux-gnueabi-gcc ledtest.o -l MyPeri -L. -o main_led_jo.elf
	
libMyPeri.a: led.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o
	
led.o: led.c led.h
	arm-linux-gnueabi-gcc -c -o led.o led.c

ledtest.o: ledtest.c led.h
	arm-linux-gnueabi-gcc -c -o ledtest.o ledtest.c

clean:
	rm -rf *.o *.a *.el-
