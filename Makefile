useHeap.out: useHeap.o heap.o hash.o
	g++ -o useHeap.out useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp
	g++ -std=c++11 -c useHeap.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -std=c++11 -g -o useHeapDebug.out useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.out *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
