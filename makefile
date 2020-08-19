JVM: class_loader.o class_file_stream.o class_parser.o utils.o jvm.o java_class.o class_parser2.o
	g++ jvm.o class_loader.o class_file_stream.o utils.o class_parser.o java_class.o class_parser2.o -o JVM
	
class_parser.o: class_parser.cpp class_parser.hpp
	g++ -c class_parser.cpp

class_loader.o: class_loader.cpp class_loader.hpp
	g++ -c class_loader.cpp

class_file_stream.o: class_file_stream.cpp class_file_stream.hpp
	g++ -c class_file_stream.cpp

java_class.o: java_class.cpp java_class.hpp
	g++ -c java_class.cpp

class_parser2.o: class_parser2.cpp class_parser2.hpp
	g++ -c class_parser2.cpp

utils.o: utils.cpp utils.hpp
	g++ -c utils.cpp

jvm.o: jvm.cpp
	g++ -c jvm.cpp

clean:
	rm *.o *.exe