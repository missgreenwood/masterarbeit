CC=g++-4.8
CFLAGS=-w

# list all .cpp files 
SOURCES=main.cpp bloom_filter_tree.cpp
OBJECTS=$(SOURCES:.c=.o)

# provide name of executable	
EXECUTABLE=bloomfilters

build: $(FILES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) 

clean:
	rm -r $(EXECUTABLE)

rebuild: clean build