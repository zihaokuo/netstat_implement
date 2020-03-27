GCC = gcc
CFLAGS = -g -Wall
.c.o: # old-fashioned!
	$(GCC) -c $< $(CFLAGS)

test: GET_PROGRAM_INFO.o GET_IP_INFO.o main.o
	$(GCC) -o hw1 $^

clean:
	rm -r *.o
