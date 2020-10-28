#include "class_heap.hpp"
#include "class_file_stream.hpp"
#include "precompiled.hpp"
#include "utils.hpp"

Class_heap::Class_heap(){};
Class_heap::~Class_heap(){};

void Class_heap::add_class(Java_class * j_class){
    // should only be used by class_loader
    // CONSTANT_Utf8_info utf = j_class->constant_pool[j_class->this_class].c_utf8;
    // std::string name = utf_to_str(utf.bytes, utf.length);
    // _heap[name.c_str()] = j_class;
}

void Class_heap::load_class(const char * class_name, Java_class * j_class){
    // TODO: get abs path(class_name)
    Classfile_stream * code_stream = new Classfile_stream(class_name);
    *j_class = Java_class(code_stream);
}

Java_class * Class_heap:: get_class(std::string class_name){
    // auto it = _heap.find(class_name.c_str());
    // if (it != _heap.end()){
    //     return _heap[class_name.c_str()];
    // }   
}

