#pragma once
#include "class_structures.hpp"
#include "class_file_stream.hpp"
#include "java_class_types.hpp"

class Parseclass : public Parseclass_format {
    public:  // change to constructor
    void parse(Classfile_stream *classfile);
    cp_info ** parse_cp(u1 *cp_handle);
    void print_cp();
};