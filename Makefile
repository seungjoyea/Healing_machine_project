all:main.elf
	
main.elf: libMyPeri.a main.o
	arm-linux-gnueabi-gcc main.o -lpthread -l MyPeri -L. -o main.elf
	scp *.elf ecube@192.168.0.8:/home/ecube/ecube_jo

main.o : main.c
	arm-linux-gnueabi-gcc -c main.c -o main.o

libMyPeri.a: led.o button.o fnd.o textlcd.o colorled.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o fnd.o textlcd.o colorled.o

colorled.o : colorled.c colorled.h
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o
	
led.o: led.c led.h
	arm-linux-gnueabi-gcc -c led.c -o led.o

button.o : button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o

fnd.o : fnd.c fnddrv.h
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o

textlcd.o : textlcd.c textlcddrv.h
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o

clean:
	rm -rf *.o *.a *.el-
