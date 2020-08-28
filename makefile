CC=g++
DEPS=*.hpp
OBJ=*.o
TARGET=SJVM
BUILDDIR=.\build

$(TARGET): class_file_stream.o utils.o jvm.o class_parser.o
	$(CC) jvm.o class_file_stream.o utils.o class_parser.o -o $(TARGET)
	
class_parser.o: class_parser.cpp class_parser.hpp
	$(CC) -c class_parser.cpp

class_file_stream.o: class_file_stream.cpp class_file_stream.hpp
	$(CC) -c class_file_stream.cpp


class_parser.o: class_parser.cpp class_parser.hpp
	$(CC) -c class_parser.cpp

.\build\utils.o: utils.cpp utils.hpp
	$(CC) -c utils.cpp

jvm.o: jvm.cpp
	$(CC) -c jvm.cpp

.PHONY: clean

clean:
	rm -f *.o *.exe