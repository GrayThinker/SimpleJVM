JVM: jvm.o class_loader.o class_file_stream.o utils.o
	g++ jvm.o class_loader.o class_file_stream.o utils.o -o JVM
	
jvm.o: jvm.cpp jvm.hpp
	g++ -c jvm.cpp

class_loader.o: class_loader.cpp class_loader.hpp
	g++ -c class_loader.cpp

class_file_stream.o: class_file_stream.cpp class_file_stream.hpp
	g++ -c class_file_stream.cpp

utils.o: utils.cpp utils.hpp
	g++ -c utils.cpp

clean:
	rm *.o *.exe