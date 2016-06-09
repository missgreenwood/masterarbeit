CC=g++-4.8
CFLAGS=-w -std=c++11

# list all .cpp files 
SOURCES=tests.cpp BloomFilter.cpp BTreeNode.cpp BTree.cpp BPlusNode.cpp BPlusIndexNode.cpp BPlusLeaf.cpp BPlusTree.cpp BloomFilterNode.cpp BloomFilterIndexNode.cpp BloomFilterLeaf.cpp BloomFilterTree.cpp BloomFilterListNode.cpp BloomFilterList.cpp
OBJECTS=$(SOURCES:.c=.o)

# provide name of executable	
EXECUTABLE=Tests

build: $(FILES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) 

clean:
	rm -r $(EXECUTABLE)

rebuild: clean build