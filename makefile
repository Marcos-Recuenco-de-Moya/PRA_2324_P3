bin/testTableEntry: TableEntry.h testTableEntry.cpp
	mkdir -p bin
	g++ -o bin/testTableEntry TableEntry.h testTableEntry.cpp
clean:
	rm -r *.o *.gch bin
