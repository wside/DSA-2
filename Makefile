useGraph.out: useGraph.o graph.o heap.o hash.o
	g++ -o useGraph.out useGraph.o graph.o heap.o hash.o

useGraph.o: useGraph.cpp
	g++ -std=c++11 -c useGraph.cpp

graph.o: graph.cpp graph.h
	g++ -std=c++11 -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -std=c++11 -g -o useGraphDebug.out useGraph.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.out *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups