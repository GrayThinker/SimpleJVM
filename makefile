JVM: java_class.o class_loader.o
	g++ java_class.o class_loader.o -o JVM

java_class.o: java_class.cpp
	g++ -c java_class.cpp

class_loader.o: class_loader.cpp
	g++ -c class_loader.cpp

clean:
	rm *.o