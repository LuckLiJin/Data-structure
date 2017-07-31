driver.out: driver.o list.o 
	gcc -Wall -Werror -g -o driver.out driver.o list.o

list.o: list.c list.h 
	gcc -Wall -Werror -g -c list.c
driver.o: driver.c 
	gcc -Wall -Werror -g -c driver.c


clean:
	rm -f *.o driver.out
