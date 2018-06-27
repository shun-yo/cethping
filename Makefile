all: cethping cethpingd

rawethernetsocketserver.o: rawethernetsocketserver.c
	gcc -c rawethernetsocketserver.c

ethernet.o: ethernet.c
	gcc -c ethernet.c


cethpingd.o: cethpingd.c
	gcc -c cethpingd.c

cethping.o: cethping.c
	gcc -c cethping.c


cethping: cethping.o rawethernetsocketserver.o ethernet.o
	gcc -o cethping cethping.o rawethernetsocketserver.o ethernet.o

cethpingd: cethpingd.o rawethernetsocketserver.o ethernet.o
	gcc -o cethpingd cethpingd.o rawethernetsocketserver.o ethernet.o

clean:
		rm *.o cethping cethpingd

