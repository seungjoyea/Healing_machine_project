all : main.elf

main.elf : libfinal.a main.o
	: gcc main.o -l final -L. -o final.elf

libfinal.a : 1.o 2.o
	ar rc libfinal.a 1.o 2.o

1.o : 1.c myProject.h
	gcc --static -c -o 1.o 1.c

2.o : 2.c myProject.h
	gcc --static -c -o 2.o 2.c

main.o : main.c myProject.h
	gcc --static -c -o main.o main.c

clean :
	rm -rf *.o *.a *.elf
