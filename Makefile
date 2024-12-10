bin/testBSTree: testBSTree.cpp BSTree.h BSNode.h
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp

bin/testHashTable: testHashTable.cpp Dict.h HashTable.h TableEntry.h 
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

clean:
	rm -rf *.o *.gch bin
