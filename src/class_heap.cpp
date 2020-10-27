#include "class_heap.hpp"
#include "class_file_stream.hpp"


Class_heap::Class_heap(){};
Class_heap::~Class_heap(){};

void Class_heap::load_class(const char * class_name, Java_class * j_class){
    // TODO: get abs path(class_name)
    Classfile_stream * code_stream = new Classfile_stream(class_name);
    *j_class = Java_class(code_stream);
};