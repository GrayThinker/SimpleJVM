#pragma once
#include "class_structures.hpp"
#include "class_file_stream.hpp"
#include "class_types.hpp"
#include <iostream>

class Parseclass : public Parseclass_format {
    public:  // change to constructor
    int _current;

    Parseclass(Classfile_stream *classfile);
    ~Parseclass();
    void parse_cp(u1 *cp_handle);
    void print_cp();
    int parse_fields(u1 *field_handle, field_info * field);
    int parse_methods(u1 *method_handle, method_info* method);
    int parse_attributes(u1 *attribute_handle, attribute_info* attribute);
};