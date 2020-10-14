#pragma once
#include "class_types.hpp"
#include "class_file_stream.hpp"
#include "class_structures.hpp"
// #include "java_class.hpp"
#include <iostream>

class Java_class : public Java_classfile_format {
    public:
    int _current;
    const char * path;

    Java_class(Classfile_stream *classfile);
    
    //constant pool parsing
    int parse_cp_entry(u1* cp_handle, cp_entry * cp, int index);

    // interface parsing    
    int parse_interface(u1 * interface_handle, u1 * temp_interface);
    
    // field parsing
    int parse_field(u1 * field_handle, field_info * temp_field);

    // attribute parsing
    int parse_attribute(u1 * attr_handle, attribute * temp_attr);
    
    // method parsing
    int parse_method(u1 * method_handle, method_info * temp_method);

    void print_cp();
    void print_methods();
    void parse_exception_table();
};