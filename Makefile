all: cethping cethpingd

RawEthernetSocket.o: RawEthernetSocket.c
	gcc -c RawEthernetSocket.c

ethernet.o: ethernet.c
	gcc -c ethernet.c


cethpingd.o: cethpingd.c
	gcc -c cethpingd.c

cethping.o: cethping.c
	gcc -c cethping.c


cethping: cethping.o RawEthernetSocket.o ethernet.o
	gcc -o cethping cethping.o RawEthernetSocket.o ethernet.o

cethpingd: cethpingd.o RawEthernetSocket.o ethernet.o
	gcc -o cethpingd cethpingd.o RawEthernetSocket.o ethernet.o

clean:
	rm *.o cethping cethpingd

