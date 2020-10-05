#pragma once
#include "class_types.hpp"
#include "class_file_stream.hpp"
#include "class_structures.hpp"
// #include "java_class.hpp"
#include <iostream>

class Java_class : public Java_classfile_format {
    public:
    Java_class(Classfile_stream *classfile);

    //constant pool parsing
    cp_entry * parse_constant_pool_entries(u1 *cp_handle, u2 cp_length);
    void print_cp();
    u1 * parse_constant_pool();

    // interface parsing    
    u2 * parse_interfaces();
    
    // field parsing
    void parse_field_attr();
    void parse_fields();

    void parse_attr(u1 * attr_handle);
    
    // method parsing
    void parse_methods_ls(u1 * method_handle, u2 methods_count);
    attribute_info *parse_method_attr(u1* attr_handle);
    void parse_method();
    void parse_exception_table();
};