JVM: class_loader.o class_file_stream.o class_parser.o utils.o jvm.o
	g++ jvm.o class_loader.o class_file_stream.o utils.o class_parser.o -o JVM
	
class_parser.o: class_parser.cpp class_parser.hpp
	g++ -c class_parser.cpp

class_loader.o: class_loader.cpp class_loader.hpp
	g++ -c class_loader.cpp

class_file_stream.o: class_file_stream.cpp class_file_stream.hpp
	g++ -c class_file_stream.cpp

utils.o: utils.cpp utils.hpp
	g++ -c utils.cpp

jvm.o: jvm.cpp
	g++ -c jvm.cpp

clean:
	rm *.o *.exe