#pragma once

#include "class_types.hpp"
#include "class_structures.hpp"
#include "class_file_stream.hpp"
#include "class_parser_v2.hpp"

class Class_heap{
    public:
    Class_heap();
    ~Class_heap();

    void add_class(Java_class * j_class);
    void load_class(const char * class_name, Java_class * j_class);

    Java_class * get_class(std::string class_name);
};