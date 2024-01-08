# test for makefile

# CC = gcc
# CFLAGS = 
# all: hello
# hello: hello.o
# 	$(CC) $(CFLAGS) hello.o -o hello
# hello.o: hello.c
# clean:
# 	rm -rf hello *.o


# CC = gcc
# CFLAGS = 
# OBJS = hello.o
# all: hello
# hello: hello.o

# 	$(CC) $(CFLAGS) $^ -o $@
# hello.o:hello.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -rf hello *.o


CC = gcc
CFLAGS = 
OBJS = hello1.o hello2.o
all: hello
hello: hello1.o hello2.o

	$(CC) $(CFLAGS) $^ -o $@
hello1.o:hello1.c
	$(CC) $(CFLAGS) $^ -o $@
hello2.o:hello2.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm  hello *.o