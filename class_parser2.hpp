#pragma once
#include "class_structures.hpp"
#include "class_file_stream.hpp"
#include "class_types.hpp"
#include <iostream>

class Parseclass : public Parseclass_format {
    public:  // change to constructor
    int _current;

    // should they take class members as functions or modify them directly
    void parse(Classfile_stream *classfile);
    void parse_cp(u1 *cp_handle);
    void print_cp();
    void parse_fields(u1 *field_handle);
    void parse_methods(u1 *method_handle);
    void parse_attributes(u1 *attribute_handle);
};