bin/testHashTable: testHashTable.cpp Dict.h HashTable.h TableEntry.h 
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

clean:
	rm -rf *.o *.gch bin
