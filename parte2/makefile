bin/testBSTree: BSTree.h testBSTree.cpp BSNode.h
	mkdir -p bin
	g++ -o bin/testBSTree BSTree.h BSNode.h testBSTree.cpp

bin/testBSTreeDict: ../Dict.h BSTreeDict.h BSNode.h ../TableEntry.h testBSTreeDict.cpp
	mkdir -p bin
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp

clean:
	rm -r *.o *.gch bin
