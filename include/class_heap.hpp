#pragma once
#include "precompiled.hpp"
#include "class_types.hpp"
#include "class_structures.hpp"
#include "class_file_stream.hpp"
#include "class_parser.hpp"

class Class_heap{
    private:
    public:
    Class_heap();
    std::map<const char *, Java_class *> _heap;
    ~Class_heap();

    void add_class(Java_class * j_class);
    void load_class(const char * class_name, Java_class * j_class);
    Java_class * get_class(std::string class_name);
};