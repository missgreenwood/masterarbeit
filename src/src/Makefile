CC=g++-4.8
CFLAGS=-w

# list all .cpp files 
SOURCES=main.cpp BloomFilter.cpp BloomFilterVec.cpp BTreeNode.cpp BTree.cpp BPlusNode.cpp BPlusIndexNode.cpp BPlusLeaf.cpp BPlusTree.cpp BloomFilterNode.cpp BloomFilterTree.cpp 
OBJECTS=$(SOURCES:.c=.o)

# provide name of executable	
EXECUTABLE=bloomfilters

build: $(FILES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) 

clean:
	rm -r $(EXECUTABLE)

rebuild: clean build