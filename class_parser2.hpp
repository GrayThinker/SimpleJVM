#pragma once
#include "class_structures.hpp"
#include "class_file_stream.hpp"
#include "java_class_types.hpp"
#include <iostream>

class Parseclass : public Parseclass_format {
    public:  // change to constructor
    int _current;
    void parse(Classfile_stream *classfile);
    cp_info ** parse_cp(u1 *cp_handle);
    void print_cp();
    field_info * parse_fields(u1 *field_handle);
    method_info * parse_methods(u1 *method_handle);
    attribute_info * parse_attributes(u1 *attribute_handle);
};