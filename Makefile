CC = g++
CFLAGS = -std=c++11 -g

.PHONY: all clean

all: test1 test2 test3

test1: test1.cpp BaseNode.h Placeholder.h Op.h Binary.h Add.h Sub.h Multiply.h Divide.h Constant.h
	$(CC) $(CFLAGS) test1.cpp -o test1

test2: test2.cpp BaseNode.h Placeholder.h Op.h Binary.h Add.h Sub.h Multiply.h Divide.h Constant.h
	$(CC) $(CFLAGS) test1.cpp -o test2

test3: test3.cpp BaseNode.h Placeholder.h Op.h Binary.h Add.h Sub.h Multiply.h Divide.h Constant.h
	$(CC) $(CFLAGS) test1.cpp -o test3

clean:
	-rm *.o test1 test2 test3
	-del *.o test1.exe test2.exe test3.exe