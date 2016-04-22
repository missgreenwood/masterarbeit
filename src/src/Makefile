CC=g++-4.8
CFLAGS=-w
# list all .cpp files 
SOURCES=bloomtest.cpp
OBJECTS=$(SOURCES:.c=.o)
# provide name of executable	
EXECUTABLE=bloomtest

build: $(FILES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) 

clean:
	rm -r $(EXECUTABLE)

rebuild: clean build