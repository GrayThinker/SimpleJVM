#pragma once
#include "class_types.hpp"
#include "class_file_stream.hpp"
#include "class_structures.hpp"
#include "java_class.hpp"
#include <iostream>
class Java_class : public Java_classfile_format {
    public:
    void parse_class(Classfile_stream *classfile);
    //constant pool parsing
    cp_entry * parse_constant_pool_entries(u1 *cp_handle, u2 cp_length);
    void print_cp();
    u1 * parse_constant_pool();
    // interface parsing    
    u2 * parse_interfaces();
    // field parsing
    void parse_field_attr();
    void parse_fields();
    // method parsing
    void parse_methods_ls();
    void parse_method();
    void parse_exception_table();
};