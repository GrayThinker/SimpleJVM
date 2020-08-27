CC=g++
DEPS=*.hpp
OBJ=*.o
TARGET=SJVM

$(TARGET): class_loader.o class_file_stream.o class_parser.o utils.o jvm.o class_parser2.o
	$(CC) jvm.o class_loader.o class_file_stream.o utils.o class_parser.o class_parser2.o -o $(TARGET)
	
class_parser.o: class_parser.cpp class_parser.hpp
	$(CC) -c class_parser.cpp

class_loader.o: class_loader.cpp class_loader.hpp
	$(CC)-c class_loader.cpp

class_file_stream.o: class_file_stream.cpp class_file_stream.hpp
	$(CC) -c class_file_stream.cpp


class_parser2.o: class_parser2.cpp class_parser2.hpp
	$(CC) -c class_parser2.cpp

utils.o: utils.cpp utils.hpp
	$(CC) -c utils.cpp

jvm.o: jvm.cpp
	$(CC) -c jvm.cpp

clean:
	rm *.o *.exe