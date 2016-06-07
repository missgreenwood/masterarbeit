CC=g++-4.8
CFLAGS=-w -std=c++11

# list all .cpp files 
SOURCES=main.cpp BloomFilter.cpp BloomFilterNode.cpp BloomFilterIndexNode.cpp BloomFilterLeaf.cpp BloomFilterTree.cpp BloomFilterListNode.cpp BloomFilterList.cpp
OBJECTS=$(SOURCES:.c=.o)

# provide name of executable	
EXECUTABLE=bloomfilters

build: $(FILES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) 

clean:
	rm -r $(EXECUTABLE)

rebuild: clean build