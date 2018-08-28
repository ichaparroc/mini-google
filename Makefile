CC = g++
CFLAGS = -g -Wall -o3
SRCS = main.cpp GettingTxT.cpp txt.cpp utils.cpp
PROG = out

build: main.cpp
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS)

run:
	./out

clean:
	rm -rf out